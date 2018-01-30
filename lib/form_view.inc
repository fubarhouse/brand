<?php

/**
 * Implements hook_form().
 *
 * @inheritdoc
 */
function brand_view_form($form, $form_state) {
  $arguments = explode('/', $_GET['q']);
  $machine_name = $arguments[4];
  $timestamp = $arguments[5];
  $brand = new Brand($machine_name, $timestamp);
  $form = array_merge($form, brand_get_universal_form());
  $term = taxonomy_term_load($brand::$Brand->tid);

  $form['basic']['title']['#value'] = $brand::$Brand->title;
  $form['basic']['machine_name']['#value'] = $brand::$Brand->machine_name;
  $form['basic']['description']['#value'] = $brand::$Brand->description;
  $form['assets']['theme']['#value'] = $brand::$Brand->theme;
  $start_date = getdate($brand::$Brand->date_start);
  $form['dates']['date_start']['#value'] = array(
    'year' => $start_date['year'],
    'month' => $start_date['mon'],
    'day' => $start_date['mday'],
  );
  $finish_date = getdate($brand::$Brand->date_finish);
  $form['dates']['date_finish']['#value'] = array(
    'year' => $finish_date['year'],
    'month' => $finish_date['mon'],
    'day' => $finish_date['mday'],
  );
  $form['dates']['date_lock']['#value'] = $brand::$Brand->date_lock;
  $form['book']['bid']['#value'] = $brand::$Brand->bid;
  $form['role']['rid']['#value'] = $brand::$Brand->rid;
  $form['taxonomy']['vocabulary']['#value'] = $brand::$Brand->vid;
  if ((int) $brand::$Brand->tid > 0) {
    $form['taxonomy']['term']['#options'] = array(
      $term->tid => $term->name,
    );
    $form['taxonomy']['term']['#value'] = $term->name;
  }
  $form['visibility']['paths']['#value'] = $brand::$Brand->path_visibility;

  $form['basic']['title']['#disabled'] = TRUE;
  $form['basic']['machine_name']['#disabled'] = TRUE;
  $form['basic']['machine_name']['#access'] = FALSE;
  $form['basic']['description']['#disabled'] = TRUE;

  $form['assets']['theme']['#disabled'] = TRUE;

  $form['dates']['date_created']['#disabled'] = TRUE;
  $form['dates']['date_start']['#disabled'] = TRUE;
  $form['dates']['date_finish']['#disabled'] = TRUE;
  $form['dates']['date_lock']['#disabled'] = TRUE;

  $form['book']['bid']['#disabled'] = TRUE;
  $form['role']['rid']['#disabled'] = TRUE;
  $form['taxonomy']['vocabulary']['#disabled'] = TRUE;
  $form['taxonomy']['term']['#disabled'] = TRUE;
  $form['visibility']['paths']['#disabled'] = TRUE;

  return $form;
}

/**
 * Implements hook_form_submit().
 *
 * @inheritdoc
 */
function brand_view_form_submit($form, $form_state) {

}

/**
 * Implements hook_form_validate().
 *
 * @inheritdoc
 */
function brand_view_form_validate($form, $form_state) {

}