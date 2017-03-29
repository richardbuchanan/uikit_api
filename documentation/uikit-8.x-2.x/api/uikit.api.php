<?php

/**
 * @defgroup getting_started Getting started with UIkit
 * @{
 * @lead get_familiar Get familiar with the basic setup and structure of UIkit 8.
 * UIkit 8 does not come with the required UIkit framework files because, in
 * general,
 * @link https://www.drupal.org/node/422996 3rd party libraries and content are forbidden @endlink
 * from being committed to a reporsitory for projects hosted on
 * @link drupal.org drupal.org @endlink. We instead use
 * @link https://cdnjs.com cdnjs.com @endlink to retrieve the
 * @link https://cdnjs.com/libraries/uikit UIkit library @endlink.
 *
 * This also makes the footprint of our repository smaller. Simply follow the
 * instructions below to get started with using UIkit 8.
 *
 * @divider
 *
 * @section download_uikit Download UIkit
 * First of all you need to download UIkit 8. There are three ways to do this:
 * - direct download from drupal.org project page
 * - downloading via Drush
 * - cloning repository from git.drupal.org
 *
 * Please read the
 * @link https://www.drupal.org/docs/8/extending-drupal-8/installing-themes Installing themes @endlink
 * article before installing UIkit 8. We only provide the download methods
 * below, not how to install themes.
 *
 * @heading h3 NOTE: Recommended for theme developers only @endheading
 * Since UIkit 8 is still in development, none of the following ways to
 * download UIkit 8 are recommended for use on production sites. UIkit 8 is
 * still considered unstable.
 *
 * @subtitle via drupal.org
 * You can either visit
 * @link https://drupal.org/project/uikit drupal.org @endlink or use one of the
 * links below to download the project directly from drupal.org.
 *
 * @button_large https://ftp.drupal.org/files/projects/uikit-8.x-2.x-dev.tar.gz UIkit 8.x-2.x-dev.tar.gz @endbutton_large @button_large https://ftp.drupal.org/files/projects/uikit-8.x-2.x-dev.zip UIkit 8.x-2.x-dev.zip @endbutton_large
 *
 * @subtitle via Drush
 * Drush is a command line and shell scripting interface for Drupal. Use the
 * following command to download UIkit 8 with Drush.
 *
 * @inlineblockcode drush dl uikit @endinlineblockcode
 *
 * Information on installing and using Drush can be found
 * @link http://www.drush.org/en/master/ here @endlink.
 *
 * @subtitle via git.drupal.org
 * Use the following Git command to download the development release from the
 * 8.x-2.x branch. This will ensure you get the latest commited development
 * release.
 *
 * @inlineblockcode git clone --branch 8.x-2.x https://git.drupal.org/project/uikit.git @endinlineblockcode
 *
 * The development branch is where all new development resides and not
 * recommended for use on production sites. Work still needs done before a
 * release candidate can be released. We ask you use the
 * @link https://www.drupal.org/project/issues/uikit?categories=All issue queue @endlink
 * to report bugs, support or feature requests.
 *
 * @divider
 *
 * @section requirements Requirements
 * There are no requirements to use UIkit 8.
 * @}
 */

/**
 * @defgroup sub_theme Creating a UIkit sub-theme
 * @{
 * @lead subtheme Create a custom theme by inheriting the UIkit 8 base theme.
 * Creating a custom theme utilizing UIkit is just like creating any other
 * theme. The only difference with creating a UIkit sub-theme is your custom
 * theme will automatically inherit all UIkit offers without having to reinvent
 * the wheel.
 * @}
 */

/**
 * @defgroup uikit_themeable UIkit theme implementations
 * @{
 * @lead implementations Functions and templates for the user interface to be implemented by UIkit 8.
 * Drupal's default template renderer is a simple PHP parsing engine that
 * includes the template and stores the output. The default template engine in
 * Drupal 8 is Twig. This is the template engine utilized by UIkit 8.
 *
 * UIkit implements hook overrides by the use of template files and an include
 * file, which are used to override the default implementations provided by
 * Drupal. The folder structure of UIkit helps identify whether the template is
 * overriding a default template or theme hook:
 * - templates: Overrides default templates
 * - includes/theme.inc: Overrides default theme hooks
 *
 * Contrary to Drupal 7, in Drupal 8 template files (*.html.twig files) must be
 * stored in the 'templates' sub folder. The templates folder is further divided
 * into various elemental folders (i.e. block, layout, navigation, etc.). This
 * structure will make it easier to find a template file during development of a
 * sub-theme.
 * @}
 */
