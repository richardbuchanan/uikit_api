<?php

/**
 * @file
 * Template to display a view as a UIkit List component.
 *
 * - $title: The title of this group of rows.  May be empty.
 * - $classes: The attributes to apply to the outer view wrapper.
 * - $wrapper_attributes: The attributes to apply to the inner view wrapper.
 * - $list_attributes: The attributes to apply to the list.
 * - $rows: An array of row items.
 *
 * @see template_preprocess_uikit_view_list()
 * @see template_process_uikit_view_list()
 *
 * @ingroup uikit_views_templates
 */
?>
<div class="<?php print $classes; ?>">
  <div<?php print $wrapper_attributes; ?>>
    <?php if (!empty($title)) : ?>
      <h3><?php print $title; ?></h3>
    <?php endif; ?>
    <ul<?php print $list_attributes; ?>>
      <?php foreach ($rows as $id => $row): ?>
        <li><?php print $row; ?></li>
      <?php endforeach; ?>
    </ul>
  </div>
</div>
