<?php

class Brand implements BrandInterface {

    public static $Raw;
    public static $Brand;

    /**
     * @inheritdoc
     */
    public function __construct(string $machine_name, $timestamp = NULL) {

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
        $this::$Raw = $data->execute()->fetchAll();

        // Return FALSE if nothing came back.
        if (empty($this::$Raw)) {
            return FALSE;
        }

        // Otherwise turn it into a structured array.
        else {
            $obj = (object) array(
                'title' => $this::$Raw['title'],
                'machine_name' => $this::$Raw['machine_name'],
                'description' => $this::$Raw['description'],
                'assets_inherit' => $this::$Raw['assets_inherit'],
                'date_created' => $this::$Raw['date_created'],
                'date_lock' => $this::$Raw['date_lock'],
                'date_start' => $this::$Raw['date_start'],
                'date_finish' => $this::$Raw['date_finish'],
                'path_assets' => $this::$Raw['path_assets'],
                'path_search' => $this::$Raw['path_search'],
                'path_visibility' => $this::$Raw['path_visibility'],
                'bid' => $this::$Raw['bid'],
                'rid' => $this::$Raw['rid'],
                'tid' => $this::$Raw['tid'],
                'uid' => $this::$Raw['uid'],
                'vid' => $this::$Raw['vid'],
            );

            $this::$Brand = $obj;
        }
    }

    /**
     * @inheritdoc
     */
    public function check() {
        if (isset($this::$Brand->machine_name) && $this::$Brand->machine_name !== NULL) {
            return TRUE;
        } else {
            return FALSE;
        }
    }

    /**
     * @inheritdoc
     */
    public function find() {}

    /**
     * @inheritdoc
     */
    public function get() {}

    /**
     * @inheritdoc
     */
    public function add(string $machine_name, array $options) {
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
        $bid = (isset($options['assets_inherit'])) ? $options['bid'] : 0;
        $rid = (isset($options['assets_inherit'])) ? $options['rid'] : 0;
        $tid = (isset($options['assets_inherit'])) ? $options['tid'] : 0;
        $uid = (isset($options['assets_inherit'])) ? $options['uid'] : 0;
        $vid = (isset($options['assets_inherit'])) ? $options['vid'] : 0;
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
            'path_search' => $path_assets,
            'path_visibility' => $path_visibility,
            'bid' => $bid,
            'rid' => $rid,
            'tid' => $tid,
            'uid' => $uid,
            'vid' => $vid,
        );
        $query->fields($mapped_fields);
        $query->execute();
        $this::$Brand = $mapped_fields;
    }

    /**
     * @inheritdoc
     */
    public function remove() {
        $machine_name = $this::$Brand['machine_name'];
        $timestamp =  $this::$Brand['date_created'];
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