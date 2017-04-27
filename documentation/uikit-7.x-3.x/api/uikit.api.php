<?php

/**
 * @defgroup getting_started Getting started with UIkit
 * @{
 * @lead get_familiar Get familiar with the basic setup and structure of UIkit 7.
 * UIkit 7 does not come with the required UIkit framework files because, in
 * general,
 * @link https://www.drupal.org/node/422996 3rd party libraries and content are forbidden @endlink
 * from being committed to a reporsitory for projects hosted on
 * @link drupal.org drupal.org @endlink. We instead use
 * @link https://cdnjs.com cdnjs.com @endlink to retrieve the
 * @link https://cdnjs.com/libraries/uikit UIkit library @endlink.
 *
 * This also makes the footprint of our repository smaller. Simply follow the
 * instructions below to get started with using UIkit 7.
 *
 * @divider
 *
 * @section download_uikit Download UIkit
 * First of all you need to download UIkit 7. There are three ways to do this:
 * - direct download from drupal.org project page
 * - downloading via Drush
 * - cloning repository from git.drupal.org
 *
 * Please read the
 * @link https://www.drupal.org/docs/7/extending-drupal/installing-themes Installing themes @endlink
 * article before installing UIkit 7. We only provide the download methods
 * below, not how to install themes.
 *
 * @heading h3 NOTE: Recommended for theme developers only @endheading
 * Since UIkit 7 is still in development, none of the following ways to download
 * UIkit 7 are recommended for use on production sites. UIkit 7 is still
 * considered unstable.
 *
 * @subtitle via drupal.org
 * You can either visit
 * @link https://drupal.org/project/uikit drupal.org @endlink or use one of the
 * links below to download the project directly from drupal.org.
 *
 * @button_large https://ftp.drupal.org/files/projects/uikit-7.x-3.x-dev.tar.gz UIkit 7.x-3.x-dev.tar.gz @endbutton_large @button_large https://ftp.drupal.org/files/projects/uikit-7.x-3.x-dev.zip UIkit 7.x-3.x-dev.zip @endbutton_large
 *
 * @subtitle via Drush
 * Drush is a command line and shell scripting interface for Drupal. Use the
 * following command to download UIkit 7 with Drush.
 *
 * @inlineblockcode drush dl uikit-7.x-3.x-dev @endinlineblockcode
 *
 * Information on installing and using Drush can be found
 * @link http://www.drush.org/en/master/ here @endlink.
 *
 * @subtitle via git.drupal.org
 * Use the following Git command to download the development release from the
 * 7.x-3.x branch. This will ensure you get the latest commited development
 * release.
 *
 * @inlineblockcode git clone --branch 7.x-3.x https://git.drupal.org/project/uikit.git @endinlineblockcode
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
 * There are no requirements to use UIkit 7. The required UIkit, jQuery v2.1.4
 * and jQuery Migrate v1.4.1 libraries are retrieved automatically. jQuery
 * Migrate allows us to use old code from jQuery 1.9+.
 *
 * @divider
 *
 * @section recommendations Recommendations
 * The following modules are recommended and fully supported by UIkit 7.
 *
 * @link https://www.drupal.org/project/uikit_components UIkit Components @endlink:
 * Provides additional components and functionality to the UIkit base theme.
 *
 * @divider
 *
 * Once you have finished implementing UIkit into your Drupal site, take a look
 * look at the @link sub_theme Creating a UIkit sub-theme @endlink to create a
 * UIkit sub-theme.
 * @}
 */

/**
 * @defgroup sub_theme Creating a UIkit sub-theme
 * @{
 * @lead subtheme Create a custom theme by inheriting the UIkit 7 base theme.
 * Creating a custom theme utilizing UIkit is just like creating any other
 * theme. The only difference with creating a UIkit sub-theme is your custom
 * theme will automatically inherit all UIkit offers without having to reinvent
 * the wheel.
 * @}
 */

