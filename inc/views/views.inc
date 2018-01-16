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
class brand_handler_bid extends views_handler_field {
  /**
   * Render the name field.
   */
  public function render($values) {
    $books = book_get_books();
    if ((int) $values->brand_bid > 0) {
      return l($books[$values->brand_bid]['link_title'], '/' . $books[$values->brand_bid]['link_path']);
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

      // Program name.
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
      ),

      // Machine name.
      'machine_name' => array(
        'title' => t('Machine name'),
        'help' => t('The machine name for the brand.'),
        'field' => array(
          'click sortable' => TRUE,
        ),
        'filter' => array(
          'handler' => 'views_handler_filter_string',
        ),
        'sort' => array(
          'handler' => 'views_handler_sort',
        ),
      ),

      // Date created.
      'date_created' => array(
        'title' => t('Created'),
        'help' => t('The date the brand entry was created.'),
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
        'title' => t('Start date'),
        'help' => t('The date the brand starts.'),
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
        'title' => t('Finishes'),
        'help' => t('The date the brand finishes.'),
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

      // Targets.
      'path_visibility' => array(
        'title' => t('Targets'),
        'help' => t('The machine name for the brand.'),
        'field' => array(
          'click sortable' => TRUE,
        ),
        'filter' => array(
          'handler' => 'views_handler_filter_string',
        ),
        'sort' => array(
          'handler' => 'views_handler_sort',
        ),
      ),

      // Description.
      'description' => array(
        'title' => t('Description'),
        'help' => t('The machine name for the brand.'),
        'field' => array(
          'click sortable' => TRUE,
        ),
        'filter' => array(
          'handler' => 'views_handler_filter_string',
        ),
        'sort' => array(
          'handler' => 'views_handler_sort',
        ),
      ),

      // Path.
      'path_assets' => array(
        'title' => t('Path'),
        'help' => t('The machine name for the brand.'),
        'field' => array(
          'click sortable' => TRUE,
        ),
        'filter' => array(
          'handler' => 'views_handler_filter_string',
        ),
        'sort' => array(
          'handler' => 'views_handler_sort',
        ),
      ),

      // Targets.
      'path_search' => array(
        'title' => t('Search page'),
        'help' => t('The machine name for the brand.'),
        'field' => array(
          'click sortable' => TRUE,
        ),
        'filter' => array(
          'handler' => 'views_handler_filter_string',
        ),
        'sort' => array(
          'handler' => 'views_handler_sort',
        ),
      ),

      'date_lock' => array(
        'title' => t('Date locking'),
        'help' => t('Determine if logic should use the finish date in its logic.'),
        'field' => array(
          'handler' => 'views_handler_field_boolean',
          'click sortable' => TRUE,
        ),
        'filter' => array(
          'handler' => 'views_handler_filter_boolean_operator',
          'label' => t('Published'),
          'type' => 'yes-no',
          'use equal' => TRUE,
        ),
        'sort' => array(
          'handler' => 'views_handler_sort',
        ),
      ),

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
      ),

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
      ),

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
      ),

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
      ),

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
      ),

    ),
  );
  return $table;
}
