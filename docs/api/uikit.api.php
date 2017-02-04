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
