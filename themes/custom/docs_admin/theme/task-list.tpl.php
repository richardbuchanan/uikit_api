<?php

/**
 * @file
 * Returns HTML for a list of maintenance tasks to perform.
 */

$items = $variables['items'];
$active = $variables['active'];

$done = isset($items[$active]) || $active == NULL;
$output = '<h2 class="element-invisible">Installation tasks</h2>';
$output .= '<div class="uk-panel uk-panel-box uk-margin-top docs-panel-box">';
$output .= '<ul class="uk-nav uk-nav-side docs-nav-side">';

foreach ($items as $k => $item) {
  if ($active == $k) {
    $class = 'uk-active';
    $status = '(' . t('active') . ')';
    $done = FALSE;
  }
  else {
    $class = $done ? 'done' : '';
    $status = $done ? '(' . t('done') . ')' : '';
  }
  $item = $done ? '<a><i class="uk-icon-check"></i> ' . $item . '</a>' : '<a>' . $item . '</a>';
  $output .= '<li';
  $output .= ($class ? ' class="' . $class . '"' : '') . '>';
  $output .= $item;
  $output .= ($status ? '<span class="element-invisible">' . $status . '</span>' : '');
  $output .= '</li>';
}
$output .= '</ul>';
$output .= '</div>';
print $output;
