<?php

/**
 * @file
 * Returns HTML for a query pager.
 *
 * Available variables:
 * - $variables['tags']: An array of labels for the controls in the pager.
 * - $variables['element']: An optional integer to distinguish between multiple
 *   pagers on one page.
 * - $variables['parameters']: An associative array of query string parameters
 *   to append to the pager links.
 * - $variables['quantity']: The number of pages in the list.
 *
 * @see theme_pager()
 *
 * @ingroup uikit_themeable
 */

$tags = $variables['tags'];
$element = $variables['element'];
$parameters = $variables['parameters'];
$quantity = $variables['quantity'];
global $pager_page_array;
global $pager_total;

// Middle is used to "center" pages around the current page.
$pager_middle = ceil($quantity / 2);

// Current is the page we are currently paged to.
$pager_current = $pager_page_array[$element] + 1;

// First is the first page listed by this pager piece (re quantity).
$pager_first = $pager_current - $pager_middle + 1;

// Last is the last page listed by this pager piece (re quantity).
$pager_last = $pager_current + $quantity - $pager_middle;

// Max is the maximum page number.
$pager_max = $pager_total[$element];

// Prepare for generation loop.
$i = $pager_first;
if ($pager_last > $pager_max) {
  // Adjust "center" if at end of query.
  $i = $i + ($pager_max - $pager_last);
  $pager_last = $pager_max;
}
if ($i <= 0) {
  // Adjust "center" if at start of query.
  $pager_last = $pager_last + (1 - $i);
  $i = 1;
}

$li_first = theme('pager_first', array(
  'text' => t('<span><i class="uk-icon-angle-double-left"></i> First</span>'),
  'element' => $element,
  'parameters' => $parameters,
));

$li_previous = theme('pager_previous', array(
  'text' => t('<span><i class="uk-icon-angle-left"></i> Previous</span>'),
  'element' => $element,
  'interval' => 1,
  'parameters' => $parameters,
));

$li_next = theme('pager_next', array(
  'text' => t('<span>Next <i class="uk-icon-angle-right"></i></span>'),
  'element' => $element,
  'interval' => 1,
  'parameters' => $parameters,
));

$li_last = theme('pager_last', array(
  'text' => t('<span>Last <i class="uk-icon-angle-double-right"></i></span>'),
  'element' => $element,
  'parameters' => $parameters,
));

if ($pager_total[$element] > 1) {
  if ($li_first) {
    $items[] = array(
      'class' => array('pager-first'),
      'data' => $li_first,
    );
  }
  if ($li_previous) {
    $items[] = array(
      'class' => array('pager-previous'),
      'data' => $li_previous,
    );
  }

  // When there is more than one page, create the pager list.
  if ($i != $pager_max) {
    if ($i > 1) {
      $items[] = array(
        'class' => array('pager-ellipsis'),
        'data' => '…',
      );
    }
    // Now generate the actual pager piece.
    for (; $i <= $pager_last && $i <= $pager_max; $i++) {
      if ($i < $pager_current) {
        $items[] = array(
          'class' => array('pager-item'),
          'data' => theme('pager_previous', array(
            'text' => $i,
            'element' => $element,
            'interval' => ($pager_current - $i),
            'parameters' => $parameters,
          )),
        );
      }
      if ($i == $pager_current) {
        $items[] = array(
          'class' => array('pager-current', 'uk-active'),
          'data' => '<span>' . $i . '</span>',
        );
      }
      if ($i > $pager_current) {
        $items[] = array(
          'class' => array('pager-item'),
          'data' => theme('pager_next', array(
            'text' => $i,
            'element' => $element,
            'interval' => ($i - $pager_current),
            'parameters' => $parameters,
          )),
        );
      }
    }
    if ($i < $pager_max) {
      $items[] = array(
        'class' => array('pager-ellipsis'),
        'data' => '<span>…</span>',
      );
    }
  }

  if ($li_next) {
    $items[] = array(
      'class' => array('pager-next'),
      'data' => $li_next,
    );
  }

  if ($li_last) {
    $items[] = array(
      'class' => array('pager-last'),
      'data' => $li_last,
    );
  }

  print '<h2 class="element-invisible">' . t('Pages') . '</h2>' . theme('item_list', array(
    'items' => $items,
    'attributes' => array('class' => array('uk-pagination')),
  ));
}
