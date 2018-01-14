<?php

/**
 * Implements hook_form().
 *
 * @inheritdoc
 */
function brand_add_form($form, $form_state) {

    $form['vtabs'] = array(
        '#type' => 'vertical_tabs'
    );

    $form['basic'] = array(
        '#type' => 'fieldset',
        '#title' => t('General'),
        '#description' => t('Description'),
        '#group' => 'vtabs',
    );

    $form['dates'] = array(
        '#type' => 'fieldset',
        '#title' => t('Dates'),
        '#description' => t('Description'),
        '#group' => 'vtabs',
    );

    $form['conditions'] = array(
        '#type' => 'fieldset',
        '#title' => t('Conditions'),
        '#description' => t('Description'),
        '#group' => 'vtabs',
    );

    $form['basic']['title'] = array(
      '#type' => 'textfield',
      '#title' => t('Campaign name'),
      '#size' => 60,
      '#maxlength' => 128,
      '#required' => TRUE,
      '#default_value' => NULL,
    );

    $form['basic']['machine_name'] = array(
      '#type' => 'textfield',
      '#title' => t('Machine name'),
      '#size' => 60,
      '#maxlength' => 128,
      '#required' => TRUE,
      '#default_value' => NULL,
    );

    $form['basic']['description'] = array(
        '#type' => 'textarea',
        '#title' => t('Description'),
        '#description' => t('The  message associated to this entry to the brand.'),
        '#default_value' => t('Initial brand creation.'),
        '#rows' => 5,
        '#cols' => 5,
        '#maxlength' => 500,
        '#wysiwyg' => FALSE,
        '#format' => 'plain_text',
        '#required' => TRUE,
    );

    $date = new DateTime();
    $now = $date->getTimestamp();

    $form['dates']['date_created'] = array(
        '#type' => 'textfield',
        '#title' => t('Creation date'),
        '#description' => t('The starting date of the campaign'),
        '#required' => TRUE,
        '#default_value' => $now,
        '#disabled' => TRUE,
    );

    $form['dates']['date_start'] = array(
        '#type' => 'date',
        '#title' => t('Start date'),
        '#description' => t('The starting date of the campaign'),
        '#required' => TRUE,
        '#default_value' => NULL,
    );

    $form['dates']['date_finish'] = array(
        '#type' => 'date',
        '#title' => t('Start date'),
        '#description' => t('The starting date of the campaign'),
        '#required' => TRUE,
        '#default_value' => NULL,
    );

    $form['submit_button'] = array(
        '#type' => 'submit',
        '#value' => t('Save'),
    );

    $form['#pre_render'][] = 'vertical_tabs_form_pre_render';
    return $form;
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

}