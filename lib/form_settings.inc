<?php

/**
 * @file
 * Form functions and callbacks for the admin settings page.
 */

/**
 * Remove submit function
 */
function brand_admin_settings_form_remove($form, &$form_state) {
  $delta_remove = $form_state['triggering_element']['#parents'][2];
  $k = array_search($delta_remove, $form_state['field_deltas']);
  unset($form_state['field_deltas'][$k]);

  $form_state['rebuild'] = TRUE;
  drupal_get_messages();
}
/**
 * Remove callback.
 */
function brand_admin_settings_form_callback($form, &$form_state) {
  return $form['field_container']['themes'];
}

/**
 * Add submit function.
 */
function brand_admin_settings_form_add($form, &$form_state) {
  $form_state['field_deltas'][] = count($form_state['field_deltas']) > 1 ? max($form_state['field_deltas']) + 1 : 1;
  $form_state['rebuild'] = TRUE;
  drupal_get_messages();
}

function brand_admin_settings_form_submit($form, $form_state) {
  $inputs = $form_state['input']['field_container']['themes'];
  $dd = isset($form_state['input']['field_container']['themes']['disabled_themes']) ? $form_state['input']['field_container']['themes']['disabled_themes'] : $form_state['values']['field_container']['themes']['disabled_themes'];
  $results = array();
  foreach ($inputs as $input) {
    if (isset($input['theme'])) {
      $results[] = $input['theme'];
    }
  }
  variable_set('brand_allowed_themes', $results);
  variable_set('brand_disable_checking', $dd);
}

function brand_admin_settings_form($form, &$form_state) {
  $form['field_container'] = [
    '#type' => 'container',
    '#weight' => 80,
    '#tree' => TRUE,
  ];

  // Get current values and quickly sanitize the indexes.
  $values = variable_get('brand_allowed_themes', array(0));
  $processed_values = array();
  foreach ($values as $value) {
    $processed_values[] = $value;
  }
  if (count($processed_values) - 1 < 0) {
    $count = 0;
  }
  else {
    $count = count($processed_values) - 1;
  }

  $form_state['field_deltas'] = isset($form_state['field_deltas']) ? $form_state['field_deltas'] : range(0, $count);
  $_themes = list_themes();
  $themes = array('' => '');
  foreach ($_themes as $theme) {
    $themes[$theme->name] = $theme->name;
  }

  $form['field_container']['themes'] = [
    '#title' => 'Allowed themes',
    '#description' => t('Themes configured for allowed use on this module are declared below.'),
    '#type' => 'fieldset',
    '#prefix' => '<div id="js-ajax-elements-wrapper">',
    '#suffix' => '</div>',
  ];

  $form['field_container']['themes']['disabled_themes'] = [
    '#type' => 'checkbox',
    '#title' => t('Disable theme control'),
    '#description' => t('Disable the mechanism which restricts the available themes.'),
    '#default_value' => variable_get('brand_disable_checking', 0),
  ];

  foreach ($form_state['field_deltas'] as $delta) {

    $field_value = isset($processed_values[$delta]) ? $processed_values[$delta] : NULL;

    $form['field_container']['themes'][$delta] = [
      '#type' => 'container',
      '#attributes' => [
        'class' => ['container-inline'],
      ],
      '#tree' => TRUE,
    ];

    $form['field_container']['themes'][$delta]['theme'] = [
      '#type' => 'select',
      '#title' => 'Allowed theme #' . $delta,
      '#default_value' => NULL,
      '#options' => $themes,
    ];

    if (isset($themes[$field_value])) {
      $form['field_container']['themes'][$delta]['theme']['#value'] = $themes[$field_value];
    }

    $form['field_container']['themes'][$delta]['remove'] = [
      '#type' => 'submit',
      '#value' => t('Remove'),
      '#submit' => ['brand_admin_settings_form_remove'],
      '#ajax' => [
        'callback' => 'brand_admin_settings_form_callback',
        'wrapper' => 'js-ajax-elements-wrapper',
      ],
      '#weight' => 50,
      '#attributes' => [
        'class' => ['button-small'],
      ],
      '#name' => 'remove_theme_' . $delta,
    ];
  }

  // Submit buttons.
  $form['field_container']['themes']['add'] = [
    '#type' => 'submit',
    '#value' => t('Add one more'),
    '#submit' => ['brand_admin_settings_form_add'],
    '#ajax' => [
      'callback' => 'brand_admin_settings_form_callback',
      'wrapper' => 'js-ajax-elements-wrapper',
    ],
    '#weight' => 100,
  ];

  $form['submit'] = [
    '#type' => 'submit',
    '#value' => t('Submit'),
    '#submit' => ['brand_admin_settings_form_submit'],
    '#weight' => 150,
  ];

  return $form;
}
