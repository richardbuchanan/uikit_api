<?php

/**
 * @file
 * Describes plugins defined by the UIkit Views module.
 */

/**
 * Implements hook_views_plugins().
 */
function uikit_views_views_plugins() {
  $uikit_views = drupal_get_path('module', 'uikit_views');

  $plugins = array(
    'style' => array(
      // Settings for all UIkit Views style plugins.
      'uikit_views_accordion' => array(
        'title' => t('UIkit accordion'),
        'help' => t('Displays rows as a UIkit accordion component.'),
        'handler' => 'UIkitViewsPluginStyleAccordion',
        'uses fields' => TRUE,
        'uses row plugin' => TRUE,
        'uses row class' => FALSE,
        'uses options' => TRUE,
        'type' => 'normal',
        'path' => $uikit_views,
        'theme' => 'uikit_view_accordion',
        'theme path' => $uikit_views . '/templates',
        'theme file' => 'uikit_views.theme.inc',
      ),
      'uikit_views_grid' => array(
        'title' => t('UIkit grid'),
        'help' => t('Displays rows in a UIkit grid component.'),
        'handler' => 'UIkitViewsPluginStyleGrid',
        'uses fields' => FALSE,
        'uses row plugin' => TRUE,
        'uses row class' => FALSE,
        'uses options' => TRUE,
        'type' => 'normal',
        'path' => $uikit_views,
        'theme' => 'uikit_view_grid',
        'theme path' => $uikit_views . '/templates',
        'theme file' => 'uikit_views.theme.inc',
      ),
      'uikit_views_list' => array(
        'title' => t('UIkit list'),
        'help' => t('Displays rows as a UIkit list component.'),
        'handler' => 'UIkitViewsPluginStyleList',
        'uses fields' => TRUE,
        'uses row plugin' => TRUE,
        'uses row class' => FALSE,
        'uses options' => TRUE,
        'type' => 'normal',
        'path' => $uikit_views,
        'theme' => 'uikit_view_list',
        'theme path' => $uikit_views . '/templates',
        'theme file' => 'uikit_views.theme.inc',
      ),
      'uikit_views_table' => array(
        'title' => t('UIkit table'),
        'help' => t('Displays rows in a UIkit table component.'),
        'handler' => 'UIkitViewsPluginStyleTable',
        'uses fields' => TRUE,
        'uses row plugin' => FALSE,
        'uses row class' => TRUE,
        'uses options' => TRUE,
        'type' => 'normal',
        'path' => $uikit_views,
        'theme' => 'uikit_view_table',
        'theme path' => $uikit_views . '/templates',
        'theme file' => 'uikit_views.theme.inc',
      ),
    ),
  );

  return $plugins;
}
