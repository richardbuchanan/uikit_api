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
        ),
      );
    }
  }
}

/**
 * Implements hook_form_alter().
 */
function docs_form_alter(&$form, &$form_state, $form_id) {
  $add_to_cart_form = substr($form_id, 0, 30) === 'commerce_cart_add_to_cart_form';
  if ($add_to_cart_form) {
    $form['submit']['#attributes']['class'][] = 'uk-margin-top';

    $donate_form = isset($form['line_item_fields']) && isset($form['line_item_fields']['commerce_donate_amount']);
    if ($donate_form) {
      $args = array();
      $args['@description'] = 'UIkit for Drupal typically has little administrative overhead, which is why we believe a donation to UIkit for Drupal can be leveraged to make the maximum impact possible. We use the donations to help offset the cost of running our servers and to provide funding to our designers and developers involved in the project through Buchanan Design Group. Any donation, no matter how big or small, goes a long way to continuing the project.';
      $form['#prefix'] = '<div id="donate" class="uk-margin-large-top">';
      $form['#prefix'] .= '<hr class="uk-article-divider">';
      $form['#suffix'] = '</div>';
      $form['title'] = array(
        '#markup' => t('<h2>Donate</h2>'),
      );
      $form['description'] = array(
        '#markup' => t('<p>@description</p>', $args),
      );
      $form['#submit'][] = 'docs_donate_cart_add_to_cart_form_submit';
    }
  }

  if ($form_id == 'comment_node_forum_form') {
    $form['subject']['#required'] = TRUE;
    $form['comment_body']['und'][0]['#title'] = t('Reply');
  }
}

/**
 * Implements hook_form_FORM_ID_alter() for user_register_form.
 */
function docs_form_user_login_alter(&$form, &$form_state) {
  $form['#attributes']['class'][] = 'docs-login-form';
  $links = '<ul class="uk-subnav uk-subnav-line uk-margin-top">';
  $links .= '<li>' . l(t('Create new account'), 'user/register') . '</li>';
  $links .= '<li>' . l(t('Request new password'), 'user/password') . '</li>';
  $links .= '</ul>';
  $form['links'] = array(
    '#markup' => $links,
  );
}

/**
 * Implements hook_form_FORM_ID_alter() for user_register_form.
 */
function docs_form_user_register_form_alter(&$form, &$form_state) {
  unset($form['notifications_forum']);
  unset($form['notifications_forum']['forums']);
  unset($form['notifications_forum']['send_method']);
  unset($form['notifications_forum']['send_interval']);
}

/**
 * Form submit handler: add the selected product to the cart.
 */
function docs_donate_cart_add_to_cart_form_submit($form, &$form_state) {
  $product_id = $form_state['values']['product_id'];
  $product = commerce_product_load($product_id);

  // Create the new product line item of the same type.
  $line_item = commerce_product_line_item_new($product, $form_state['values']['quantity'], 0, $form_state['line_item']->data, $form_state['line_item']->type);

  // Only attempt an Add to Cart if the line item has a valid unit price.
  $line_item_wrapper = entity_metadata_wrapper('commerce_line_item', $line_item);

  if (!is_null($line_item_wrapper->commerce_unit_price->value())) {
    // Redirect the user to the cart.
    $form_state['redirect'] = 'cart';
  }
}


/**
 * Implements hook_js_alter().
 */
function docs_js_alter(&$javascript) {
  $theme = drupal_get_path('theme', 'docs');
  $ctools = drupal_get_path('module', 'ctools');
  $collapsible_div = $ctools . '/js/collapsible-div.js';
  $advanced_forum = drupal_get_path('module', 'advanced_forum') . '/js/advanced_forum.js';

  if (isset($javascript['misc/autocomplete.js'])) {
    $javascript['misc/autocomplete.js']['data'] = $theme . '/js/autocomplete.js';
  }

  if (isset($javascript['misc/textarea.js'])) {
    $javascript['misc/textarea.js']['data'] = $theme . '/js/textarea.js';
  }

  if (isset($javascript[$collapsible_div])) {
    $javascript[$collapsible_div]['data'] = $theme . '/js/collapsible-div.js';
  }

  if (isset($javascript[$advanced_forum])) {
    $javascript[$advanced_forum]['data'] = $theme . '/js/advanced_forum.js';
  }
}
