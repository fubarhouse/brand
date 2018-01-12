<?php

namespace Drupal\Brand\Brand;

class Brand implements BrandInterface {

    public $Raw;

    /**
     * @inheritdoc
     */
    public function __construct(string $machine_name, $timestamp = NULL) {
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

        if (NULL !== $timestamp) {
            $data->condition('date_created', $timestamp, '=');
        }

        $data->condition('machine_name', $machine_name, '=');
        $data->orderBy('n.date_created', 'ASC');
        $this::$Raw = $data->execute()->fetchAll();

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
    }

    /**
     * @inheritdoc
     */
    public function check() {}

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