<?php

/**
 * @file
 * Class file for the Brands class.
 */

class Brands implements BrandsInterface {

    public static $Brands;

    public function __construct(string $machine_name = NULL, bool $latest_only = FALSE) {
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
                'bid',
                'rid',
                'tid',
                'uid',
                'vid',
            ]);

        // If a machine name was specified, add it as a condition.
        if (NULL !== $machine_name) {
            $data->condition('machine_name', $machine_name, '=');
        }

        if ($latest_only === TRUE) {
            $data->distinct('n.machine_name');
        }

        // Sort it.
        $data->orderBy('n.date_created', 'ASC');

        // Execute and store it!
      $AllData = $data->execute()->fetchAll();
      $brands = array();
      foreach ($AllData as $Data) {
        // Additional filter for latest date
        if ($latest_only === TRUE) {
          $brands[$Data->machine_name] = new Brand($Data->machine_name, $Data->date_created);
        }
        else {
          $brands[] = new Brand($Data->machine_name, $Data->date_created);
        }
      }

      $this::$Brands = $brands;
    }
}
