<?php

/**
 * Provide the active state of the brand's row.
 *
 * @ingroup views_filter_handlers
 */
class brand_handler_theme_status extends views_handler_field
{

  function query()
  {
  }

  function option_definition()
  {
    return parent::option_definition();
  }

  function options_form(&$form, &$form_state)
  {
    parent::options_form($form, $form_state);
  }

  /**
   * Render the active state of the brand.
   */
  public function render($values)
  {
    $brand = new Brand($values->brand_machine_name, $values->brand_date_created);
    $theme = $brand::$Brand->theme;
    $themes = list_themes();
    if ($theme !== 'none') {
      $allowed_themes = variable_get('brand_allowed_themes', array());
      foreach ($allowed_themes as $allowed_theme) {
        if (isset($themes[$theme]) && (int) $themes[$theme]->status === 1) {
          if ($theme === $allowed_theme) {
            return 'Allowed';
          }
          if (variable_get('brand_disable_checking', 0) === 1) {
            return 'Allowed';
          }
        }
        return 'Not allowed';
      }
      return 'Not configured';
    }

  }
}
