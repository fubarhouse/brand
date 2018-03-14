<?php

/**
 * Provide the active state of the brand's row.
 *
 * @ingroup views_filter_handlers
 */
class brand_handler_active_status extends views_handler_field
{

  function query() {
  }

  function option_definition() {
    return parent::option_definition();
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
  }

  /**
   * Render the active state of the brand.
   */
  public function render($values) {
    $brand = new Brand($values->brand_machine_name, $values->brand_date_created);
    return $brand->Check();
  }

}
