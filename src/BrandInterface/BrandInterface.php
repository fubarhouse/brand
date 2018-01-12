<?php

/**
 * @file
 * Interfaces for the Brand class.
 */

namespace Drupal\Brand\BrandInterface;

/**
 * The interface for the Brand class describes the available API.
 */
interface BrandInterface {

    public function __construct();

    public function check() ;

    public function find() ;

    public function get();

    public function add();

    public function remove();

}