<?php

/**
 * @file
 * Modify structured content arrays.
 *
 * These hooks are called after the content has been assembled in a structured
 * array and may be used for doing processing which requires that the complete
 * content structure has been built.
 *
 * If the theme wishes to act on the rendered HTML of the content rather than
 * the structured content array, it may use this hook to add a #post_render
 * callback. Alternatively, it could also implement hook_preprocess_HOOK().
 *
 * @see drupal_render()
 * @see theme()
 */

/**
 * Implements hook_block_view_alter().
 */
function docs_block_view_alter(&$data, $block) {
  $delta = $block->delta;
  $module = $block->module;
  $region = $block->region;
  $branch = api_get_active_branch();

  if ($delta == 'navigation' && $module == 'api' && $region == 'sidebar_second') {
    $branch = api_get_active_branch();

    if (user_access('access API reference') && !empty($branch)) {
      // Figure out if this is the default branch for this project, the same
      // way the menu system decides.
      $branches = api_get_branches();
      $projects = _api_make_menu_projects();
      $is_default = ($branch->branch_name === $projects[$branch->project]['use branch']);
      $suffix = ($is_default) ? '' : '/' . $branch->branch_name;

      $types = array(
        'groups' => t('Topics'),
        'classes' => t('Classes'),
        'functions' => t('Functions'),
        'files' => t('Files'),
        'namespaces' => t('Namespaces'),
        'services' => t('Services'),
        'constants' => t('Constants'),
        'globals' => t('Globals'),
        'deprecated' => t('Deprecated'),
      );

      $links = array(
        '#theme_wrappers' => array('container__api__navigation'),
        '#attributes' => array(
          'class' => array('uk-panel', 'uk-panel-box', 'uk-active'),
        ),
      );

      $current_path = current_path();
      $counts = api_listing_counts($branch);
      $item = _db_api_active_item();

      foreach ($types as $type => $title) {
        if ($type === '' || $counts[$type] > 0) {
          $branch_path = 'api/' . $branch->project;
          $path = $branch_path;

          if ($type) {
            $path .= "/$type";
            $title = $title . '<span class="uk-badge uk-float-right">' . $counts[$type] . '</span>';
          }

          $path .= $suffix;
          $class = array();

          if ($type || ($type === '' && !$counts['groups'])) {

            if ($path === $current_path || ($item && preg_match('/^' . $item->object_type . '/', $type))) {
              $class[] = 'uk-active';
            }

            $links[] = array(
              '#theme' => 'link__api__navigation_link',
              '#text' => $title,
              '#path' => $path,
              '#options' => array(
                'html' => TRUE,
                'attributes' => array(
                  'class' => $class,
                ),
              ),
            );
          }
          else {
            $links[] = array(
              '#theme' => 'html_tag__api__navigation_link',
              '#tag' => 'div',
              '#value' => $title,
              '#attributes' => array(
                'class' => $class,
              ),
            );
          }
        }
      }

      $items = array();

      foreach ($branches as $obj) {
        $is_default = ($obj->branch_name === $projects[$obj->project]['use branch']);
        $suffix = ($is_default) ? '' : '/' . $obj->branch_name;

        $items[] = array(
          '#theme' => 'link',
          '#text' => $obj->title,
          '#path' => 'api/' . $obj->project . $suffix,
          '#options' => array(
            'html' => FALSE,
            'attributes' => array(),
          ),
          '#active' => $branch->branch_name === $obj->branch_name,
        );
      }

      $data = array(
        'subject' => t('API Navigation'),
        'content' => array(
          'links' => $links,
          'branches' => array(
            '#theme' => 'bootstrap_dropdown',
            '#toggle' => array(
              '#theme' => 'button',
              '#button_type' => 'button',
              '#value' => t('Projects') . ' <span class="caret"></span>',
              '#attributes' => array(
                'class' => array('btn-default', 'btn-block'),
              ),
            ),
            '#items' => $items,
          ),
        ),
      );
    }
  }
}

/**
 * Implements hook_form_FORM_ID_alter().
 */
function docs_form_commerce_cart_add_to_cart_form_1_alter(&$form, &$form_state, $form_id) {
  $form['element']['submit']['#attributes']['class'][] = 'uk-margin-top';
}


/**
 * Implements hook_js_alter().
 */
function docs_js_alter(&$javascript) {
  $theme = drupal_get_path('theme', 'docs');
  $ctools = drupal_get_path('module', 'ctools');
  $collapsible_div = $ctools . '/js/collapsible-div.js';

  if (isset($javascript['misc/autocomplete.js'])) {
    $javascript['misc/autocomplete.js']['data'] = $theme . '/js/autocomplete.js';
  }

  if (isset($javascript['misc/textarea.js'])) {
    $javascript['misc/textarea.js']['data'] = $theme . '/js/textarea.js';
  }
  if (isset($javascript[$collapsible_div])) {
    $javascript[$collapsible_div]['data'] = $theme . '/js/collapsible-div.js';
  }
}
