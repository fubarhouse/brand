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
    public function add() {}

    /**
     * @inheritdoc
     */
    public function remove() {
        $machine_name = '';
        $timestamp =  '';
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