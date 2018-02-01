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
  $machine_name = $arguments[4];

  $form['disclaimer'] = array(
    '#type' => 'markup',
    '#markup' => t("<p>Are you absolutely sure you wish to proceed with the following?</p><ul><li>Delete all records of brand identified by machine name '{$machine_name}'</li></li></ul><p>This action is not reversible.</p></p>"),
  );
  $form['submit']['no'] = array(
    '#type' => 'submit',
    '#value' => 'No',
  );
  $form['submit']['yes'] = array(
    '#type' => 'submit',
    '#value' => 'Yes',
  );

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
  $brand = new Brand($machine_name, NULL);
  $brand->remove();
  drupal_goto('/admin/config/user-interface/brands');
}