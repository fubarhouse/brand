<?php

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