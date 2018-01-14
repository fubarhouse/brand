<?php

/**
 * Implements hook_form().
 *
 * @inheritdoc
 */
function brand_add_form($form, $form_state) {
  return array_merge($form, brand_get_universal_form());
}

/**
 * Implements hook_form_submit().
 *
 * @inheritdoc
 */
function brand_add_form_submit($form, $form_state) {

}

/**
 * Implements hook_form_validate().
 *
 * @inheritdoc
 */
function brand_add_form_validate($form, $form_state) {
  $machine_name = strtolower($form_state['values']['machine_name']);
  if (FALSE !== strpos($form_state['values']['machine_name'], ' ')) {
    form_set_error('machine_name', 'Machine name cannot contain spaces.');
  }
  $results = new Brand($machine_name, NULL);
  if (FALSE !== $results::$Raw) {
    form_set_error('machine_name', 'Machine name is already taken.');
  }
  if (FALSE !== strpos($form_state['values']['machine_name'], ' ')) {
    form_set_error('machine_name', 'Machine name cannot contain spaces.');
  }
  if (FALSE !== strpos($form_state['values']['machine_name'], 'page')) {
    form_set_error('machine_name', 'Machine name cannot contain the term "page".');
  }
  if (FALSE !== strpos($form_state['values']['machine_name'], 'node')) {
    form_set_error('machine_name', 'Machine name cannot contain the term "node".');
  }
}