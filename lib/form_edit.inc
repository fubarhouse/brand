<?php

/**
 * Implements hook_form().
 *
 * @inheritdoc
 */
function brand_edit_form($form, $form_state) {
  $arguments = explode('/', $_SERVER['HTTP_REFERER']);
  $machine_name = $arguments[7];
  $brands = new Brand($machine_name);
  $brand = $brands::$Brand;
  $terms = brand_form_get_terms($brand->vid);
  $start_date = getdate($brand->date_start);
  $finish_date = getdate($brand->date_finish);

  $form = brand_get_universal_form();
  $form['basic']['title']['#value'] = $brand->title;
  $form['basic']['machine_name']['#value'] = $brand->machine_name;
  $form['basic']['machine_name']['#disabled'] = TRUE;
  $form['assets']['file-system']['#value'] = $brand->path_assets;
  $form['assets']['theme']['#value'] = $brand->theme;
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
  $form['taxonomy']['term']['#options'] = $terms;
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
  $start_date = (isset($form_state['input']['date_start'])) ? new DateTime($form_state['input']['date_start']['year'] . '-' .  $form_state['input']['date_start']['month'] . '-' . $form_state['input']['date_start']['day']) : new DateTime($form_state['values']['date_start']['year'] . '-' .  $form_state['values']['date_start']['month'] . '-' . $form_state['values']['date_start']['day']);
  $finish_date = (isset($form_state['input']['date_finish'])) ? new DateTime($form_state['input']['date_finish']['year'] . '-' .  $form_state['input']['date_finish']['month'] . '-' . $form_state['input']['date_finish']['day']) : new DateTime($form_state['values']['date_finish']['year'] . '-' .  $form_state['values']['date_finish']['month'] . '-' . $form_state['values']['date_finish']['day']);
  $title = (isset($form_state['input']['title'])) ? $form_state['input']['title'] : $form_state['values']['title'];
  $machine_name = (isset($form_state['input']['machine_name'])) ? $form_state['input']['machine_name'] : $form_state['values']['machine_name'];
  $options = array(
    'title' => isset($form_state['input']['title']) ? $form_state['input']['title'] : $form_state['values']['title'],
    'machine_name' => isset($form_state['input']['machine_name']) ? $form_state['input']['machine_name'] : $form_state['values']['machine_name'],
    'description' => isset($form_state['input']['description']) ? $form_state['input']['description'] : $form_state['values']['description'],
    'path_assets' => isset($form_state['input']['file-system']) ? $form_state['input']['file-system'] : $form_state['values']['title'],
    'theme' => isset($form_state['input']['theme']) ? $form_state['input']['theme'] : $form_state['values']['theme'],
    'assets_inherit' => isset($form_state['input']['inheritance']) ? $form_state['input']['inheritance'] : $form_state['values']['inheritance'],
    'meta_chrome' => isset($form_state['input']['chrome_edge']) ? $form_state['input']['chrome_edge'] : $form_state['values']['chrome_edge'],
    'meta_viewport' => isset($form_state['input']['viewport']) ? $form_state['input']['viewport'] : $form_state['values']['viewport'],
    'http_robots' => isset($form_state['input']['robots']) ? $form_state['input']['tobots'] : $form_state['values']['robots'],
    'date_created' => isset($form_state['input']['date_created']) ? $form_state['input']['date_created'] : $form_state['values']['date_created'],
    'date_start' => $start_date->getTimestamp(),
    'date_finish' => $finish_date->getTimestamp(),
    'date_lock' => isset($form_state['input']['date_lock']) ? $form_state['input']['date_lock'] : $form_state['values']['date_lock'],
    'path_search' => isset($form_state['input']['search_page']) ? $form_state['input']['search_page'] : $form_state['values']['search_page'],
    'bid' => isset($form_state['input']['bid']) ? $form_state['input']['bid'] : $form_state['values']['bid'],
    'rid' => isset($form_state['input']['rid']) ? $form_state['input']['rid'] : $form_state['values']['rid'],
    'tid' => isset($form_state['input']['term']) ? $form_state['input']['term'] : $form_state['values']['term'],
    'uid' => $user->uid,
    'vid' => isset($form_state['input']['vocabulary']) ? $form_state['input']['vocabulary'] : $form_state['values']['vocabulary'],
    'path_visibility' => isset($form_state['input']['paths']) ? $form_state['input']['paths'] : $form_state['values']['paths'],
  );
  $brand->add($form_state['values']['machine_name'], $options);

  drupal_set_message("Sucessfully updated brand '{$title}'");
  drupal_goto("/admin/config/user-interface/brands/{$machine_name}");
}

/**
 * Implements hook_form_validate().
 *
 * @inheritdoc
 */
function brand_edit_form_validate($form, $form_state) {
  // @TODO: Find out if nothing has changed, and report a form error if needed.
}