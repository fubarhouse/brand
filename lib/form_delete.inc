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
      '#markup' => t("<p>Are you absolutely sure you wish to proceed with the following?</p><ul><li>Delete record of brand identified by machine name '{$machine_name}' with matching creation timestamp of '{$timestamp}'</li></li></ul><p>This action is not reversible.</p></p>"),
    );
    $form['submit']['no'] = array(
      '#type' => 'submit',
      '#value' => 'No',
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
    drupal_goto('/admin/config/user-interface/brands/'.$machine_name);
  }
  else {
    $brand = new Brand($machine_name, NULL);
    $brand->remove();
    drupal_goto('/admin/config/user-interface/brands/');
  }
}