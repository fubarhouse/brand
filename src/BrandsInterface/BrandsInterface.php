<?php

/**
 * @file
 * Interface for the Brands class.
 */

/**
 * The interface for the Brand class describes the available API.
 */
interface BrandsInterface {
  /**
   * Constructor for the Brands interface.
   *
   * @param string $machine_name
   *   The identifying machine name for the Brands object.
   * @param bool $latest_only
   *   A boolean to indicate if this Brands object is to fetch the latest
   *   set of data for the given machine name, or all available entries.
   *   The same logic will be applied if the machine name is null.
   */
  public function __construct(string $machine_name = NULL, bool $latest_only = FALSE);
}
