<?php

/**
 * @file
 * Displays an API page for a class or interface, including list of members.
 *
 * Available variables:
 * - $alternatives: List of alternate versions (branches) of this class.
 * - $documentation: Documentation from the comment header of the class.
 * - $see: See also documentation.
 * - $deprecated: Deprecated documentation.
 * - $namespace: Name of the namespace for this function, if any.
 * - $implements: List of classes that implements this interface, if any.
 * - $hierarchy: Class hierarchy, if any.
 * - $objects: Listing of member variables, constants, and functions.
 * - $defined: HTML reference to file that defines this class.
 * - $code: HTML-formatted declaration and code for this class.
 * - $related_topics: List of related groups/topics.
 * - $call_links: Links to uses of this class, etc.
 * - $branch: Object with information about the branch.
 * - $object: Object with information about the class.
 *
 * Available variables in the $branch object:
 * - $branch->project: The machine name of the branch.
 * - $branch->title: A proper title for the branch.
 * - $branch->directories: The local included directories.
 * - $branch->excluded_directories: The local excluded directories.
 *
 * Available variables in the $object object:
 * - $object->title: Display name.
 * - $object->object_type: For this template it will be 'class'.
 * - $object->branch_id: An identifier for the branch.
 * - $object->file_name: The path to the file in the source.
 * - $object->summary: A one-line summary of the object.
 * - $object->code: Escaped source code.
 * - $object->see: HTML index of additional references.
 *
 * @see api_preprocess_api_object_page()
 *
 * @ingroup uikit_themeable
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

  <?php if ($implements) : ?>
    <div id="docs-api-implements">
      <a href="#implements" class="uk-link-muted docs-link-anchor">
        <h3 id="implements"><?php print t('Implemented by'); ?><i class="uk-icon uk-icon-link uk-text-muted"></i></h3>
      </a>
      <?php print $implements; ?>
    </div>
    <hr>
  <?php endif; ?>

  <?php if (!empty($hierarchy)): ?>
    <div id="docs-api-hierarchy">
      <a href="#hierarchy" class="uk-link-muted docs-link-anchor">
        <h3 id="hierarchy"><?php print t('Hierarchy'); ?><i class="uk-icon uk-icon-link uk-text-muted"></i></h3>
      </a>
      <?php print $hierarchy; ?>
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

  <?php if (!empty($related_topics)): ?>
    <div id="docs-api-related-topics">
      <a href="#related-topics" class="uk-link-muted docs-link-anchor">
        <h3 id="related-topics"><?php print t('Related topics') ?><i class="uk-icon uk-icon-link uk-text-muted"></i></h3>
      </a>
      <?php print $related_topics ?>
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

    <div>
      <?php print theme('ctools_collapsible', array(
        'handle' => t('View source'),
        'content' => $code,
        'collapsed' => TRUE,
      )); ?>
    </div>
  </div>
  <hr>

  <?php if ($namespace): ?>
    <div id="docs-api-namespace">
      <a href="#namespace" class="uk-link-muted docs-link-anchor">
        <h3 id="namespace"><?php print t('Namespace'); ?><i class="uk-icon uk-icon-link uk-text-muted"></i></h3>
      </a>
      <?php print $namespace; ?>
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
