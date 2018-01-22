<?php

/**
 * @file
 * File for views integration for Brand.
 */

/**
 * Provide the first name only from the name field.
 *
 * @ingroup views_filter_handlers
 */
class brand_handler_bid extends views_handler_field
{
  /**
   * Render the name field.
   */
  public function render($values) {
    $books = book_get_books();
    if ((int)$values->brand_bid > 0) {
      return l($books[$values->brand_bid]['link_title'], '/' . $books[$values->brand_bid]['link_path']);
    } else {
      return 0;
    }
  }
}

/**
 * Provide the first name only from the name field.
 *
 * @ingroup views_filter_handlers
 */
class brand_handler_tid extends views_handler_field {
  /**
   * Render the name field.
   */
  public function render($values) {
    if ($values->brand_tid > 0) {
      $term = taxonomy_term_load($values->brand_tid);
      return $term->name;
    }
    else {
      return '';
    }
  }
}

/**
 * Provide the first name only from the name field.
 *
 * @ingroup views_filter_handlers
 */
class brand_handler_vid extends views_handler_field {
  /**
   * Render the name field.
   */
  public function render($values) {
    if ($values->brand_vid > 0) {
      return taxonomy_get_vocabularies()[$values->brand_vid]->name;
    }
    else {
      return '';
    }
  }
}

/**
 * Implements hook_views_data().
 *
 * @inheritdoc
 */
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

      // Asset inheritance.
      'assets_inherit' => array(
        'title' => t('Asset inheritance'),
        'help' => t('A boolean indicating the status of asset inheritance.'),
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
          'handler' => 'views_handler_argument',
        ),
      ),

      // Chrome edging.
      'meta_chrome' => array(
        'title' => t('Chrome edging'),
        'help' => t('A boolean indicating the status of chrome edging.'),
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
          'handler' => 'views_handler_argument',
        ),
      ),

      // Viewport.
      'meta_viewport' => array(
        'title' => t('Viewport'),
        'help' => t('A boolean indicating the status of viewport.'),
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
          'handler' => 'views_handler_argument',
        ),
      ),

      // HTTP Robots.
      'http_robots' => array(
        'title' => t('Robots'),
        'help' => t('A boolean indicating the status of HTTP Robots.'),
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
          'handler' => 'views_handler_argument',
        ),
      ),

      // Path to assets.
      'path_assets' => array(
        'title' => t('Path of assets'),
        'help' => t('The location of the file system containing assets.'),
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

      // Path to search.
      'path_search' => array(
        'title' => t('Path of search page'),
        'help' => t('The search page for this brand, if configured.'),
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
 * Implements hook_views_pre_render().
 *
 * @inheritdoc
 */
function brand_views_pre_render(&$view) {
  if (NULL !== $_GET['q'] && $_GET['q'] === 'admin/config/user-interface') {
    $newset = array();
    foreach ($view->result as $result) {
      $newset[$result->campaign_manager_machine_name] = $result;
    }
    $view->result = $newset;
  }
}
