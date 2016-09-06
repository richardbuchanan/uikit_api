<?php

/**
 * @defgroup getting_started Getting started with UIkit
 * @{
 * @lead get_familiar Get familiar with the basic setup and structure of UIkit.
 * UIkit for Drupal does not come with the required UIkit framework files
 * because, in general,
 * @link https://www.drupal.org/node/422996 3rd party libraries and content are forbidden @endlink
 * from being committed to a reporsitory for projects hosted on
 * @link drupal.org drupal.org @endlink. We instead use
 * @link https://cdnjs.com cdnjs.com @endlink to retrieve the
 * @link https://cdnjs.com/libraries/uikit UIkit library @endlink.
 *
 * This also makes the footprint of our repository smaller. Simply follow the
 * instructions below to get started with using UIkit for Drupal.
 *
 * @divider
 *
 * @section download_uikit Download UIkit
 * First of all you need to download UIkit for Drupal. There are three ways to
 * do this:
 * - direct download from drupal.org project page
 * - cloning repository from git.drupal.org
 * - downloading via Drush
 *
 * Please read the
 * @link https://www.drupal.org/docs/7/extending-drupal/installing-themes Installing themes @endlink
 * article before installing UIkit for Drupal. We only provide the download
 * methods below, not how to install themes.
 *
 * @subtitle via git.drupal.org
 * Use the following Git command to download the latest release from the 7.x-2.x
 * branch. This will ensure you get the latest commited branch. All other
 * methods below will only give you the most recent release, which may not
 * contain changes made in the Git repository.
 *
 * @inlineblockcode git clone --branch 7.x-2.x https://git.drupal.org/project/uikit.git @endinlineblockcode
 *
 * The development branch is currently the only supported branch. Extensive
 * work still needs done before a release candidate can be released.
 *
 * @subtitle via drupal.org
 * You can either visit
 * @link https://drupal.org/project/uikit drupal.org @endlink or use one of the
 * links below to download the project directly from drupal.org. There are two
 * releases (@del 7.x-1.x-dev @enddel and 7.x-2.x-dev), but work is no longer
 * being done on the 7.x-1.x branch. So be sure to download the 7.x-2.x branch.
 *
 * @button_large https://ftp.drupal.org/files/projects/uikit-7.x-2.x-dev.tar.gz UIkit 7.x-2.x-dev.tar.gz @endbutton_large @button_large https://ftp.drupal.org/files/projects/uikit-7.x-2.x-dev.zip UIkit 7.x-2.x-dev.zip @endbutton_large
 *
 * @subtitle via Drush
 * Drush is a command line and shell scripting interface for Drupal. Use the
 * following command to download UIkit for Drupal with Drush.
 *
 * @inlineblockcode drush dl uikit @endinlineblockcode
 *
 * Information on installing and using Drush can be found
 * @link http://www.drush.org/en/master/ here @endlink.
 *
 * @divider
 *
 * @section requirements Requirements
 * There were originall two requirements in order for UIkit for Drupal to work
 * properly,
 * @del @link https://www.drupal.org/project/jquery_update jQuery Update 2.7+ running jQuery 1.10+ @endlink @enddel
 * and
 * @del @link https://www.drupal.org/project/libraries Libraries API @endlink @enddel.
 * We have removed these requirements since we are now retrieving the UIkit
 * library from cdnjs.com.
 *
 * @divider
 *
 * Once you have finished implementing UIkit into your Drupal site, take a look
 * at the @link theme_settings UIkit theme settings @endlink to configure UIkit.
 * @}
 */

/**
 * @defgroup theme_settings UIkit theme settings
 * @{
 * @lead settings Customizing UIkit from the Drupal administration back-end.
 * UIkit comes with an extensive variety of theme settings to configure almost
 * all themeable aspects of your Drupal site. This topic provides a brief
 * overview of these theme settings to customize the look of your website.
 *
 * @subtitle Jump to a section
 * - @ref theme_styles
 * - @ref mobile_settings
 * - @ref layout
 * - @ref navigations
 * - @ref elements
 * - @ref common
 * - @ref javascript
 * - @ref components
 *
 * @section theme_styles Theme styles
 * UIkit comes with a basic theme and two neat themes to get you started. Here
 * you can select which base style to start with.
 *
 * @section mobile_settings Mobile settings
 * Adjust the mobile layout settings to enhance your users' experience on
 * smaller devices.
 *
 * @section layout Layout
 * Apply our fully responsive fluid grid system and panels, common layout parts
 * like blog articles and comments and useful utility classes.
 *
 * @section navigations Navigations
 * UIkit offers different types of navigations, like navigation bars and side
 * navigations. Use breadcrumbs or a pagination to steer through articles.
 *
 * @section elements Elements
 * Style basic HTML elements, like tables and forms. These components use their
 * own classes. They won't interfere with any default element styling.
 *
 * @section common Common
 * Here you'll find components that you often use within your content, like
 * buttons, icons, badges, overlays, animations and much more.
 *
 * @section javascript Javascript
 * These components rely mostly on JavaScript to fade in hidden content, like
 * dropdowns, modal dialogs, off-canvas bars and tooltips.
 *
 * @section components Components
 * UIkit offers some advanced components that are not included in the UIkit core
 * framework. Usually you wouldn't use these components in your everyday
 * website.
 * @}
 */

/**
 * @defgroup sub_theme Creating a UIkit sub-theme
 * @{
 * @lead subtheme Create a custom theme by inheriting the UIkit base theme.
 * Creating a custom theme utilizing UIkit is just like creating any other
 * theme. The only difference with creating a UIkit sub-theme is your custom
 * theme will automatically inherit all UIkit offers without having to reinvent
 * the wheel.
 * @}
 */

/**
 * @defgroup uikit_themeable UIkit's theme implementations
 * @{
 * Functions and templates for the user interface to be implemented by UIkit.
 *
 * Drupal's default template renderer is a simple PHP parsing engine that
 * includes the template and stores the output. Drupal's theme engines
 * can provide alternate template engines, such as XTemplate, Smarty and
 * PHPTal. The most common template engine is PHPTemplate (included with
 * Drupal and implemented in phptemplate.engine, which uses Drupal's default
 * template renderer. This is the template engine utilized by UIkit.
 *
 * UIkit implements hook overrides by the use of template files, which are used
 * to override the default implementations provided by Drupal. The folder
 * structure of UIkit helps identify whether the template is overriding a
 * default template or hook:
 * - uikit/templates: Overrides default templates
 * - uikit/theme: Overrides default hooks
 *
 * The templates folder is further divided into the modules which provided the
 * default template. This structure will make it easier to find a template file
 * during development of a sub-theme.
 * @}
 */
