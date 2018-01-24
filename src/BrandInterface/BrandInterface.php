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
   */
  public function remove();

}