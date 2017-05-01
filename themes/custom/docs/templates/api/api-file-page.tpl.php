<?php

/**
 * @file
 * Displays an API page for a file and the objects defined in it.
 *
 * Available variables:
 * - $alternatives: List of alternate versions (branches) of this file.
 * - $documentation: Documentation from the comment header of the file.
 * - $see: See also documentation.
 * - $deprecated: Deprecated documentation.
 * - $namespace: Name of the namespace for this function, if any.
 * - $objects: List of functions, classes, etc. defined in the file.
 * - $call_links: Links to calling functions (for theme templates).
 * - $code: Source code for the file.
 * - $related_topics: List of related groups/topics.
 * - $defined: Location of the file.
 * - $branch: Object with information about the branch.
 * - $object: Object with information about the file.
 *
 * Available variables in the $branch object:
 * - $branch->project: The machine name of the branch.
 * - $branch->title: A proper title for the branch.
 * - $branch->directories: The local included directories.
 * - $branch->excluded_directories: The local excluded directories.
 *
 * Available variables in the $object object:
 * - $object->title: Display name.
 * - $object->object_type: For this template it will be 'file'.
 * - $object->branch_id: An identifier for the branch.
 * - $object->file_name: The path to the file in the source.
 * - $object->summary: A one-line summary of the object.
 * - $object->code: Escaped source code.
 * - $object->see: HTML-formatted additional references.
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
  
  <?php if (!empty($documentation)): ?>
    <div id="docs-api-documentation">
      <?php print $documentation ?>
    </div>
    <hr>
  <?php endif; ?>
  
  <?php if ($namespace) : ?>
    <div id="docs-api-namespace">
      <a href="#namespace" class="uk-link-muted docs-link-anchor">
        <h3 id="namespace"><?php print t('Namespace'); ?><i class="uk-icon uk-icon-link uk-text-muted"></i></h3>
      </a>
      <?php print $namespace; ?>
    </div>
    <hr>
  <?php endif; ?>
  
  <?php if (!empty($deprecated)): ?>
    <div id="docs-api-deprecated" class="uk-alert uk-alert-warning">
      <a href="#deprecated" class="uk-link-muted docs-link-anchor">
        <h3 id="deprecated"><?php print t('Deprecated') ?><i class="uk-icon uk-icon-link uk-text-muted"></i></h3>
      </a>
      <?php print $deprecated ?>
    </div>
    <hr>
  <?php endif; ?>

  <?php if (!empty($see)): ?>
    <div id="docs-api-see-also">
      <a href="#see-also" class="uk-link-muted docs-link-anchor">
        <h3 id="see-also" class="uk-panel-title"><?php print t('See also') ?><i class="uk-icon uk-icon-link uk-text-muted"></i></h3>
      </a>
      <ul class="uk-list">
        <?php print $see ?>
      </ul>
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
    </a>
    <span><?php print $defined; ?></span>

    <?php print theme('ctools_collapsible', array(
      'handle' => t('View source'),
      'content' => $code,
      'collapsed' => TRUE,
    )); ?>
  </div>
  <hr>
  
  <?php if (!empty($related_topics)): ?>
    <div id="docs-api-related-topics">
      <a href="#related-topics" class="uk-link-muted docs-link-anchor">
        <h3 id="related-topics"><?php print t('Related topics') ?><i class="uk-icon uk-icon-link uk-text-muted"></i></h3>
      </a>
      <?php print $related_topics ?>
    </div>
    <hr>
  <?php endif; ?>
  
  <?php if (!empty($objects)): ?>
    <div id="docs-api-objects" class="uk-margin-top">
      <?php print $objects; ?>
    </div>
    <hr>
  <?php endif; ?>
</div>
