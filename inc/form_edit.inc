<?php

/**
 * Implements hook_form().
 *
 * @inheritdoc
 */
function brand_edit_form($form, $form_state) {
  $machine_name = 'hhh';
  $brand = new Brand($machine_name, 1516014539);
  $form = array_merge($form, brand_get_universal_form());

  $form['basic']['title']['#value'] = $brand::$Brand->title;
  $form['basic']['machine_name']['#value'] = $brand::$Brand->machine_name;
  $form['basic']['description']['#value'] = $brand::$Brand->description;

  $form['assets']['file-system']['#value'] = $brand::$Brand->path_assets;
  $form['assets']['inheritance']['#value'] = $brand::$Brand->assets_inherit;
  $form['assets']['chrome_edge']['#value'] = $brand::$Brand->meta_chrome;
  $form['assets']['viewport']['#value'] = $brand::$Brand->meta_viewport;
  $form['assets']['robots']['#value'] = $brand::$Brand->http_robots;

  $form['dates']['date_created']['#value'] = $brand::$Brand->date_created;
  $form['dates']['date_lock']['#value'] = $brand::$Brand->date_lock;

  $start = getdate($form['dates']['date_start']['#default_value']);
  $form['dates']['date_start']['#value']['year'] = $start['year'];
  $form['dates']['date_start']['#value']['mon'] = $start['mon'];
  $form['dates']['date_start']['#value']['day'] = $start['day'];

  $finish = getdate($form['dates']['date_finish']['#default_value']);
  $form['dates']['date_finish']['#value']['year'] = $finish['year'];
  $form['dates']['date_finish']['#value']['mon'] = $finish['mon'];
  $form['dates']['date_finish']['#value']['day'] = $finish['day'];

  $form['basic']['machine_name']['#disabled'] = TRUE;


  return $form;
}

/**
 * Implements hook_form_submit().
 *
 * @inheritdoc
 */
function brand_edit_form_submit($form, $form_state) {

}

/**
 * Implements hook_form_validate().
 *
 * @inheritdoc
 */
function brand_edit_form_validate($form, $form_state) {

}