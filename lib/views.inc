<?php

/**
 * Implements hook_views_pre_render().
 *
 * @inheritdoc
 */
function brand_views_pre_render(&$view) {
  // @TODO: This is a release blocker... :'(
  if ($view->name === 'brands') {
    $ff = $view->argument['machine_name'];
    $arguments = array();
    $newset = array();
    if (isset($_GET['q'])) {
      $arguments = explode('/', $_GET['q']);
    }
    if (isset($_GET['q']) && isset($arguments[4])) {
      foreach ($view->result as $result) {
        if ($result->brand_machine_name === $arguments[4]) {
          $newset[$result->brand_date_created] = $result;
        }
      }
    }
    elseif ($_GET['q'] === 'admin/config/user-interface/brands') {
      foreach ($view->result as $result) {
        $newset[$result->brand_machine_name] = $result;
      }
    }
//    $view->result = $newset;
  }
}

/**
- * Implements hook_views_data().
- *
- * @inheritdoc
- */
function brand_views_data() {
  $table = array(
    'brand' => array(
      'table' => array(
        'group' => 'Brand',
        'base' => array(
          'field' => 'id',
          'title' => 'Brands',
          'help' => 'Table used for Brands',
        ),
      ),

      // Human readable name for the brand.
      'title' => array(
        'title' => t('Name'),
        'help' => t('The human-readable name for the brand.'),
        'field' => array(
          'click sortable' => TRUE,
        ),
        'filter' => array(
          'handler' => 'views_handler_filter_string',
        ),
        'sort' => array(
          'handler' => 'views_handler_sort',
        ),
        'argument' => array(
          'handler' => 'views_handler_argument_string',
        ),
      ),

      // Machine name.
      'machine_name' => array(
        'title' => t('Machine name'),
        'help' => t('The machine name for the brand, which acts like a unique identifier.'),
        'field' => array(
          'click sortable' => TRUE,
        ),
        'filter' => array(
          'handler' => 'views_handler_filter_string',
        ),
        'sort' => array(
          'handler' => 'views_handler_sort',
        ),
        'argument' => array(
          'handler' => 'views_handler_argument_string',
        ),
      ),

      // Date created.
      'date_created' => array(
        'title' => t('Date of creation'),
        'help' => t('The date each row was created.'),
        'field' => array(
          'handler' => 'views_handler_field_date',
          'click sortable' => TRUE,
        ),
        'filter' => array(
          'handler' => 'views_handler_filter_date',
        ),
        'sort' => array(
          'handler' => 'views_handler_sort',
        ),
      ),

      // Date created.
      'date_start' => array(
        'title' => t('Date of start'),
        'help' => t('The date the brand logic allows it to start.'),
        'field' => array(
          'handler' => 'views_handler_field_date',
          'click sortable' => TRUE,
        ),
        'filter' => array(
          'handler' => 'views_handler_filter_date',
        ),
        'sort' => array(
          'handler' => 'views_handler_sort',
        ),
      ),

      // Date created.
      'date_finish' => array(
        'title' => t('Date of finish'),
        'help' => t('The date the brand logic allows it to end.'),
        'field' => array(
          'handler' => 'views_handler_field_date',
          'click sortable' => TRUE,
        ),
        'filter' => array(
          'handler' => 'views_handler_filter_date',
        ),
        'sort' => array(
          'handler' => 'views_handler_sort',
        ),
      ),

      // Visibility.
      'path_visibility' => array(
        'title' => t('Visibility'),
        'help' => t('The paths to select for this brand.'),
        'field' => array(
          'click sortable' => TRUE,
        ),
        'filter' => array(
          'handler' => 'views_handler_filter_string',
        ),
        'sort' => array(
          'handler' => 'views_handler_sort',
        ),
        'argument' => array(
          'handler' => 'views_handler_argument_string',
        ),
      ),

      // Weight.
      'weight' => array(
        'title' => t('Weight'),
        'help' => t('The weight specified for this brand.'),
        'field' => array(
          'click sortable' => TRUE,
        ),
        'filter' => array(
          'handler' => 'views_handler_filter_numeric',
        ),
        'sort' => array(
          'handler' => 'views_handler_sort',
        ),
        'argument' => array(
          'handler' => 'views_handler_argument_numeric',
        ),
      ),

      // Description.
      'description' => array(
        'title' => t('Description'),
        'help' => t('The message associated with this change.'),
        'field' => array(
          'click sortable' => TRUE,
        ),
        'filter' => array(
          'handler' => 'views_handler_filter_string',
        ),
        'sort' => array(
          'handler' => 'views_handler_sort',
        ),
        'argument' => array(
          'handler' => 'views_handler_argument_string',
        ),
      ),

      // Date locking mechanism:
      'date_lock' => array(
        'title' => t('Date locking'),
        'help' => t('Determine if logic should prevent branding from finishing.'),
        'field' => array(
          'handler' => 'views_handler_field_boolean',
          'click sortable' => TRUE,
        ),
        'filter' => array(
          'handler' => 'views_handler_filter_boolean_operator',
          'label' => t('Does not expire?'),
          'type' => 'yes-no',
          'use equal' => TRUE,
        ),
        'sort' => array(
          'handler' => 'views_handler_sort',
        ),
        'argument' => array(
          'handler' => 'views_handler_argument',
        ),
      ),

      // Book:
      'bid' => array(
        'title' => t('Book'),
        'help' => t('The book selected for the entry for the brand.'),
        'field' => array(
          'handler' => 'brand_handler_bid',
          'click sortable' => TRUE,
        ),
        'filter' => array(
          'handler' => 'views_handler_filter_string',
        ),
        'sort' => array(
          'handler' => 'views_handler_sort',
        ),
        'argument' => array(
          'handler' => 'views_handler_argument_numeric',
        ),
      ),

      // Taxonomy:
      'tid' => array(
        'title' => t('Term'),
        'help' => t('The taxonomy term selected for the entry for the brand.'),
        'field' => array(
          'handler' => 'brand_handler_tid',
          'click sortable' => TRUE,
        ),
        'filter' => array(
          'handler' => 'views_handler_filter_string',
        ),
        'sort' => array(
          'handler' => 'views_handler_sort',
        ),
        'argument' => array(
          'handler' => 'views_handler_argument_numeric',
        ),
      ),

      // Role:
      'rid' => array(
        'title' => t('Role'),
        'help' => t('The user role selected for the entry for the brand.'),
        'field' => array(
          'handler' => 'views_handler_field_user_roles',
          'click sortable' => TRUE,
        ),
        'filter' => array(
          'handler' => 'views_handler_filter_user_roles',
        ),
        'sort' => array(
          'handler' => 'views_handler_sort',
        ),
        'argument' => array(
          'handler' => 'views_handler_argument_numeric',
        ),
      ),

      // User:
      'uid' => array(
        'title' => t('User'),
        'help' => t('The user that created the entry for the brand.'),
        'field' => array(
          'handler' => 'views_handler_field_user_name',
          'click sortable' => TRUE,
        ),
        'filter' => array(
          'handler' => 'views_handler_filter_user_name',
        ),
        'sort' => array(
          'handler' => 'views_handler_sort',
        ),
        'argument' => array(
          'handler' => 'views_handler_argument_numeric',
        ),
      ),

      // Vocabulary:
      'vid' => array(
        'title' => t('Vocabulary'),
        'help' => t('The vocabulary for the entry for the brand.'),
        'field' => array(
          'handler' => 'brand_handler_vid',
          'click sortable' => TRUE,
        ),
        'filter' => array(
          'handler' => 'views_handler_filter_string',
        ),
        'sort' => array(
          'handler' => 'views_handler_sort',
        ),
        'argument' => array(
          'handler' => 'views_handler_argument_numeric',
        ),
      ),

    ),
  );
  return $table;
}

