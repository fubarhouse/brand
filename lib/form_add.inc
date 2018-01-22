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
  $brand = new Brand($form_state['values']['machine_name']);
  $options = array(
    'title' => $form_state['values']['title'],
    'machine_name' => $form_state['values']['machine_name'],
    'description' => $form_state['values']['description'],
    'path_assets' => $form_state['values']['file-system'],
    'assets_inherit' => $form_state['values']['inheritance'],
    'meta_chrome' => $form_state['values']['chrome_edge'],
    'meta_viewport' => $form_state['values']['view_port'],
    'http_robots' => $form_state['values']['robots'],
    'date_created' => $form_state['values']['date_created'],
    'date_start' => new DateTime($form_state['values']['date_start']['year'] . '-' .  $form_state['values']['date_start']['month'] . '-' . $form_state['values']['date_start']['day']),
    'date_finish' => new DateTime($form_state['values']['date_finish']['year'] . '-' . $form_state['values']['date_finish']['month'] . '-' . $form_state['values']['date_finish']['day']),
    'date_lock' => $form_state['values']['date_lock'],
    'path_search' => $form_state['values']['search_page'],
    'bid' => (int) $form_state['values']['bid'],
    'rid' => (int) $form_state['values']['rid'],
    'tid' => (int) $form_state['values']['term'],
    'uid' => $user->uid,
    'vid' => (int) $form_state['values']['vocabulary'],
    'paths' => (int) $form_state['values']['paths'],
  );
  $brand->add($form_state['values']['machine_name'], $options);
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