<?php

/**
 * @file
 * Theme implementation to show forum legend.
 */
?>
<div class="uk-panel uk-panel-box uk-panel-box-secondary uk-margin">
  <h3 class="uk-panel-title">Forum legend</h3>
  <div class="uk-margin-top">
    <span class="uk-badge uk-badge-success">
      <i class="uk-icon uk-icon-star uk-icon-medium"></i>
    </span>
    <span class="uk-margin-small-left uk-vertical-align-middle"><?php print t('New posts'); ?></span>
  </div>

  <div class="uk-margin-top">
    <span class="uk-badge">
      <i class="uk-icon uk-icon-star uk-icon-medium"></i>
    </span>
    <span class="uk-margin-small-left uk-vertical-align-middle"><?php print t('No new posts'); ?></span>
  </div>
</div>
