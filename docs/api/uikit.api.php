<?php

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
 *
 * @section theme_styles Theme styles
 * UIkit comes with a basic theme and two neat themes to get you started. Here
 * you can select which base style to start with. Or you can use the
 * @link https://getuikit.com/v2/docs/customizer.html Customizer @endlink to
 * easily upload a customized theme.
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
 * @heading h3 Page Layout @endheading
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
 * @heading h3 Navigation Bar @endheading
 * Configure settings for the navigation bar, where the primary and secondary
 * menus reside. Configurable options:
 * - Navbar container: Configure settings for the navigation bar container with
 *   the following options:
 *   - Container: Add the .uk-container class to the navbar container to give it
 *     a max-width and wrap the navbar of your website. For large screens it
 *     applies a different max-width.
 *   - Centering: To center the navbar container, use the .uk-container-center
 *     class.
 *   - Navbar attached: Adds the .uk-navbar-attached class to optimize the
 *     navbar's styling to be attached to the top of the viewport. For example,
 *     rounded corners will be removed.
 * - Navbar margin: Configure the top and bottom margin to apply to the navbar.
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
