<?php

/**
 * Implementation of hook_drush_command().
 */
function brand_drush_command() {
  $items = array();
  $items['brand'] = array(
    'callback' => 'brand_drush_execute',
    'description' => 'Drush command to get node count of particular node type.',
    'examples' => array(
      'Add a theme to the allowed themes list' => 'drush brand allow bartik',
      'List the machine names for all configured brands' => 'drush brand list',
      'Remove a theme from the list of allowed themes' => 'drush brand disallow bartik',
    ),
    'arguments' => array(
      'allow' => 'Add a theme into the list of allowed themes.',
      'disallow' => 'Remove a theme from the allowed themes.',
      'restrict' => 'Imposes the restriction of theme selection to those configured',
      'unrestrict' => 'Removes the restriction of available themes configured.',
    ),
  );
  return $items;
}

/**
 * Callback function for hook_drush_command().
 */
function brand_drush_execute() {
  // Get arguments passed in command, Ex: drush nc page blog
  $args = func_get_args();
  if ($args) {
    switch ($args[0]):
      case 'allow':
        if (isset($args[1])) {
          $allowed_themes = brand_get_allowed_themes();
          foreach ($allowed_themes as $allowed_theme) {
            $themes[$allowed_theme] = $allowed_theme;
          }
          if (!isset($themes[$args[1]])) {
            $real_themes = list_themes();
            if (isset($real_themes[$args[1]])) {
              $allowed_themes[] = $args[1];
              variable_set('brand_allowed_themes', $allowed_themes);
              $new_themes = variable_get('brand_allowed_themes', array());
              foreach ((array) $new_themes as $new_theme) {
                if ($new_theme === $args[1]) {
                  drush_log("{$args[1]} has successfully been added to the allowed themes list.", 'ok');
                }
                else {
                  drush_log("{$args[1]} could not be added to the allowed themes list.", 'error');
                }
              }
            }
            else {
              drush_log("{$args[1]} doesn't appear to be recognized as a theme by Drupal.", 'error');
            }
          }
          else {
            drush_log("{$args[1]} is already in the list of allowed themes.", 'warning');
          }
        }
        else {
          drush_log('No theme specified, run \'drush help brand\' for more information.', 'error');
        }
        break;
      case 'disallow':
        if (isset($args[1])) {
          $allowed_themes = brand_get_allowed_themes();
          foreach ($allowed_themes as $allowed_theme) {
            $themes[$allowed_theme] = $allowed_theme;
          }
          if (isset($themes[$args[1]])) {
            $real_themes = list_themes();
            if (isset($real_themes[$args[1]])) {
              foreach ($allowed_themes as $key => $value) {
                if ($value === $args[1]) {
                  unset($allowed_themes[$key]);
                }
              }
              variable_set('brand_allowed_themes', $allowed_themes);
              $new_themes = variable_get('brand_allowed_themes', array());
              $found = FALSE;
              foreach ((array) $new_themes as $new_theme) {
                if ($new_theme === $args[1]) {
                  $found = TRUE;
                }
              }
              if ($found === FALSE) {
                drush_log("{$args[1]} has successfully been removed from the allowed themes list.", 'ok');
              }
              else {
                drush_log("{$args[1]} could not be removed from the allowed themes list.", 'error');
              }
            }
            else {
              drush_log("{$args[1]} doesn't appear to be recognized as a theme by Drupal.", 'error');
            }
          }
          else {
            drush_log("{$args[1]} is not already in the list of allowed themes.", 'warning');
          }
        }
        else {
          drush_log('No theme specified, run \'drush help brand\' for more information.', 'error');
        }
        break;
      case 'restrict':
        $old_restriction = variable_get('brand_disable_checking', 0);
        if ((int) $old_restriction === 0) {
          drush_log('Restrictions on theme selection are already imposed.', 'warning');
        }
        else {
          variable_set('brand_disable_checking', 0);
          $new_restriction = variable_get('brand_disable_checking', 0);
          if ((int) $new_restriction === 0) {
            drush_log('Restrictions on theme selection have been imposed.', 'ok');
          }
          else {
            drush_log('Restrictions on theme selection could not be imposed.', 'error');
          }
        }
        break;
      case 'unrestrict':
        $old_restriction = variable_get('brand_disable_checking', 0);
        if ((int) $old_restriction === 1) {
          drush_log('Restrictions on theme selection are not imposed.', 'warning');
        }
        else {
          variable_set('brand_disable_checking', 1);
          $new_restriction = variable_get('brand_disable_checking', 0);
          if ((int) $new_restriction === 1) {
            drush_log('Restrictions on theme selection have been lifted.', 'ok');
          }
          else {
            drush_log('Restrictions on theme selection could not be lifted.', 'err');
          }
        }
        break;
      default:
        drush_log('No argument specified, run \'drush help brand\' for more information.', 'error');
        break;
    endswitch;
  }
  else {
    drush_log('No argument specified, run \'drush help brand\' for more information.', 'error');
  }
}