/**
 * Implements hook_views_default_views().
 *
 * @inheritdoc
 */
function brand_views_default_views() {

  $view = new view();
  $view->name = 'brands';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'brand';
  $view->human_name = 'Brands';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Brands';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'brand visibility';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Field: UNIX Timestamp */
  $handler->display->display_options['fields']['date_created_1']['id'] = 'date_created_1';
  $handler->display->display_options['fields']['date_created_1']['table'] = 'brand';
  $handler->display->display_options['fields']['date_created_1']['field'] = 'date_created';
  $handler->display->display_options['fields']['date_created_1']['ui_name'] = 'UNIX Timestamp';
  $handler->display->display_options['fields']['date_created_1']['label'] = 'UNIX TIMESTAMP';
  $handler->display->display_options['fields']['date_created_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['date_created_1']['date_format'] = 'custom';
  $handler->display->display_options['fields']['date_created_1']['custom_date_format'] = 'U';
  $handler->display->display_options['fields']['date_created_1']['second_date_format'] = 'rss';
  /* Field: Brand: Machine name */
  $handler->display->display_options['fields']['machine_name']['id'] = 'machine_name';
  $handler->display->display_options['fields']['machine_name']['table'] = 'brand';
  $handler->display->display_options['fields']['machine_name']['field'] = 'machine_name';
  $handler->display->display_options['fields']['machine_name']['label'] = '';
  $handler->display->display_options['fields']['machine_name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['machine_name']['element_label_colon'] = FALSE;
  /* Field: Brand: Name */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'brand';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['text'] = '[title]';
  $handler->display->display_options['fields']['title']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['path'] = 'admin/config/user-interface/brands/[machine_name]';
  /* Field: Brand: Date of creation */
  $handler->display->display_options['fields']['date_created']['id'] = 'date_created';
  $handler->display->display_options['fields']['date_created']['table'] = 'brand';
  $handler->display->display_options['fields']['date_created']['field'] = 'date_created';
  $handler->display->display_options['fields']['date_created']['label'] = 'Updated';
  $handler->display->display_options['fields']['date_created']['date_format'] = 'short';
  $handler->display->display_options['fields']['date_created']['second_date_format'] = 'rss';
  /* Field: Brand: Date of start */
  $handler->display->display_options['fields']['date_start']['id'] = 'date_start';
  $handler->display->display_options['fields']['date_start']['table'] = 'brand';
  $handler->display->display_options['fields']['date_start']['field'] = 'date_start';
  $handler->display->display_options['fields']['date_start']['label'] = 'Starts';
  $handler->display->display_options['fields']['date_start']['date_format'] = 'short';
  $handler->display->display_options['fields']['date_start']['second_date_format'] = 'rss';
  /* Field: Brand: Date of finish */
  $handler->display->display_options['fields']['date_finish']['id'] = 'date_finish';
  $handler->display->display_options['fields']['date_finish']['table'] = 'brand';
  $handler->display->display_options['fields']['date_finish']['field'] = 'date_finish';
  $handler->display->display_options['fields']['date_finish']['label'] = 'Finishes';
  $handler->display->display_options['fields']['date_finish']['date_format'] = 'short';
  $handler->display->display_options['fields']['date_finish']['second_date_format'] = 'rss';
  /* Sort criterion: Brand: Weight */
  $handler->display->display_options['sorts']['weight']['id'] = 'weight';
  $handler->display->display_options['sorts']['weight']['table'] = 'brand';
  $handler->display->display_options['sorts']['weight']['field'] = 'weight';
  /* Sort criterion: Brand: Machine name */
  $handler->display->display_options['sorts']['machine_name']['id'] = 'machine_name';
  $handler->display->display_options['sorts']['machine_name']['table'] = 'brand';
  $handler->display->display_options['sorts']['machine_name']['field'] = 'machine_name';
  /* Sort criterion: Brand: Date of creation */
  $handler->display->display_options['sorts']['date_created']['id'] = 'date_created';
  $handler->display->display_options['sorts']['date_created']['table'] = 'brand';
  $handler->display->display_options['sorts']['date_created']['field'] = 'date_created';
  $handler->display->display_options['sorts']['date_created']['order'] = 'DESC';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['empty'] = FALSE;
  /* No results behavior: Global: Unfiltered text */
  $handler->display->display_options['empty']['area_text_custom']['id'] = 'area_text_custom';
  $handler->display->display_options['empty']['area_text_custom']['table'] = 'views';
  $handler->display->display_options['empty']['area_text_custom']['field'] = 'area_text_custom';
  $handler->display->display_options['empty']['area_text_custom']['empty'] = TRUE;
  $handler->display->display_options['empty']['area_text_custom']['content'] = '<p>Brands are small sub-themes which have specific logic to expose them during a given duration.</p>
<p>You can apply a brand using various components which make for good structural design, such as books, taxonomy terms or paths.</p>
<p>So why not create one using the link above?</p>';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: UNIX Timestamp */
  $handler->display->display_options['fields']['date_created_1']['id'] = 'date_created_1';
  $handler->display->display_options['fields']['date_created_1']['table'] = 'brand';
  $handler->display->display_options['fields']['date_created_1']['field'] = 'date_created';
  $handler->display->display_options['fields']['date_created_1']['ui_name'] = 'UNIX Timestamp';
  $handler->display->display_options['fields']['date_created_1']['label'] = '';
  $handler->display->display_options['fields']['date_created_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['date_created_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['date_created_1']['date_format'] = 'custom';
  $handler->display->display_options['fields']['date_created_1']['custom_date_format'] = 'U';
  $handler->display->display_options['fields']['date_created_1']['second_date_format'] = 'rss';
  /* Field: Brand: Machine name */
  $handler->display->display_options['fields']['machine_name']['id'] = 'machine_name';
  $handler->display->display_options['fields']['machine_name']['table'] = 'brand';
  $handler->display->display_options['fields']['machine_name']['field'] = 'machine_name';
  $handler->display->display_options['fields']['machine_name']['label'] = '';
  $handler->display->display_options['fields']['machine_name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['machine_name']['element_label_colon'] = FALSE;
  /* Field: Brand: Name */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'brand';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['text'] = '[title]';
  $handler->display->display_options['fields']['title']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['path'] = 'admin/config/user-interface/brands/[machine_name]/';
  /* Field: Brand: Date of creation */
  $handler->display->display_options['fields']['date_created']['id'] = 'date_created';
  $handler->display->display_options['fields']['date_created']['table'] = 'brand';
  $handler->display->display_options['fields']['date_created']['field'] = 'date_created';
  $handler->display->display_options['fields']['date_created']['label'] = 'Updated';
  $handler->display->display_options['fields']['date_created']['date_format'] = 'short';
  $handler->display->display_options['fields']['date_created']['second_date_format'] = 'rss';
  $handler->display->display_options['path'] = 'admin/config/user-interface/brands';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Brands';
  $handler->display->display_options['menu']['description'] = 'Configuration page for brands';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: UNIX Timestamp */
  $handler->display->display_options['fields']['date_created_1']['id'] = 'date_created_1';
  $handler->display->display_options['fields']['date_created_1']['table'] = 'brand';
  $handler->display->display_options['fields']['date_created_1']['field'] = 'date_created';
  $handler->display->display_options['fields']['date_created_1']['ui_name'] = 'UNIX Timestamp';
  $handler->display->display_options['fields']['date_created_1']['label'] = 'UNIX';
  $handler->display->display_options['fields']['date_created_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['date_created_1']['date_format'] = 'custom';
  $handler->display->display_options['fields']['date_created_1']['custom_date_format'] = 'U';
  $handler->display->display_options['fields']['date_created_1']['second_date_format'] = 'rss';
  /* Field: Brand: Machine name */
  $handler->display->display_options['fields']['machine_name']['id'] = 'machine_name';
  $handler->display->display_options['fields']['machine_name']['table'] = 'brand';
  $handler->display->display_options['fields']['machine_name']['field'] = 'machine_name';
  $handler->display->display_options['fields']['machine_name']['label'] = '';
  $handler->display->display_options['fields']['machine_name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['machine_name']['element_label_colon'] = FALSE;
  /* Field: Brand: Name */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'brand';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['text'] = '[title]';
  $handler->display->display_options['fields']['title']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['path'] = 'admin/config/user-interface/brands/[machine_name]/[date_created_1]';
  /* Field: Brand: Date of creation */
  $handler->display->display_options['fields']['date_created']['id'] = 'date_created';
  $handler->display->display_options['fields']['date_created']['table'] = 'brand';
  $handler->display->display_options['fields']['date_created']['field'] = 'date_created';
  $handler->display->display_options['fields']['date_created']['label'] = 'Date';
  $handler->display->display_options['fields']['date_created']['date_format'] = 'short';
  $handler->display->display_options['fields']['date_created']['second_date_format'] = 'rss';
  /* Field: Brand: Description */
  $handler->display->display_options['fields']['description']['id'] = 'description';
  $handler->display->display_options['fields']['description']['table'] = 'brand';
  $handler->display->display_options['fields']['description']['field'] = 'description';
  $handler->display->display_options['fields']['description']['label'] = 'Message';
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Brand: Date of creation */
  $handler->display->display_options['sorts']['date_created']['id'] = 'date_created';
  $handler->display->display_options['sorts']['date_created']['table'] = 'brand';
  $handler->display->display_options['sorts']['date_created']['field'] = 'date_created';
  $handler->display->display_options['sorts']['date_created']['order'] = 'DESC';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Brand: Machine name */
  $handler->display->display_options['arguments']['machine_name']['id'] = 'machine_name';
  $handler->display->display_options['arguments']['machine_name']['table'] = 'brand';
  $handler->display->display_options['arguments']['machine_name']['field'] = 'machine_name';
  $handler->display->display_options['arguments']['machine_name']['default_action'] = 'default';
  $handler->display->display_options['arguments']['machine_name']['default_argument_type'] = 'raw';
  $handler->display->display_options['arguments']['machine_name']['default_argument_options']['index'] = '4';
  $handler->display->display_options['arguments']['machine_name']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['machine_name']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['machine_name']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['machine_name']['limit'] = '0';
  $handler->display->display_options['path'] = 'admin/config/user-interface/brands/%';
  $handler->display->display_options['menu']['title'] = 'Brand dashboard';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  $views[$view->name] = $view;
  return $views;
}