<?php

/**
 * @file
 * Theme implementation to show forum legend.
 */
?>

<div class="uk-panel uk-panel-box uk-panel-box-secondary uk-margin docs-legend">
  <h3 class="uk-panel-title">Topic legend</h3>
  <div class="uk-margin-top uk-position-relative">
    <i class="uk-icon uk-icon-comments uk-icon-medium uk-text-primary"></i>
    <i class="uk-icon uk-icon-plus uk-position-absolute uk-contrast docs-icon-mini"></i>
    <span class="uk-margin-small-left uk-vertical-align-middle"><?php print t(' New posts'); ?></span>
  </div>
  <div class="uk-margin-top">
    <i class="uk-icon uk-icon-comments uk-icon-medium uk-text-primary"></i>
    <span class="uk-margin-small-left uk-vertical-align-middle"><?php print t(' No new posts'); ?></span>
  </div>

  <div class="uk-margin-top uk-position-relative">
    <i class="uk-icon uk-icon-comments uk-icon-medium uk-text-success"></i>
    <i class="uk-icon uk-icon-plus uk-position-absolute uk-contrast docs-icon-mini"></i>
    <span class="uk-margin-small-left uk-vertical-align-middle"><?php print t(' Hot topic with new posts'); ?></span>
  </div>
  <div class="uk-margin-top">
    <i class="uk-icon uk-icon-comments uk-icon-medium uk-text-success"></i>
    <span class="uk-margin-small-left uk-vertical-align-middle"><?php print t(' Hot topic without new posts'); ?></span>
  </div>

  <div class="uk-margin-top uk-position-relative">
    <i class="uk-icon uk-icon-comments uk-icon-medium"></i>
    <i class="uk-icon uk-icon-thumb-tack uk-position-absolute uk-contrast docs-icon-mini"></i>
    <span class="uk-margin-small-left uk-vertical-align-middle"><?php print t(' Sticky topic'); ?></span>
  </div>

  <div class="uk-margin-top uk-position-relative">
    <i class="uk-icon uk-icon-comments uk-icon-medium uk-text-danger"></i>
    <i class="uk-icon uk-icon-lock uk-position-absolute uk-contrast docs-icon-mini"></i>
    <span class="uk-margin-small-left uk-vertical-align-middle"><?php print t(' Locked topic'); ?></span>
  </div>
</div>
