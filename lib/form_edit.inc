<?php

/**
 * Implements hook_form().
 *
 * @inheritdoc
 */
function brand_edit_form($form, $form_state) {
  $brands = new Brand('machine_name_1');
  $brand = $brands::$Brand;
  $start_date = getdate($brand->date_start);
  $finish_date = getdate($brand->date_finish);

  $form = brand_get_universal_form();
  $form['basic']['title']['#value'] = $brand->title;
  $form['basic']['machine_name']['#value'] = $brand->machine_name;
  $form['basic']['machine_name']['#disabled'] = TRUE;
  $form['assets']['file-system']['#value'] = $brand->path_assets;
  $form['assets']['inheritance']['#value'] = $brand->assets_inherit;
  $form['assets']['chrome_edge']['#value'] = $brand->meta_chrome;
  $form['assets']['viewport']['#value'] = $brand->meta_viewport;
  $form['assets']['robots']['#value'] = $brand->http_robots;
  $form['dates']['date_start']['#value'] = array(
    'year' => $start_date['year'],
    'month' => $start_date['mon'],
    'day' => $start_date['mday'],
  );
  $form['dates']['date_finish']['#value'] = array(
    'year' => $finish_date['year'],
    'month' => $finish_date['mon'],
    'day' => $finish_date['mday'],
  );
  $form['dates']['date_lock']['#value'] = $brand->date_lock;
  $form['search']['search_page']['#value'] = $brand->path_search;
  $form['book']['bid']['#value'] = $brand->bid;
  $form['role']['rid']['#value'] = $brand->rid;
  $form['taxonomy']['vocabulary']['#value'] = $brand->vid;
  $form['taxonomy']['term']['#value'] = $brand->tid;
  $form['visibility']['paths']['#value'] = $brand->path_visibility;

  return $form;
}

/**
 * Implements hook_form_submit().
 *
 * @inheritdoc
 */
function brand_edit_form_submit($form, $form_state) {
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
function brand_edit_form_validate($form, $form_state) {
  // @TODO: Find out if nothing has changed, and report a form error if needed.
}