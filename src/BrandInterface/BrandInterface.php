<?php

/**
 * @file
 * Interface for the Brand class.
 */

/**
 * The interface for the Brand class describes the available API.
 */
interface BrandInterface {

  /**
   * The constructor function which creates a Brand object.
   *
   * @param string $machine_name
   *   The mandatory input which will be used to filter the result.
   * @param int $timestamp
   *   The unix timestamp of the item you're fetching.
   * @param bool $skip_query
   *   A boolean to prevent receiving an error object instead of input
   *   data. Used for manual manipulation of data.
   */
  public function __construct(string $machine_name, int $timestamp = NULL, $skip_query = FALSE);

  /**
   * Determine if a Brand should be applied to the current entity.
   */
  public function Check() : bool;

  /**
   * Create a new entry based on an array for manual data input.
   *
   * @param string $machine_name
   *   The identifying machine name for this item.
   * @param array $options
   *   The array containing the available options/values.
   */
  public function add(string $machine_name, array $options);

  /**
   * Delete a record.
   *
   * If $timestamp is NULL, the entire record will be removed.
   *
   * @param int $timestamp
   *   The timestamp of the record to remove.
   */
  public function remove(int $timestamp = NULL);

}
