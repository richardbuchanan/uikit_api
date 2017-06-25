<?php

/**
 * @mainpage UIkit Blog
 * Welcome to the UIkit Blog developer's documentation. Newcomers to Drupal 8
 * theme development should review the
 * @link https://api.drupal.org/api/drupal/core%21lib%21Drupal%21Core%21Render%21theme.api.php/group/themeable/8.2.x Theme system overview @endlink
 * API reference and
 * @link https://www.drupal.org/theming Theming and Front End Development with Drupal @endlink
 * before reading the heavily-documented topics below.
 *
 * @section about_uikit_blog About UIkit Blog
 * @link https://www.drupal.org/project/uikit UIkit @endlink blog theme tailored
 * to bloggers and personal websites.
 *
 * UIkit Blog comes installed with pre-configured regions and theme settings to
 * get you started blogging fast!
 *
 * @section installation Installation
 * For the best blogging experience install and enable
 * @link https://www.drupal.org/project/uikit_components UIkit Components @endlink
 * first, then install and enable UIkit Blog as you normally would install a
 * theme.
 *
 * @section drush_integration Drush integration
 * We have added Drush integration to support generating a UIkit Blog sub-theme
 * from the command line. The Drush command
 * @inlinecode uikit-blog-starterkit @endinlinecode (alias
 * @inlinecode uikit-blog-sk @endinlinecode) uses the starterkit now included
 * with the project.
 *
 * @subtitle Usage example:
 * @code
 * drush uikit-blog-sk machine_name "Theme name" --path=sites/default/themes --description="Awesome theme description."
 * @endcode
 *
 * @inlinecode machine_name @endinlinecode, @inlinecode --path @endinlinecode
 * and @inlinecode --description @endinlinecode are all optional; only the theme
 * name (wrapped in double-quotes) is required. Use drush
 * @inlinecode uikit-blog-sk --help @endinlinecode to view more detailed help
 * information. If Drush reports it cannot find the command, be sure to run
 * @inlinecode drush cc drush @endinlinecode to clear Drush's cache.
 *
 * @section uikit_blog_api UIkit Blog API Topics
 * Here are some topics to help you get started developing with UIkit Blog 8:
 * - @link uikit_blog_themeable UIkit Blog theme implementations @endlink
 */
