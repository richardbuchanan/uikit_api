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

print '<ul class="uk-nav menu">' . $variables['tree'] . '</ul>';
