<?php

/**
 * @file
 * Displays an API page for a class member property.
 *
 * Available variables:
 * - $alternatives: List of alternate versions (branches) of this property.
 * - $override: If this is an override, the text to show for that.
 * - $var: The data type of the property.
 * - $documentation: Documentation from the comment header of the property.
 * - $see: See also documentation.
 * - $deprecated: Deprecated documentation.
 * - $namespace: Name of the namespace for this function, if any.
 * - $defined: HTML reference to file that defines this property.
 * - $class: The text for the class section.
 * - $code: HTML-formatted declaration of this property.
 * - $related_topics: List of related groups/topics.
 * - $branch: Object with information about the branch.
 * - $object: Object with information about the property.
 *
 * Available variables in the $branch object:
 * - $branch->project: The machine name of the branch.
 * - $branch->title: A proper title for the branch.
 * - $branch->directories: The local included directories.
 * - $branch->excluded_directories: The local excluded directories.
 *
 * Available variables in the $object object:
 * - $object->title: Display name.
 * - $object->related_topics: Related information about the function.
 * - $object->object_type: For this template it will be 'property'.
 * - $object->branch_id: An identifier for the branch.
 * - $object->file_name: The path to the file in the source.
 * - $object->summary: A one-line summary of the object.
 * - $object->code: Escaped source code.
 * - $object->see: HTML index of additional references.
 * - $object->var: Type of property.
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

  <?php if (!empty($var)) { ?>
    <div id="docs-api-type">
      <a href="#type" class="uk-link-muted docs-link-anchor">
        <h3 id="type"><?php print t('Type') ?><i class="uk-icon uk-icon-link uk-text-muted"></i></h3>
      </a>
      <p><?php print $var; ?></p>
    </div>
    <hr>
  <?php } ?>

  <?php if (!empty($override)): ?>
    <div id="docs-api-override">
      <?php print $override; ?>
    </div>
    <hr>
  <?php endif; ?>

  <?php if (!empty($deprecated)): ?>
    <div id="docs-api-deprecated">
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

  <div id="docs-api-file">
    <a href="#file" class="uk-link-muted docs-link-anchor">
      <h3 id="file"><?php print t('File'); ?><i class="uk-icon uk-icon-link uk-text-muted"></i></h3>
    </a>
    <?php print $defined; ?>
  </div>
  <hr>

  <?php if ($class): ?>
    <div id="docs-api-class">
      <a href="#class" class="uk-link-muted docs-link-anchor">
        <h3 id="class"><?php print t('Class'); ?><i class="uk-icon uk-icon-link uk-text-muted"></i></h3>
      </a>
      <?php print $class; ?>
    </div>
    <hr>
  <?php endif; ?>

  <?php if ($namespace): ?>
    <div id="docs-api-namespace">
      <a href="#namespace" class="uk-link-muted docs-link-anchor">
        <h3 id="namespace"><?php print t('Namespace'); ?><i class="uk-icon uk-icon-link uk-text-muted"></i></h3>
      </a>
      <?php print $namespace; ?>
    </div>
    <hr>
  <?php endif; ?>

  <div id="docs-api-code">
    <a href="#code" class="uk-link-muted docs-link-anchor">
      <h3 id="code"><?php print t('Code'); ?><i class="uk-icon uk-icon-link uk-text-muted"></i></h3>
    </a>
    <?php print $code; ?>
  </div>
  <hr>
</div>
