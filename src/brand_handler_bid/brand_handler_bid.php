<?php

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
