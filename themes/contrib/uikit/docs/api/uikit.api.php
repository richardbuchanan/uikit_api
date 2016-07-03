<?php

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
