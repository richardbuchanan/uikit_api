<?php

/**
 * @file
 * The UIkit theme system, which controls the output of the UIkit theme.
 *
 * The theme system allows for nearly all output of the Drupal system to be
 * customized by UIkit themes.
 *
 * @ingroup uikit_themeable
 */

/**
 * Implements hook_theme().
 */
function uikit_theme($existing, $type, $theme, $path) {
  $items['menu__navbar'] = array(
    'base hook' => 'menu',
    'variables' => array('items' => array(), 'attributes' => array()),
    'path' => drupal_get_path('theme', 'uikit') . '/templates/navigation',
    'template' => 'menu--navbar',
  );
  $items['menu__offcanvas'] = array(
    'base hook' => 'menu',
    'variables' => array('items' => array(), 'attributes' => array()),
    'path' => drupal_get_path('theme', 'uikit') . '/templates/navigation',
    'template' => 'menu--offcanvas',
  );

  return $items;
}
