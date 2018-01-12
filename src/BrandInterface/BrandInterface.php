<?php

/**
 * @file
 * Interfaces for the Brand class.
 */

/**
 * The interface for the Brand class describes the available API.
 */
interface BrandInterface {

    public function __construct(string $machine_name, $timestamp = NULL);

    public function check() ;

    public function find() ;

    public function get();

    public function add();

    public function remove();

}