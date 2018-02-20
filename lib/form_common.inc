<?php

/**
 * @file
 * Common form rendering functions for the Brand module.
 */

/**
 * Get an associative array of terms.
 *
 * @param int $vid
 *   The optional vocabulary ID to choose.
 *
 * @return array
 *   An associative array of terms.
 */
function brand_form_get_terms($vid = NULL) {
  // Get and store a key => value strucured array with
  // the VID containing the term name and term id.
  $vocabularies = taxonomy_get_vocabularies();
  $results = array();
  foreach ((array) $vocabularies as $vocabulary) {
    $terms = taxonomy_get_tree($vocabulary->vid);
    foreach ($terms as $term) {
      $results[$vocabulary->vid][0] = 'Not selected';
      $results[$vocabulary->vid][$term->tid] = $term->name;
    }
  }
  if (!empty($results)) {
    if (NULL !== $vid && (int) $vid > 0) {
      return $results[$vid];
    }
    return $results;
  }
  else {
    return array();
  }
}

/**
 * Change the available taxonomy terms after changing the vocabulary.
 *
 * @param array $form
 *   The form array.
 * @param array $form_state
 *   The form state array.
 *
 * @return string
 *   The rendered form component for the term component.
 */
function brand_form_vocabulary_callback($form, &$form_state) {
  $arguments = explode('/', $_GET['q']);
  $all_terms = brand_form_get_terms();
  $selectable_terms = $all_terms[$form_state['input']['vocabulary']];
  if ((int) $form_state['input']['vocabulary'] > 0) {
    $form['taxonomy']['term']['#options'] = $selectable_terms;
    form_set_value($form['taxonomy']['term'], '0', $form_state);
  }
  else {
    form_set_value($form['taxonomy']['term'], '0', $form_state);
    $form['taxonomy']['term']['#options'] = array(
      0 => 'Vocabulary not selected.',
    );
  }
  $form_state['rebuild'] = TRUE;
  return render($form['taxonomy']['term']);
}

/**
 * Cancel button for form.
 */
function brand_form_cancel() {
  $arguments = explode('/', $_GET['q']);
  $machine_name = $arguments[4];
  if (is_numeric((int) $arguments[5])) {
    $timestamp = (int) $arguments[5];
  }
  if (isset($timestamp) && isset($machine_name)) {
    drupal_goto("/admin/config/user-interface/brands/{$machine_name}/");
  }
  elseif (isset($machine_name)) {
    drupal_goto("/admin/config/user-interface/brands/");
  }
}

/**
 * Returns a standardized $form object.
 *
 * To be used as a parameter to array_merge().
 * This may or may not include options , values
 * or default values for each field.
 */
