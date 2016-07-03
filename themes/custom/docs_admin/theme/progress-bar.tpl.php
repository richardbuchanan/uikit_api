<?php

/**
 * @file
 * Returns HTML for a progress bar.
 */
?>
<div class="progress-wrapper" aria-live="polite">
  <div id="progress" class="uk-progress uk-progress-striped uk-active">
    <div class="uk-progress-bar" style="width: <?php print $percent; ?>%">
      <div class="percentage"><?php print $percent; ?>%</div>
    </div>
  </div>
  <div class="percentage uk-hidden"><?php print $percent; ?>%</div>
  <div class="uk-alert"><?php print $message; ?></div>
</div>
