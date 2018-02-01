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

  global $user;
  $title = (isset($form_state['input']['title'])) ? $form_state['input']['title'] : $form_state['values']['title'];
  $brand = new Brand($form_state['values']['machine_name']);
  $start = new DateTime($form_state['values']['date_start']['year'] . '-' .  $form_state['values']['date_start']['month'] . '-' . $form_state['values']['date_start']['day']);
  $finish = new DateTime($form_state['values']['date_finish']['year'] . '-' . $form_state['values']['date_finish']['month'] . '-' . $form_state['values']['date_finish']['day']);
  $options = array(
    'title' => $form_state['values']['title'],
    'machine_name' => $form_state['values']['machine_name'],
    'description' => $form_state['values']['description'],
    'path_visibility' => $form_state['values']['paths'],
    'theme' => $form_state['values']['theme'],
    'date_created' => $form_state['values']['date_created'],
    'date_start' => $start->getTimestamp(),
    'date_finish' => $finish->getTimestamp(),
    'date_lock' => $form_state['values']['date_lock'],
    'bid' => (int) $form_state['values']['bid'],
    'rid' => (int) $form_state['values']['rid'],
    'tid' => (int) $form_state['values']['term'],
    'uid' => $user->uid,
    'vid' => (int) $form_state['values']['vocabulary'],
  );
  $brand->add($form_state['values']['machine_name'], $options);

  drupal_set_message("Sucessfully created brand '{$title}'");
  drupal_goto('/admin/config/user-interface/brands');
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