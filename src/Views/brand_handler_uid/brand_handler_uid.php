<?php

/**
 * Provide a link to the user page.
 *
 * @ingroup views_filter_handlers
 */
class brand_handler_uid extends views_handler_field {
  /**
   * Render the UID field.
   */
  public function render($values) {
    $user = user_load($values->brand_uid);
    return l($user->name, '/user/' . $user->uid);
  }
}
