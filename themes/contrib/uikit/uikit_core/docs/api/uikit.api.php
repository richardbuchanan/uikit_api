<?php

/**
 * @defgroup getting_started Getting started with UIkit
 * @{
 * @lead get_familiar Get familiar with the basic setup and structure of UIkit.
 * UIkit for Drupal does not come with the required UIkit framework files
 * because, in general,
 * @link https://www.drupal.org/node/422996 3rd party libraries and content are forbidden @endlink
 * from being committed to a reporsitory for projects hosted on
 * @link drupal.org drupal.org @endlink.
 *
 * This also makes the footprint of our repository smaller. Simply follow the
 * instructions below to get started with using UIkit for Drupal.
 *
 * @divider
 *
 * @section download_uikit Download UIkit
 * First of all you need to download UIkit. You can find the whole project and
 * all source files on GitHub. We currently support the latest version, 2.26.4.
 *
 * @button https://github.com/uikit/uikit/releases/tag/v2.26.4 Download UIkit v2.26.4 @endbutton
 *
 * @divider
 *
 * @section file_structure File Structure
 * In the ZIP file you will find all CSS, JavaScript and font files ready to use
 * for your project. The core framework of UIkit has almost no styling in order
 * to keep it slim. Therefore we provide two addidional distributions with a
 * gradient and an almost flat style.
 *
 * @table
 * @thead
 * @tr
 * @th Folder
 * @th Description
 * @endtr
 * @endthead
 * @tbody
 * @tr
 * @td
 * @inlinecode /css @endinlinecode
 * @endtd
 * @td
 * Contains all UIkit CSS files and minified versions.
 * @endtd
 * @endtr
 * @tr
 * @td
 * @inlinecode /fonts @endinlinecode
 * @endtd
 * @td
 * Contains fonts used in UIkit.
 * @endtd
 * @endtr
 * @tr
 * @td
 * @inlinecode /js @endinlinecode
 * @endtd
 * @td
 * Contains all UIkit JavaScript files and minified versions.
 * @endtd
 * @endtr
 * @endtbody
 * @endtable
 *
 * @precode
 * /css
 *     <!-- UIkit with the basic style -->
 *     uikit.css
 *     uikit.min.css
 *
 *     <!-- UIkit with Gradient style -->
 *     uikit.gradient.css
 *     uikit.gradient.min.css
 *
 *     <!-- UIkit with Almost flat style -->
 *     uikit.almost-flat.css
 *     uikit.almost-flat.min.css
 *
 *     <!-- Advanced components -->
 *     /components
 *
 * /fonts
 *     <!-- FontAwesome webfont -->
 *     fontawesome-webfont.ttf
 *     fontawesome-webfont.woff
 *     fontawesome-webfont.woff2
 *     FontAwesome.otf
 *
 * /js
 *     <!-- JavaScript and minified version -->
 *     uikit.js
 *     uikit.min.js
 *
 *     <!-- Advanced components -->
 *     /components
 *
 *     <!-- Core components -->
 *     /core
 * @endprecode
 * @bold Note @endbold: The complete folder structure should be placed in the
 * correct libraries directory as detailed in the installation section below.
 * The theme settings will allow you to choose which style and components your
 * site will use and will load the required files for you.
 *
 * @divider
 *
 * @section requirements Requirements
 * There are two addition requirements in order for UIkit for Drupal to work
 * properly.
 *
 * - @link https://www.drupal.org/project/jquery_update jQuery Update 2.7+ running jQuery 1.10+ @endlink
 * - @link https://www.drupal.org/project/libraries Libraries API @endlink
 *
 * @divider
 *
 * @section installation Installation
 * @subtitle Step one
 * UIkit for Drupal requires the UIkit framework to be installed in a
 * @link https://www.drupal.org/node/1440066 valid libraries directory @endlink.
 * You have three options in Drupal 7:
 * - sites/all/libraries~ directory or
 * - profiles/[yourprofilename]/libraries~ or
 * - sites/example.com/libraries~ if you have a multi-site installation
 *
 * @subtitle Step two
 * Now create a new directory named @inlinecode uikit @endinlinecode in the
 * libraries folder you used from above. Then extract everything from the zip
 * file you downloaded from GitHub into the new @inlinecode uikit @endinlinecode
 * directory.
 *
 * @subtitle Step three
 * Finally, install the
 * @link https://www.drupal.org/project/uikit UIkit theme project @endlink from
 * Drupal on your site. Detailed instructions can be found
 * @link https://www.drupal.org/getting-started/install-contrib/themes here @endlink.
 *
 * @subtitle Step four
 * Now you can enable the UIkit for Drupal theme by visiting
 * @inlinecode admin/appearance @endinlinecode. If creating a sub-theme, just
 * remember to add @inlinecode base theme = uikit @endinlinecode in your
 * [yourthemename].info file.
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
 * overview of these theme settings.
 *
 * @section theme_styles Theme styles
 *
 * @section mobile_settings Mobile settings
 *
 * @section layout Layout
 *
 * @section navigations Navigations
 *
 * @section elements Elements
 *
 * @section common Common
 *
 * @section javascript Javascript
 *
 * @section components Components
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
