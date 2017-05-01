<?php

/**
 * @file
 * Displays an API page for a service, including a list of tags.
 *
 * Available variables:
 * - $alternatives: List of alternate versions (branches) of this class.
 * - $defined: HTML reference to file that defines this service.
 * - $code: HTML-formatted declaration and code for this service.
 * - $tags: List of tags for this service.
 * - $branch: Object with information about the branch.
 * - $object: Object with information about the service.
 * - $call_links: Links to references.
 *
 * Available variables in the $branch object:
 * - $branch->project: The machine name of the branch.
 * - $branch->title: A proper title for the branch.
 * - $branch->directories: The local included directories.
 * - $branch->excluded_directories: The local excluded directories.
 *
 * Available variables in the $object object:
 * - $object->title: Display name.
 * - $object->object_type: For this template it will be 'service'.
 * - $object->branch_id: An identifier for the branch.
 * - $object->file_name: The path to the file in the source.
 * - $object->summary: A one-line summary of the object.
 * - $object->code: Escaped source code.
 *
 * @see api_preprocess_api_object_page()
 *
 * @ingroup themeable
 */
?>

<div id="docs-api">
  <?php if (!empty($alternatives)): ?>
    <div id="docs-api-alternatives">
      <?php print $alternatives; ?>
    </div>
    <hr>
  <?php endif; ?>

  <?php if ($class): ?>
    <div id="docs-api-class">
      <a href="#class" class="uk-link-muted docs-link-anchor">
        <h3 id="class"><?php print t('Class'); ?><i class="uk-icon uk-icon-link uk-text-muted"></i></h3>
      </a>
      <?php print $class; ?>
    </div>
    <hr>
  <?php endif; ?>

  <?php if ($tags): ?>
    <div id="docs-api-tags">
      <a href="#class" class="uk-link-muted docs-link-anchor">
        <h3 id="tags"><?php print t('Tags'); ?><i class="uk-icon uk-icon-link uk-text-muted"></i></h3>
      </a>
      <?php print $tags; ?>
    </div>
    <hr>
  <?php endif; ?>

  <?php if (!empty($call_links)): ?>
    <div id="docs-api-call-links">
      <?php foreach ($call_links as $link): ?>
        <?php print $link; ?>
      <?php endforeach; ?>
    </div>
    <hr>
  <?php endif; ?>

  <div id="docs-api-file">
    <a href="#file" class="uk-link-muted docs-link-anchor">
      <h3 id="file"><?php print t('File'); ?><i class="uk-icon uk-icon-link uk-text-muted"></i></h3>
    </a><br>
    <span><?php print $defined; ?></span>

    <div>
      <?php print theme('ctools_collapsible', array(
        'handle' => t('View source'),
        'content' => $code,
        'collapsed' => TRUE,
      )); ?>
    </div>
  </div>
  <hr>
</div>
