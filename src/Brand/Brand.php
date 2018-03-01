<?php

/**
 * @file
 * Class file for the Brand class.
 */

class Brand implements BrandInterface {

  // $Raw is a public result from a database query before processing.
  public static $Raw;
  // $Brand is the public object which exposes the data for the Brand.
  public static $Brand;

  /**
   * Constructor.
   *
   * @inheritdoc
   */
  public function __construct(string $machine_name, int $timestamp = NULL, $skip_query = FALSE, $options = NULL) {

    // If the query has already run via Brands, we don't want to re-run it.
    if ($skip_query === TRUE) {
      if (NULL !== $options) {
        $obj = $options;
      } else {
        $obj = (object)array(
          'title' => '',
          'machine_name' => $machine_name,
          'description' => '',
          'date_created' => 0,
          'date_lock' => 0,
          'date_start' => 0,
          'date_finish' => 0,
          'path_visibility' => '',
          'content_type' => '',
          'theme' => '',
          'weight' => 0,
          'bid' => 0,
          'rid' => 0,
          'tid' => 0,
          'uid' => 0,
          'vid' => 0,
        );
      }
    }
    else {
      // Start a query to get the fields.
      $data = db_select('brand', 'n')
        ->fields('n', [
          'title',
          'machine_name',
          'description',
          'date_created',
          'date_lock',
          'date_start',
          'date_finish',
          'path_visibility',
          'content_type',
          'theme',
          'weight',
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

      // Return FALSE if nothing came back.
      if (empty(self::$Raw)) {
        self::$Brand = NULL;
        return;
      }

      // Otherwise turn it into a structured array.
      else {
        $obj = (object) array(
          'title' => self::$Raw->title,
          'machine_name' => self::$Raw->machine_name,
          'description' => self::$Raw->description,
          'date_created' => self::$Raw->date_created,
          'date_lock' => self::$Raw->date_lock,
          'date_start' => self::$Raw->date_start,
          'date_finish' => self::$Raw->date_finish,
          'path_visibility' => self::$Raw->path_visibility,
          'content_type' => self::$Raw->content_type,
          'theme' => self::$Raw->theme,
          'weight' => self::$Raw->weight,
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
   * Check the brand to see if it's supposed to show.
   *
   * @inheritdoc
   */
  public function Check() : bool {
    if (user_has_role(self::$Brand->rid) || ((int) user_role_load(self::$Brand->rid)->rid === DRUPAL_ANONYMOUS_RID)) {
      if ((time() >= (int) self::$Brand->date_start && time() <= self::$Brand->date_finish) || (int) self::$Brand->date_lock === 1) {
        return TRUE;
      }
    }
    return FALSE;
  }

  /**
   * Create a new database row based upon the current object.
   *
   * @inheritdoc
   */
  public function add(string $machine_name, array $options = array()) {
    $query = db_insert('brand');
    $now = new DateTime();
    $title = (isset($options['title'])) ? $options['title'] : '';
    $description = (isset($options['description'])) ? $options['description'] : '';
    $date_created = $now->getTimestamp();
    $date_lock = (isset($options['date_lock'])) ? $options['date_lock'] : 0;
    $date_start = (isset($options['date_start'])) ? $options['date_start'] : $now->getTimestamp();
    $date_finish = (isset($options['date_finish'])) ? $options['date_finish'] : $now->getTimestamp();
    $path_visibility = (isset($options['path_visibility'])) ? $options['path_visibility'] : '';
    $content_type = (isset($options['content_type'])) ? $options['content_type'] : '';
    $theme = (isset($options['theme'])) ? $options['theme'] : '';
    $weight = (isset($options['weight'])) ? $options['weight'] : 0;
    $bid = (isset($options['bid'])) ? $options['bid'] : 0;
    $rid = (isset($options['rid'])) ? $options['rid'] : 0;
    $tid = (isset($options['tid'])) ? $options['tid'] : 0;
    $uid = (isset($options['uid'])) ? $options['uid'] : 0;
    $vid = (isset($options['vid'])) ? $options['vid'] : 0;
    $mapped_fields = array(
      'title' => $title,
      'machine_name' => $machine_name,
      'description' => $description,
      'date_created' => $date_created,
      'date_lock' => $date_lock,
      'date_start' => $date_start,
      'date_finish' => $date_finish,
      'path_visibility' => $path_visibility,
      'content_type' => $content_type,
      'theme' => $theme,
      'weight' => $weight,
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
   * Remove a database row based upon the current object.
   *
   * @inheritdoc
   */
  public function remove(int $timestamp = NULL) {
    $machine_name = self::$Brand->machine_name;

    $q = db_delete('brand');
    $q->condition('machine_name', $machine_name, '=');
    if ($timestamp !== NULL) {
      $q->condition('date_created', $timestamp, '=');
      $q->execute();
      drupal_set_message("The record timestamped {$timestamp} for brand {$machine_name} has been removed.");
    }
    else {
      $q->execute();
      drupal_set_message("The brand {$machine_name} has been removed.");
    }
  }
}
