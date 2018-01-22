<?php

/**
 * Returns a standardized $form object.
 *
 * To be used as a parameter to array_merge().
 * This may or may not include options , values
 * or default values for each field.
 */
function brand_get_universal_form() {
  $form = array();


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
    '#type' => 'vertical_tabs'
  );

  $form['basic'] = array(
    '#type' => 'fieldset',
    '#title' => t('General'),
    '#description' => t('Description'),
    '#group' => 'vtabs',
  );

  $form['assets'] = array(
    '#type' => 'fieldset',
    '#title' => t('Assets'),
    '#description' => t('Assets'),
    '#group' => 'vtabs',
  );

  $form['dates'] = array(
    '#type' => 'fieldset',
    '#title' => t('Dates'),
    '#description' => t('Description'),
    '#group' => 'vtabs',
  );

  $form['search'] = array(
    '#type' => 'fieldset',
    '#title' => t('Search'),
    '#description' => t('Search'),
    '#group' => 'vtabs',
  );

  if (module_exists('book')) {
    $form['book'] = array(
      '#type' => 'fieldset',
      '#title' => t('Book'),
      '#description' => t('Book'),
      '#group' => 'vtabs',
    );
  }

  $form['role'] = array(
    '#type' => 'fieldset',
    '#title' => t('Role'),
    '#description' => t('Role'),
    '#group' => 'vtabs',
  );

  if (module_exists('taxonomy')) {
    $form['taxonomy'] = array(
      '#type' => 'fieldset',
      '#title' => t('Taxonomy'),
      '#description' => t('Taxonomy'),
      '#group' => 'vtabs',
    );
  }

  $form['visibility'] = array(
    '#type' => 'fieldset',
    '#title' => t('Visibility'),
    '#description' => t('Visibility'),
    '#group' => 'vtabs',
  );

  /* Declare fields. */

  $form['basic']['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Branding name'),
    '#size' => 60,
    '#maxlength' => 128,
    '#required' => TRUE,
  );

  $form['basic']['machine_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Machine name'),
    '#size' => 60,
    '#maxlength' => 128,
    '#required' => TRUE,
  );

  $form['basic']['description'] = array(
    '#type' => 'textarea',
    '#title' => t('Description'),
    '#description' => t('The  message associated to this entry to the brand.'),
    '#rows' => 5,
    '#cols' => 5,
    '#maxlength' => 500,
    '#wysiwyg' => FALSE,
    '#format' => 'plain_text',
    '#required' => TRUE,
  );

  $form['assets']['file-system'] = array(
    '#type' => 'textfield',
    '#title' => 'File system path',
    '#description' => t('The relative path to the assets for the branding.'),
    '#size' => 60,
    '#maxlength' => 128,
  );

  $form['assets']['inheritance'] = array(
    '#type' => 'checkbox',
    '#title' => 'Asset Inheritance',
    '#description' => t('Inherit the stylesheet and javascript assets from the default theme?'),
    '#default_value' => 1,
  );

  $form['assets']['chrome_edge'] = array(
    '#type' => 'checkbox',
    '#title' => 'Chrome Edge',
    '#description' => t('Apply chrome edging to this brand?'),
    '#default_value' => 1,
  );

  $form['assets']['viewport'] = array(
    '#type' => 'checkbox',
    '#title' => 'Viewport defaults',
    '#description' => t('Set viewport defaults to this brand?'),
    '#default_value' => 1,
  );

  $form['assets']['robots'] = array(
    '#type' => 'checkbox',
    '#title' => 'Robots',
    '#description' => t('Add robots HTTP Header to prevent crawlers indexing this brand?'),
    '#default_value' => 0,
  );

  $date = new DateTime();
  $now = $date->getTimestamp();

  $form['dates']['date_created'] = array(
    '#type' => 'textfield',
    '#title' => t('Creation date'),
    '#description' => t('The UNIX timestamp for when this form was created.'),
    '#required' => TRUE,
    '#disabled' => TRUE,
    '#default_value' => $now,
  );

  $form['dates']['date_start'] = array(
    '#type' => 'date',
    '#title' => t('Start date'),
    '#description' => t('The date which the branding should take effect.'),
    '#required' => TRUE,
  );

  $form['dates']['date_finish'] = array(
    '#type' => 'date',
    '#title' => t('Finish date'),
    '#description' => t('The date which the branding should cease to work.'),
    '#required' => TRUE,
  );

  $form['dates']['date_lock'] = array(
    '#type' => 'checkbox',
    '#title' => 'Ignore the finish date?',
    '#description' => t('If selected, the branding will not stop until unchecked.'),
  );

  $form['search']['search_page'] = array(
    '#type' => 'textfield',
    '#title' => t('Search page'),
    '#description' => t('Path to custom search page for pages/nodes affected by the brand.'),
    '#size' => 60,
    '#maxlength' => 128,
    '#required' => FALSE,
  );

  if (module_exists('book')) {
    $form['book']['bid'] = array(
      '#type' => 'select',
      '#title' => t('Book'),
      '#description' => t('Apply this branding to a book.'),
      '#options' => $books,
    );
  }

  $form['role']['rid'] = array(
    '#type' => 'select',
    '#title' => 'User access',
    '#description' => t('User role to confine visibility access to.<br /><strong>Note</strong>: setting this to "anonymous user" will ensure public visibility.'),
    '#options' => user_roles(),
  );

  $form['taxonomy']['vocabulary'] = array(
    '#type' => 'select',
    '#title' => 'Select a taxonomy',
    '#options' => $vocabularies,
//    '#ajax' => array(
//      'callback' => 'unknown_form_vocabulary_change',
//      'wrapper' => 'view-display-dropdown',
//    ),
  );

  $form['taxonomy']['term'] = array(
    '#type' => 'select',
    '#title' => 'Term',
    '#description' => t('Select a term'),
    '#prefix' => '<div id="view-display-dropdown">',
    '#suffix' => '</div>',
    '#options' => array(
      0 => 'Not selected',
    ),
  );

  $form['visibility']['paths'] = array(
    '#type' => 'textarea',
    '#title' => t('Paths'),
    '#description' => t('A list of paths which use this brand.<br /><br />Example:<br /><br />node/1<br />node/2<br />resources/*'),
    '#size' => 60,
    '#maxlength' => 500,
    '#wysiwyg' => TRUE,
    '#format' => 'full_html',
  );

  $form['submit_button'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  $form['#pre_render'][] = 'vertical_tabs_form_pre_render';

  return $form;
}