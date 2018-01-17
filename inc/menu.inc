<?php

/**
 * @file
 * Add menu items and pages for the module.
 */

/**
 * Implements hook_menu().
 *
 * @inheritdoc
 */
function brand_menu() {
  $items['admin/config/user-interface/brands'] = array(
    'title' => 'Brands',
    'type' => MENU_LOCAL_TASK,
    'description' => '',
    'access callback' => TRUE,
  );
  $items['admin/config/user-interface/brands/add'] = array(
    'title' => 'Brand Creation Form',
    'type' => MENU_LOCAL_TASK,
    'description' => '',
    'page callback' => array('drupal_get_form'),
    'page arguments' => array('brand_add_form'),
    'access callback' => TRUE,
    'file' => 'system.admin.inc',
    'file path' => drupal_get_path('module', 'system'),
  );
  $items['admin/config/user-interface/brands/edit'] = array(
    'title' => 'Brands',
    'type' => MENU_LOCAL_TASK,
    'description' => '',
    'page callback' => array('drupal_get_form'),
    'page arguments' => array('brand_edit_form'),
    'access callback' => TRUE,
    'file' => 'system.admin.inc',
    'file path' => drupal_get_path('module', 'system'),
  );
  return $items;
}
