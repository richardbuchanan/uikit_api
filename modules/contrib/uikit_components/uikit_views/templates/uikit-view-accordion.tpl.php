<?php

/**
 * @file
 * Template to display a view as a UIkit Grid component.
 *
 * - $title: The title of this group of rows.  May be empty.
 * - $rows: An array of row items.
 * - $attributes: The attributes to apply to the list wrapper.
 * - $grid_classes: The classes to apply to the list element.
 *
 * @see template_preprocess_uikit_view_grid()
 * @see template_process_uikit_view_grid()
 *
 * @ingroup uikit_views_templates
 */
?>
<?php if (!empty($title)): ?>
  <h3><?php print $title; ?></h3>
<?php endif; ?>

<div<?php print $accordion_attributes; ?>>
  <?php foreach ($items as $id => $row): ?>
    <h3 class="uk-accordion-title"><?php print $row['title']; ?></h3>
    <div class="uk-accordion-content"><?php print $row['content']; ?></div>
  <?php endforeach; ?>
</div>