/**
 * @defgroup theme_settings UIkit theme settings
 * @{
 * @lead settings Customizing UIkit 7 from the Drupal administration back-end.
 * UIkit comes with an extensive variety of theme settings to configure almost
 * all themeable aspects of your Drupal site. This topic provides a brief
 * overview of these theme settings to customize the look of your website.
 *
 * @subtitle Jump to a section
 * - @ref theme_styles
 * - @ref mobile_settings
 * - @ref layout
 * - @ref navigations
 *
 * @section theme_styles Theme styles
 * UIkit comes with a basic theme and two neat themes to get you started. Here
 * you can select which base style to start with.
 *
 * @divider
 *
 * @section mobile_settings Mobile settings
 * Adjust the mobile layout settings to enhance your users' experience on
 * smaller devices.
 *
 * @heading h3 Mobile Metadata @endheading
 * HTML5 has attributes that can be defined in meta elements. Here you can
 * control some of these attributes:
 * - charset: Specify the character encoding for the HTML document.
 * - x_ua_compatible IE Mode: In some cases, it might be necessary to restrict a
 *   webpage to a document mode supported by an older version of Windows
 *   Internet Explorer. Here we look at the x-ua-compatible header, which allows
 *   a webpage to be displayed as if it were viewed by an earlier version of the
 *   browser.
 *
 * @heading h3 Viewport Metadata @endheading
 * Gives hints about the size of the initial size of the viewport. This pragma
 * is used by several mobile devices only.
 * - Device width ratio: Defines the ratio between the device width
 *   (device-width in portrait mode or device-height in landscape mode) and the
 *   viewport size. Literal device width is defined as device-width and is the
 *   recommended value. You can also specify a pixel width by selecting Other,
 *   such as 300.
 * - Device height ratio: Defines the ratio between the device height
 *   (device-height in portrait mode or device-width in landscape mode) and the
 *   viewport size. Literal device height is defined as device-height and is the
 *   recommended value. You can also specify a pixel height by selecting Other,
 *   such as 300.
 * - initial-scale: Defines the ratio between the device width (device-width in
 *   portrait mode or device-height in landscape mode) and the viewport size.
 * - maximum-scale: Defines the maximum value of the zoom; it must be greater or
 *   equal to the minimum-scale or the behavior is indeterminate.
 * - minimum-scale: Defines the minimum value of the zoom; it must be smaller or
 *   equal to the maximum-scale or the behavior is indeterminate.
 * - user-scalable: If set to no, the user is not able to zoom in the webpage.
 *   Default value is Yes.
 *
 * @divider
 *
 * @section layout Layout
 * Apply our fully responsive fluid grid system and panels, common layout parts
 * like blog articles and comments and useful utility classes.
 *
 * @heading h3 Page Layout @endheading's
 * Page layout settings are available for standard, tablet and mobile layouts,
 * allowing you to arrange the main content and sidebar regions in various ways.
 * Each layout is independent of the others, giving you many ways to present
 * your content to your users.
 *
 * Additional page layout settings:
 * - Page Container: Add the .uk-container class to the page container to give
 *   it a max-width and wrap the main content of your website. For large screens
 *   it applies a different max-width.
 * - Page Centering: To center the page container, use the .uk-container-center
 *   class.
 * - Page Margin: Select the margin to add to the top and bottom of the page
 *   container. This is useful, for example, when using the gradient style with
 *   a centered page container and a navbar.
 *
 * @heading h3 Region Layout @endheading
 * Change region layout settings on a per region basis. You can currently apply
 * the following two components to each region (more will be added in the
 * future):
 * - Panel
 * - Block
 *
 * @divider
 *
 * @section navigations Navigations
 * UIkit offers different types of navigations, like navigation bars and side
 * navigations. Use breadcrumbs or a pagination to steer through articles.
 *
 * @heading h3 Local Tasks @endheading
 * Configure settings for the local tasks menus.
 * - Primary tasks style: Select the style to apply to the primary local tasks.
 * - Secondary tasks style: Select the style to apply to the secondary local
 *   tasks.
 *
 * @heading h3 Breadcrumbs @endheading
 * Configure settings for breadcrumb navigation.
 * - Display breadcrumbs: Check this box to display the breadcrumb.
 * - Display home link in breadcrumbs: Check this box to display the home link
 *   in breadcrumb trail.
 * - Display current page title in breadcrumbs: Check this box to display the
 *   current page title in breadcrumb trail.
 * @}
 */

/**
 * @defgroup uikit_themeable UIkit theme implementations
 * @{
 * @lead implementations Functions and templates for the user interface to be implemented by UIkit 7.
 * Drupal's default template renderer is a simple PHP parsing engine that
 * includes the template and stores the output. Drupal's theme engines
 * can provide alternate template engines, such as XTemplate, Smarty and
 * PHPTal. The most common template engine is PHPTemplate (included with
 * Drupal and implemented in phptemplate.engine, which uses Drupal's default
 * template renderer. This is the template engine utilized by UIkit.
 *
 * UIkit implements hook overrides by the use of template files and an include
 * file, which are used to override the default implementations provided by
 * Drupal. The folder structure of UIkit helps identify whether the template is
 * overriding a default template or theme hook:
 * - uikit_core/templates: Overrides default templates
 * - uikit_core/includes/theme.inc: Overrides default theme hooks
 *
 * The templates folder is further divided into the modules which provided the
 * default template. This structure will make it easier to find a template file
 * during development of a sub-theme.
 * @}
 */
