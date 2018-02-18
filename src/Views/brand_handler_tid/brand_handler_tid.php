<?php

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
