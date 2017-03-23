<?php

/**
 * @file
 * Default views for the Docs Companion module.
 */

/**
 * Implements hook_views_default_views().
 */
function docs_companion_views_default_views() {
  $view = new view();
  $view->name = 'uikit_statistics';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'projectstats';
  $view->human_name = 'UIkit Statistics';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'UIkit for Drupal Statistics';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: projectstats: downloads */
  $handler->display->display_options['fields']['downloads']['id'] = 'downloads';
  $handler->display->display_options['fields']['downloads']['table'] = 'projectstats';
  $handler->display->display_options['fields']['downloads']['field'] = 'downloads';
  $handler->display->display_options['fields']['downloads']['label'] = '';
  $handler->display->display_options['fields']['downloads']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['downloads']['alter']['text'] = '<li class="uk-text-contrast">downloads: [downloads]</li>';
  $handler->display->display_options['fields']['downloads']['element_type'] = '0';
  $handler->display->display_options['fields']['downloads']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['downloads']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['downloads']['element_default_classes'] = FALSE;
  /* Field: projectstats: installs */
  $handler->display->display_options['fields']['installs']['id'] = 'installs';
  $handler->display->display_options['fields']['installs']['table'] = 'projectstats';
  $handler->display->display_options['fields']['installs']['field'] = 'installs';
  $handler->display->display_options['fields']['installs']['label'] = '';
  $handler->display->display_options['fields']['installs']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['installs']['alter']['text'] = '<li class="uk-text-contrast">installs: [installs]</li>';
  $handler->display->display_options['fields']['installs']['element_type'] = '0';
  $handler->display->display_options['fields']['installs']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['installs']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['installs']['element_default_classes'] = FALSE;
  /* Filter criterion: projectstats: pid */
  $handler->display->display_options['filters']['pid']['id'] = 'pid';
  $handler->display->display_options['filters']['pid']['table'] = 'projectstats';
  $handler->display->display_options['filters']['pid']['field'] = 'pid';
  $handler->display->display_options['filters']['pid']['value']['value'] = '1';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');

  $views[$view->name] = $view;

  return $views;
}