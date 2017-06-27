<?php

/**
 * @defgroup uikit_admin_themeable UIkit Admin theme implementations
 * @{
 * @lead implementations Functions and templates for the user interface to be implemented by UIkit Admin 8.
 * Drupal's default template renderer is a simple PHP parsing engine that
 * includes the template and stores the output. The default template engine in
 * Drupal 8 is Twig. This is the template engine utilized by UIkit Admin 8.
 *
 * UIkit Admin implements hook overrides by the use of template files and an
 * include file, which are used to override the default implementations provided
 * by Drupal.
 *
 * Contrary to Drupal 7, in Drupal 8 template files (*.html.twig files) must be
 * stored in the 'templates' sub folder. The templates folder is further divided
 * into various elemental folders (i.e. block, layout, navigation, etc.). This
 * structure will make it easier to find a template file during development of a
 * sub-theme.
 * @}
 */
