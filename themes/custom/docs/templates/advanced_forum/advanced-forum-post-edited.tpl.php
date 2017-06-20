<?php

/**
 * @file
 * advanced-forum.naked.post-edited.tpl.php
 */
?>

<div class="uk-margin-top uk-margin-bottom">
  <span class="post-edit-label"><?php print t('Edited by'); ?>:</span> <?php print $edited_name; ?>
  <span class="post-edit-label"> <?php print t('on'); ?> </span> <?php print $edited_datetime; ?>
  <?php if (!empty($edited_reason)) : ?>
    <span class="post-edit-label"> <?php print t('Reason'); ?>:</span> <?php print $edited_reason; ?>
  <?php endif; ?>
</div>
