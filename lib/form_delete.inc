<?php

/**
 * @file
 * Delete forms.
 */

/**
 * Implements hook_form().
 *
 * @inheritdoc
 */
function brand_delete_form($form, $form_state) {
  $arguments = explode('/', $_GET['q']);
  if (count($arguments) >= 4) {
    $machine_name = $arguments[4];
    if (count($arguments) >= 6 && $arguments[6] === 'delete') {
      $timestamp = $arguments[5];
    }

    $form['disclaimer'] = array(
      '#type' => 'markup',
    );
    if (isset($timestamp)) {
      $form['disclaimer']['#markup'] = "<p>Are you absolutely sure you wish to proceed with the following?</p><ul><li>Delete record of the brand identified by machine name '{$machine_name}' with matching creation timestamp of '{$timestamp}'</li></li></ul><p>This action is not reversible.</p></p>";
    }
    else {
      $form['disclaimer']['#markup'] = "<p>Are you absolutely sure you wish to proceed with the following?</p><ul><li>Delete all records of the brand identified by machine name '{$machine_name}'</li></li></ul><p>This action is not reversible.</p></p>";
    }
    $form['submit']['no'] = array(
      '#type' => 'submit',
      '#value' => 'No',
      '#submit' => array('brand_form_delete_item_cancel'),
      '#limit_validation_errors' => array(),
    );
    $form['submit']['yes'] = array(
      '#type' => 'submit',
      '#value' => 'Yes',
    );
  }
  return $form;
}

/**
 * Implements hook_form_submit().
 *
 * @inheritdoc
 */
function brand_delete_form_submit($form, $form_state) {
  $arguments = explode('/', $_GET['q']);
  $machine_name = $arguments[4];
  if (count($arguments) >= 6 && $arguments[6] === 'delete') {
    $timestamp = $arguments[5];
    $brand = new Brand($machine_name, $timestamp);
    $brand->remove($timestamp);
    drupal_goto('/admin/config/user-interface/brands/' . $machine_name);
  }
  else {
    $brand = new Brand($machine_name, NULL);
    $brand->remove();
    drupal_goto('/admin/config/user-interface/brands/');
  }
}

/**
 * Cancel button for delete item form.
 */
function brand_form_delete_item_cancel() {
  $arguments = explode('/', $_GET['q']);
  $machine_name = $arguments[4];
  if (is_numeric((int) $arguments[5])) {
    $timestamp = (int) $arguments[5];
  }
  if (isset($timestamp, $machine_name)) {
    drupal_goto("/admin/config/user-interface/brands/{$machine_name}/{$timestamp}");
  }
}
