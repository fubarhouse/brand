<?php

class Brand implements BrandInterface {

  public static $Raw;
  public static $Brand;

  /**
   * @inheritdoc
   */
  public function __construct(string $machine_name, $timestamp = NULL, $skip_query = FALSE)
  {

    // If the query has already run via Brands, we don't want to re-run it.
    if ($skip_query === TRUE) {
      $obj = (object) array(
        'title' => '',
        'machine_name' => $machine_name,
        'description' => '',
        'assets_inherit' => 0,
        'date_created' => 0,
        'date_lock' => 0,
        'date_start' => 0,
        'date_finish' => 0,
        'path_assets' => 0,
        'path_search' => '',
        'path_visibility' => '',
        'meta_chrome' => 0,
        'meta_viewport' => 0,
        'http_robots' => 0,
        'bid' => 0,
        'rid' => 0,
        'tid' => 0,
        'uid' => 0,
        'vid' => 0,
      );
    }
    else {
      // Logic to identify the machine_name goes here.

      // Start a query to get the fields.
      $data = db_select('brand', 'n')
        ->fields('n', [
          'title',
          'machine_name',
          'description',
          'assets_inherit',
          'date_created',
          'date_lock',
          'date_start',
          'date_finish',
          'path_assets',
          'path_search',
          'path_visibility',
          'meta_chrome',
          'meta_viewport',
          'http_robots',
          'bid',
          'rid',
          'tid',
          'uid',
          'vid',
        ]);

      // If a timestamp was specified, add it as a condition.
      if (NULL !== $timestamp) {
        $data->condition('date_created', $timestamp, '=');
      }

      // Add the machine name as a condition and sort it.
      $data->condition('machine_name', $machine_name, '=');
      $data->orderBy('n.date_created', 'ASC');

      // Execute and store it!
      $dataset = $data->execute()->fetchAll();
      self::$Raw = end($dataset);
      unset($dataset);
      var_dump(self::$Raw);

      // Return FALSE if nothing came back.
      if (empty(self::$Raw)) {
        self::$Brand = NULL;
        return FALSE;
      }

      // Otherwise turn it into a structured array.
      else {
        $obj = (object) array(
          'title' => self::$Raw->title,
          'machine_name' => self::$Raw->machine_name,
          'description' => self::$Raw->description,
          'assets_inherit' => self::$Raw->assets_inherit,
          'date_created' => self::$Raw->date_created,
          'date_lock' => self::$Raw->date_lock,
          'date_start' => self::$Raw->date_start,
          'date_finish' => self::$Raw->date_finish,
          'path_assets' => self::$Raw->path_assets,
          'path_search' => self::$Raw->path_search,
          'path_visibility' => self::$Raw->path_visibility,
          'meta_chrome' => self::$Raw->meta_chrome,
          'meta_viewport' => self::$Raw->meta_viewport,
          'http_robots' => self::$Raw->http_robots,
          'bid' => self::$Raw->bid,
          'rid' => self::$Raw->rid,
          'tid' => self::$Raw->tid,
          'uid' => self::$Raw->uid,
          'vid' => self::$Raw->vid,
        );
      }

    }
    self::$Brand = $obj;
  }

    /**
     * @inheritdoc
     */
    public function check() : bool {
      if ($node = menu_get_object()) {

        // Book.
        if (module_exists('book')) {
          if (isset($node->book['bid'])) {
            if ((int) $node->book['bid'] === (int) self::$Brand->bid) {
              return TRUE;
            }
          }
        }

        // Nodes.
        if (module_exists('node')) {
          $delimiter = preg_split('/\s+/', self::$Brand->path_visibility);
          foreach ($delimiter as $node_target) {

            // Look for "node/xxx" in the path_visibility field:
            if ($node = menu_get_object()) {
              if (strpos($node_target, 'node/' . $node->nid) !== FALSE) {
                return TRUE;
              }
            }

            // Check if the current node alias is the node target.
            if ($node_target === current_path()) {
              return TRUE;
            }

            // Check if the current node path matches the node target.
            if (drupal_match_path(current_path(), $node_target)) {
              return TRUE;
            }

            // Check if the current node alias matches the node target.
            if (drupal_match_path(drupal_get_path_alias(), $node_target)) {
              return TRUE;
            }
          }
        }

        // Taxonomy.
        if (module_exists('taxonomy')) {
          foreach ((array) field_info_instances('node', $node->type) as $field_name => $info) {
            foreach ((array) field_get_items('node', $node, $field_name) as $item) {
              if (is_array($item) && !empty($item['tid']) && self::$Brand->tid == $item['tid']) {
                return TRUE;
              }
            }
          }
        }
      }

      // Paths.
      $delimiter = preg_split('/\s+/', self::$Brand->path_visibility);
      foreach ($delimiter as $path_target) {
        if (!empty(trim($path_target))) {
          if (isset($_GET['destination']) && drupal_match_path($_GET['destination'], $path_target)) {
            return TRUE;
          }
          elseif (isset($_GET['q']) && drupal_match_path($_GET['q'], $path_target)) {
            return TRUE;
          }
        }
      }
      return FALSE;
    }

    /**
     * @inheritdoc
     */
    public function add(string $machine_name, array $options = array()) {
        $query = db_insert('brand');
        $now = new DateTime();
        $title = (isset($options['title'])) ? $options['title'] : '';
        $description = (isset($options['description'])) ? $options['description'] : '';
        $assets_inherit = (isset($options['assets_inherit'])) ? $options['assets_inherit'] : 0;
        $date_created = $now->getTimestamp();
        $date_lock = (isset($options['date_lock'])) ? $options['date_lock'] : 0;
        $date_start = $now->getTimestamp();
        $date_finish = $now->getTimestamp();
        $path_assets = (isset($options['path_assets'])) ? $options['path_assets'] : '';
        $path_search = (isset($options['path_search'])) ? $options['path_search'] : '';
        $path_visibility = (isset($options['path_visibility'])) ? $options['path_visibility'] : '';
        $bid = (isset($options['bid'])) ? $options['bid'] : 0;
        $rid = (isset($options['rid'])) ? $options['rid'] : 0;
        $tid = (isset($options['tid'])) ? $options['tid'] : 0;
        $uid = (isset($options['uid'])) ? $options['uid'] : 0;
        $vid = (isset($options['vid'])) ? $options['vid'] : 0;
        $mapped_fields = array(
            'title' => $title,
            'machine_name' => $machine_name,
            'description' => $description,
            'assets_inherit' => $assets_inherit,
            'date_created' => $date_created,
            'date_lock' => $date_lock,
            'date_start' => $date_start,
            'date_finish' => $date_finish,
            'path_assets' => $path_assets,
            'path_search' => $path_search,
            'path_visibility' => $path_visibility,
            'bid' => $bid,
            'rid' => $rid,
            'tid' => $tid,
            'uid' => $uid,
            'vid' => $vid,
        );
        $query->fields($mapped_fields);
        $query->execute();
      self::$Brand = (object) $mapped_fields;
    }

    /**
     * @inheritdoc
     */
    public function remove() {
        $machine_name = self::$Brand->machine_name;
        $timestamp = self::$Brand->date_created;
        if ($timestamp > 0) {
            db_delete('brand')
                ->condition('machine_name', $machine_name, '=')
                ->condition('date_created', $timestamp, '=')
                ->execute();
        }
        else {
            db_delete('brand')
                ->condition('machine_name', $machine_name, '=')
                ->execute();
        }
    }
}