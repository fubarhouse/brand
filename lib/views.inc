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
    if ((int) $values->brand_bid > 0) {
      return l($books[$values->brand_bid]['link_title'], '/' . $books[$values->brand_bid]['link_path']);
    }
    else {
      return 0;
    }
  }
}

/**
 * Provide the first name only from the name field.
 *
 * @ingroup views_filter_handlers
 */
class brand_handler_weight extends views_handler_field
{
  /**
   * Render the weight field.
   */
  public function render($values) {
    return $values->brand_weight;
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