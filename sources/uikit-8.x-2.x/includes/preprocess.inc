<?php

/**
 * @file
 * Set up variables to be placed within the template (.tpl.php) files.
 *
 * The variables set up here apply to both templates (.tpl.php) files and
 * functions (theme_HOOK). These are also used for providing
 * @link https://www.drupal.org/node/223440 template suggestions @endlink.
 *
 * @see process.inc
 */

/**
 * Implements template_preprocess_block() for the primary menu.
 */
function uikit_preprocess_block__primary_menu__menu(&$variables) {
  $variables['content']['#theme'] = 'menu__primary';
}

/**
 * Implements template_preprocess_block() for the secondary menu.
 */
function uikit_preprocess_block__secondary_menu__menu(&$variables) {
  $variables['content']['#theme'] = 'menu__secondary';
}