function brand_get_universal_form() {
  $form = array();
  $theme_restrictions = (int) variable_get('brand_disable_checking', 0);
  if ($theme_restrictions === 1) {
    $all_themes = list_themes();
    $themes = array(
      'none' => 'None selected',
    );
    foreach ($all_themes as $name => $theme) {
      if ((int) $theme->status === 1) {
        $themes[$name] = $name;
      }
    }
  } else if ($theme_restrictions === 0) {
    $all_themes = brand_get_allowed_themes();
    $drupal_themes = list_themes();
    $themes = array(
      'none' => 'None selected',
    );
    foreach ($all_themes as $name => $theme) {
      if ((int) $drupal_themes[$theme]->status === 1) {
        $themes[$theme] = $theme;
      }
    }
  }

  if (module_exists('book')) {
    $book_raw = book_get_books();
    $books = array(
      0 => 'None',
    );
    foreach ($book_raw as $key => $value) {
      $books[$key] = $book_raw[$key]['title'];
    }
  }

  if (module_exists('taxonomy')) {
    $vocabs = taxonomy_get_vocabularies();
    $vocabularies = array(
      0 => 'Not selected',
    );
    foreach ((array) $vocabs as $vocabulary) {
      $vocabularies[$vocabulary->vid] = $vocabulary->name;
    }
  }

  /* Declare the vertical tab groups. */

  $form['vtabs'] = array(
    '#type' => 'vertical_tabs',
  );

  $form['basic'] = array(
    '#type' => 'fieldset',
    '#title' => t('General'),
    '#group' => 'vtabs',
  );

  $form['assets'] = array(
    '#type' => 'fieldset',
    '#title' => t('Assets'),
    '#group' => 'vtabs',
  );

  $form['dates'] = array(
    '#type' => 'fieldset',
    '#title' => t('Dates'),
    '#group' => 'vtabs',
  );

  if (module_exists('book')) {
    $form['book'] = array(
      '#type' => 'fieldset',
      '#title' => t('Book'),
      '#group' => 'vtabs',
    );
  }

  $form['role'] = array(
    '#type' => 'fieldset',
    '#title' => t('Role'),
    '#group' => 'vtabs',
  );

  if (module_exists('taxonomy')) {
    $form['taxonomy'] = array(
      '#type' => 'fieldset',
      '#title' => t('Taxonomy'),
      '#group' => 'vtabs',
    );
  }

  $form['visibility'] = array(
    '#type' => 'fieldset',
    '#title' => t('Visibility'),
    '#group' => 'vtabs',
  );

  /* Declare fields. */

  $form['basic']['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Branding name'),
    '#description' => t("This is the human-readable name associated to the brand.<br />It's only used on administration pages to identify the brand."),
    '#size' => 60,
    '#maxlength' => 128,
    '#required' => TRUE,
  );

  $form['basic']['machine_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Machine name'),
    '#description' => t('The name which Drupal will associate to this brand.<br />This value must be unique, as it is used to discover if the brand should be displayed and to show information in the administration pages.'),
    '#size' => 60,
    '#maxlength' => 128,
    '#required' => TRUE,
  );

  $form['basic']['description'] = array(
    '#type' => 'textarea',
    '#title' => t('Description'),
    '#description' => t('The message associated to this change, which could include details about what changed, who asked for the changes and why the changes are occuring.'),
    '#rows' => 5,
    '#cols' => 5,
    '#maxlength' => 500,
    '#wysiwyg' => FALSE,
    '#format' => 'plain_text',
    '#required' => TRUE,
  );

  $form['assets']['theme'] = array(
    '#type' => 'select',
    '#title' => 'Theme',
    '#description' => t("Which theme do you wish to associate to this brand?<br /><strong>Note</strong>: Choosing a theme that isn't enabled will load the default theme."),
    '#required' => FALSE,
    '#default_value' => 'none',
    '#options' => $themes,
  );

  $form['assets']['weight'] = array(
    '#type' => 'select',
    '#title' => 'Weight',
    '#description' => t('Specify a weight, which will be used to determine if a particular brand should rule out including conflicting brands.'),
    '#required' => FALSE,
  );
  $options = array();
  for ($i = -20; $i <= 20; $i++) {
    $options[(int) $i] = $i;
  };
  $form['assets']['weight']['#options'] = $options;
  $form['assets']['weight']['#default_value'] = 0;

  $date = new DateTime();
  $now = $date->getTimestamp();

  $form['dates']['date_created'] = array(
    '#type' => 'textfield',
    '#title' => t('Creation date'),
    '#description' => t('The timestamp associated to this entry, be it the first entry of a new brand or any subsequent changes.<br />This value represents the timestamp for when this form was generated.'),
    '#required' => TRUE,
    '#disabled' => TRUE,
    '#access' => FALSE,
    '#default_value' => $now,
  );

  $form['dates']['date_start'] = array(
    '#type' => 'date',
    '#title' => t('Start date'),
    '#description' => t('The date in which this brand will become available.<br /><strong>Note</strong>: This will be used in the UNIX timestamp format based upon the configured server time.<br /><strong>Note</strong>: Caches could still prevent the change from happening when expected.'),
    '#required' => TRUE,
  );

  $form['dates']['date_finish'] = array(
    '#type' => 'date',
    '#title' => t('Finish date'),
    '#description' => t('The date in which this brand will stop being available.<br /><strong>Note</strong>: This will be used in the UNIX timestamp format based upon the configured server time.<br /><strong>Note</strong>: Caches could still prevent the change from happening when expected.'),
    '#required' => TRUE,
  );

  $form['dates']['date_lock'] = array(
    '#type' => 'checkbox',
    '#title' => 'Prevent brand expiration',
    '#description' => t('Instead of stopping the availability of a brand, you can continue it indefinitely (until configured otherwise) by checking this option.'),
  );

  if (module_exists('book')) {
    $form['book']['bid'] = array(
      '#type' => 'select',
      '#title' => t('Book'),
      '#description' => t('Apply the branding to a given book - which will change the theme on every page in the book outline.'),
      '#options' => $books,
    );
  }

  $form['role']['rid'] = array(
    '#type' => 'select',
    '#title' => 'User access',
    '#description' => t('Allow the brand to show for the given user role (anonymous or otherwise).'),
    '#options' => user_roles(),
  );

  if (module_exists('taxonomy')) {
    $form['taxonomy']['vocabulary'] = array(
      '#type' => 'select',
      '#title' => 'Select a taxonomy',
      '#description' => t('Choose a vocabulary to filter the term selection input.<br />Choosing a vocabulary has no bearing on the validation checkers which control the display/logic of a brand.'),
      '#options' => $vocabularies,
      '#ajax' => array(
        'callback' => 'brand_form_vocabulary_callback',
        'wrapper' => 'view-display-dropdown',
      ),
    );

    $form['taxonomy']['term'] = array(
      '#type' => 'select',
      '#title' => 'Term',
      '#description' => t('Apply the branding to all content tagged with this term.'),
      '#prefix' => '<div id="view-display-dropdown">',
      '#suffix' => '</div>',
      '#options' => array(
        0 => 'Not selected',
      ),
    );
  }

  $form['visibility']['paths'] = array(
    '#type' => 'textarea',
    '#title' => t('Paths'),
    '#description' => t('Manually enter one or more paths (optionally using globs) to show the branding on.<br /><br />Example:<br /><br />node/1<br />node/2<br />resources/*'),
    '#size' => 60,
    '#maxlength' => 500,
    '#wysiwyg' => TRUE,
    '#format' => 'full_html',
  );

  $form['submit_button'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  $form['cancel_button'] = array(
    '#type' => 'submit',
    '#value' => t('Cancel'),
    '#submit' => array('brand_form_cancel'),
    '#limit_validation_errors' => array(),
  );

  $form['#pre_render'][] = 'vertical_tabs_form_pre_render';

  return $form;
}
