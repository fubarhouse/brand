<?php

/**
 * @file
 * Interfaces for the Brand class.
 */

/**
 * The interface for the Brand class describes the available API.
 */
interface BrandInterface {

  /**
   */
  public function __construct(string $machine_name, $timestamp = NULL);

  /**
   */
  public function Check() : bool;

  /**
   */
  public function add(string $machine_name, array $options);

  /**
   * Delete a record.
   *
   * If $timestamp is NULL, the entire record will be removed.
   *
   * @param mixed $timestamp
   *   The timestamp of the record to remove.
   */
  public function remove($timestamp = NULL);

}