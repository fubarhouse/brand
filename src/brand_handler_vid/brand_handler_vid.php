<?php

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
