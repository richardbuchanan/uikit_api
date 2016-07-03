<?php

/**
 * @file
 * Returns HTML for a wrapper for a menu sub-tree.
 *
 * Available variables:
 * - $variables['tree']: An HTML string containing the tree's items.
 *
 * @see template_preprocess_menu_tree()
 * @see uikit_preprocess_page()
 * @see theme_menu_tree()
 *
 * @ingroup uikit_themeable
 */

print '<div class="uk-navbar-flip"><ul class="uk-navbar-nav uk-hidden-small">' . $variables['tree'] . '</ul></div>';
