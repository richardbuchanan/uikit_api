<?php

/**
 * @file
 * Preprocessors and helper functions to make theming easier.
 */

/**
 * Prepares variables for UIkit Grid templates.
 *
 * Default template: uikit-view-grid.tpl.php.
 *
 * @param array $variables
 *   An associative array containing:
 *   - view: A ViewExecutable object.
 *   - rows: The raw row data.
 */
function template_preprocess_uikit_view_grid(&$variables) {
  $view = $variables['view'];
  $options = $view->style_plugin->options;
  $grid_classes = array('uk-grid');
  $attributes = array(
    'class' => array('uikit-view-grid'),
  );

  $variables['grid_divider'] = FALSE;
  if ($options['grid_divider']) {
    $grid_classes[] = 'uk-grid-divider';
  }

  if ($options['grid_gutter'] != 'default') {
    $grid_classes[] = $options['grid_gutter'];
  }

  foreach (['@s', '@m', '@l', '@xl'] as $size) {
    $grid_classes[] = $options["width_${size}"];
  }

  if ($options['row_class']) {
    $grid_classes[] = $options['row_class'];
  }

  $variables['attributes_array'] = $attributes;
  $variables['grid_classes'] = implode(' ', $grid_classes);

  drupal_add_css(drupal_get_path('module', 'uikit_views') . '/css/uikit-views.grid.layout.css');
}

/**
 * Prepares variables for UIkit Grid templates.
 *
 * Default template: uikit-view-grid.tpl.php.
 *
 * @param array $variables
 *   An associative array containing:
 *   - view: A ViewExecutable object.
 *   - rows: The raw row data.
 */
function template_process_uikit_view_grid(&$variables) {
  $variables['attributes'] = drupal_attributes($variables['attributes_array']);
}

/**
 * Prepares variables for UIkit List templates.
 *
 * Default template: uikit-view-list.tpl.php.
 *
 * @param array $variables
 *   An associative array containing:
 *   - view: A ViewExecutable object.
 *   - rows: The raw row data.
 */
function template_preprocess_uikit_view_list(&$variables) {
  $handler = $variables['view']->style_plugin;
  $options = $handler->options;

  $variables['list_attributes_array']['class'] = array('uk-list');
  if ($options['modifier'] != 'default') {
    $variables['list_attributes_array']['class'][] = $options['modifier'];
  }
  if ($options['large_modifier']) {
    $variables['list_attributes_array']['class'][] = 'uk-list-large';
  }

  $variables['wrapper_attributes_array'] = array();
  if ($options['wrapper_class']) {
    $wrapper_classes = explode(' ', $options['wrapper_class']);
    foreach ($wrapper_classes as $wrapper_class) {
      $variables['wrapper_attributes_array']['class'][] = $wrapper_class;
    }
  }
}

function template_process_uikit_view_list(&$variables) {
  $variables['list_attributes'] = drupal_attributes($variables['list_attributes_array']);
  $variables['wrapper_attributes'] = drupal_attributes($variables['wrapper_attributes_array']);
}

/**
 * Prepares variables for UIkit Table templates.
 *
 * Default template: uikit-view-table.tpl.php.
 *
 * @param array $variables
 *   An associative array containing:
 *   - view: A ViewExecutable object.
 *   - rows: The raw row data.
 */
function template_preprocess_uikit_view_table(&$variables) {
  $view = $variables['view'];

  // We need the raw data for this grouping, which is passed in as $variables['rows'].
  // However, the template also needs to use for the rendered fields.  We
  // therefore swap the raw data out to a new variable and reset $variables['rows']
  // so that it can get rebuilt.
  // Store rows so that they may be used by further preprocess functions.
  $result = $variables['result'] = $variables['rows'];
  $variables['rows'] = array();
  $variables['field_classes'] = array();
  $variables['header'] = array();

  $options = $view->style_plugin->options;
  $handler = $view->style_plugin;

  $row_class_special = isset($options['row_class_special']) ? $options['row_class_special'] : TRUE;
  $responsive = isset($options['uikit_table_options']['responsive_table']) ? $options['uikit_table_options']['responsive_table'] : FALSE;
  $vertical_modifier = isset($options['uikit_table_options']['vertical_modifier']) ? $options['uikit_table_options']['vertical_modifier'] : FALSE;
  $table_modifiers = isset($options['uikit_table_options']['table_modifiers']) ? $options['uikit_table_options']['table_modifiers'] : array();

  $fields = &$view->field;
  $columns = $handler->sanitize_columns($options['columns'], $fields);

  $active = !empty($handler->active) ? $handler->active : '';
  $order = !empty($handler->order) ? $handler->order : 'asc';

  $query = tablesort_get_query_parameters();
  if (isset($view->exposed_raw_input)) {
    $query += $view->exposed_raw_input;
  }

  // Fields must be rendered in order as of Views 2.3, so we will pre-render
  // everything.
  $renders = $handler->render_fields($result);

  foreach ($columns as $field => $column) {
    // Create a second variable so we can easily find what fields we have and what the
    // CSS classes should be.
    $variables['fields'][$field] = drupal_clean_css_identifier($field);
    if ($active == $field) {
      $variables['fields'][$field] .= ' active';
    }

    // render the header labels
    if ($field == $column && empty($fields[$field]->options['exclude'])) {
      $label = check_plain(!empty($fields[$field]) ? $fields[$field]->label() : '');
      if (empty($options['info'][$field]['sortable']) || !$fields[$field]->click_sortable()) {
        $variables['header'][$field] = $label;
      }
      else {
        $initial = !empty($options['info'][$field]['default_sort_order']) ? $options['info'][$field]['default_sort_order'] : 'asc';

        if ($active == $field) {
          $initial = ($order == 'asc') ? 'desc' : 'asc';
        }

        $title = t('sort by @s', array('@s' => $label));
        if ($active == $field) {
          $label .= theme('tablesort_indicator', array('style' => $initial));
        }

        $query['order'] = $field;
        $query['sort'] = $initial;
        $link_options = array(
          'html' => TRUE,
          'attributes' => array('title' => $title),
          'query' => $query,
        );
        $variables['header'][$field] = l($label, $_GET['q'], $link_options);
      }

      $variables['header_classes'][$field] = '';
      // Set up the header label class.
      if ($fields[$field]->options['element_default_classes']) {
        $variables['header_classes'][$field] .= "views-field views-field-" . $variables['fields'][$field];
      }
      $class = $fields[$field]->element_label_classes(0);
      if ($class) {
        if ($variables['header_classes'][$field]) {
          $variables['header_classes'][$field] .= ' ';
        }
        $variables['header_classes'][$field] .= $class;
      }
      // Add a CSS align class to each field if one was set
      if (!empty($options['info'][$field]['align'])) {
        $variables['header_classes'][$field] .= ' ' . drupal_clean_css_identifier($options['info'][$field]['align']);
      }

      // Add a header label wrapper if one was selected.
      if ($variables['header'][$field]) {
        $element_label_type = $fields[$field]->element_label_type(TRUE, TRUE);
        if ($element_label_type) {
          $variables['header'][$field] = '<' . $element_label_type . '>' . $variables['header'][$field] . '</' . $element_label_type . '>';
        }
      }

    }

    // Add a CSS align class to each field if one was set
    if (!empty($options['info'][$field]['align'])) {
      $variables['fields'][$field] .= ' ' . drupal_clean_css_identifier($options['info'][$field]['align']);
    }

    // Render each field into its appropriate column.
    foreach ($result as $num => $row) {
      // Add field classes
      $variables['field_classes'][$field][$num] = '';
      if ($fields[$field]->options['element_default_classes']) {
        $variables['field_classes'][$field][$num] = "views-field views-field-" . $variables['fields'][$field];
      }
      if ($classes = $fields[$field]->element_classes($num)) {
        if ($variables['field_classes'][$field][$num]) {
          $variables['field_classes'][$field][$num] .= ' ';
        }

        $variables['field_classes'][$field][$num] .= $classes;
      }
      $variables['field_attributes'][$field][$num] = array();

      if (!empty($fields[$field]) && empty($fields[$field]->options['exclude'])) {
        $field_output = $renders[$num][$field];
        $element_type = $fields[$field]->element_type(TRUE, TRUE);
        if ($element_type) {
          $field_output = '<' . $element_type . '>' . $field_output . '</' . $element_type . '>';
        }

        // Don't bother with separators and stuff if the field does not show up.
        if (empty($field_output) && !empty($variables['rows'][$num][$column])) {
          continue;
        }

        // Place the field into the column, along with an optional separator.
        if (!empty($variables['rows'][$num][$column])) {
          if (!empty($options['info'][$column]['separator'])) {
            $variables['rows'][$num][$column] .= filter_xss_admin($options['info'][$column]['separator']);
          }
        }
        else {
          $variables['rows'][$num][$column] = '';
        }

        $variables['rows'][$num][$column] .= $field_output;
      }
    }

    // Remove columns if the option is hide empty column is checked and the field is not empty.
    if (!empty($options['info'][$field]['empty_column'])) {
      $empty = TRUE;
      foreach ($variables['rows'] as $num => $columns) {
        $empty &= empty($columns[$column]);
      }
      if ($empty) {
        foreach ($variables['rows'] as $num => &$column_items) {
          unset($column_items[$column]);
          unset($variables['header'][$column]);
        }
      }
    }
  }

  // Hide table header if all labels are empty.
  if (!array_filter($variables['header'])) {
    $variables['header'] = array();
  }

  $count = 0;
  foreach ($variables['rows'] as $num => $row) {
    $variables['row_classes'][$num] = array();
    if ($row_class_special) {
      $variables['row_classes'][$num][] = ($count++ % 2 == 0) ? 'odd' : 'even';
    }
    if ($row_class = $handler->get_row_class($num)) {
      $variables['row_classes'][$num][] = $row_class;
    }
    if ($vertical_modifier) {
      $variables['row_classes'][$num][] = 'uk-table-middle';
    }
  }

  if ($row_class_special) {
    $variables['row_classes'][0][] = 'views-row-first';
    $variables['row_classes'][count($variables['row_classes']) - 1][] = 'views-row-last';
  }

  $variables['attributes_array']['class'] = array('uk-table');
  if (empty($variables['rows']) && !empty($options['empty_table'])) {
    $variables['rows'][0][0] = $view->display_handler->render_area('empty');
    // Calculate the amounts of rows with output.
    $variables['field_attributes'][0][0]['colspan'] = count($variables['header']);
    $variables['field_classes'][0][0] = 'views-empty';
  }

  $variables['responsive_table'] = FALSE;
  if ($responsive) {
    $variables['responsive_table'] = TRUE;
  }

  foreach ($table_modifiers as $key => $table_modifier) {
    if ($table_modifier) {
      $variables['attributes_array']['class'][] = 'uk-table-' . $key;
    }
  }

  if (!empty($options['sticky'])) {
    drupal_add_js('misc/tableheader.js');
    $variables['attributes_array']['class'][] = "sticky-enabled";
  }
  $variables['attributes_array']['class'][] = 'cols-' . count($variables['header']);

  // Add the summary to the list if set.
  if (!empty($handler->options['summary'])) {
    //$variables['attributes_array'] = array('summary' => filter_xss_admin($handler->options['summary']));
  }

  // Add the caption to the list if set.
  if (!empty($handler->options['caption'])) {
    $variables['caption'] = filter_xss_admin($handler->options['caption']);
  }
  else {
    $variables['caption'] = '';
  }
}
