<?php

/**
 * @file
 * Displays an API page for a function.
 *
 * Available variables:
 * - $signatures: Function signatures for this and other branches.
 * - $documentation: Documentation from the comment header of the function.
 * - $parameters: Function parameter documentation.
 * - $return: Function return value documentation.
 * - $override: If this is an override, the text to show for that.
 * - $throws: Documentation of thown exceptions.
 * - $class: If this is a method, the text for the class section.
 * - $see: See also documentation.
 * - $deprecated: Deprecated documentation.
 * - $related_topics: Related topics documentation.
 * - $call_links: Links to calling functions, hook implementations, etc.
 * - $defined: HTML reference to file that defines this function.
 * - $namespace: Name of the namespace for this function, if any.
 * - $code: HTML-formatted declaration and code of this function.
 * - $branch: Object with information about the branch.
 * - $object: Object with information about the function.
 * - $defined: HTML reference to file that defines this function.
 *
 * Available variables in the $branch object:
 * - $branch->project: The machine name of the branch.
 * - $branch->title: A proper title for the branch.
 * - $branch->directories: The local included directories.
 * - $branch->excluded_directories: The local excluded directories.
 *
 * Available variables in the $object object:
 * - $object->title: Display name.
 * - $object->return: What the function returns.
 * - $object->parameters: The function parameters.
 * - $object->related_topics: Related information about the function.
 * - $object->object_type: For this template it will be 'function'.
 * - $object->branch_id: An identifier for the branch.
 * - $object->file_name: The path to the file in the source.
 * - $object->summary: A one-line summary of the object.
 * - $object->code: Escaped source code.
 * - $object->see: HTML index of additional references.
 * - $object->throws: Paragraph describing possible exceptions.
 *
 * @see api_preprocess_api_object_page()
 *
 * @ingroup uikit_themeable
 */
?>
<div id="api-function-signatures">
  <?php foreach ($signatures as $signature): ?>
    <table class="uk-margin-small-bottom">
      <tbody>
        <tr>
          <?php if ($signature['active']): ?>
            <td class="uk-text-bold uk-text-right uk-text-nowrap"><?php print $signature['label']; ?></td>
            <td><code class="uk-margin-small-left"><?php print $signature['signature']; ?></code></td>
          <?php else: ?>
            <td class="uk-text-right uk-text-nowrap"><?php print l($signature['label'], $signature['url'], array(
                'attributes' => array(
                  'class' => array('uk-text-muted'),
                ),
                'html' => TRUE,
              )); ?></td>
            <td><code class="uk-text-muted uk-margin-small-left"><?php print $signature['signature']; ?></code></td>
          <?php endif; ?>
        </tr>
      </tbody>
    </table>
  <?php endforeach; ?>
  <hr>
</div>

<div id="docs-api">
  <?php if (!empty($documentation)): ?>
    <div id="docs-api-documentation">
      <?php print $documentation ?>
    </div>
    <hr>
  <?php endif; ?>

  <?php if (!empty($parameters)): ?>
    <div id="docs-api-parameters">
      <a href="#parameters" class="uk-link-muted docs-link-anchor">
        <h3 id="parameters"><?php print t('Parameters') ?><i class="uk-icon uk-icon-link uk-text-muted"></i></h3>
      </a>
      <?php print $parameters ?>
    </div>
    <hr>
  <?php endif; ?>

  <?php if (!empty($return)): ?>
    <div id="docs-api-return-value">
      <a href="#return-value" class="uk-link-muted docs-link-anchor">
        <h3 id="return-value"><?php print t('Return value') ?><i class="uk-icon uk-icon-link uk-text-muted"></i></h3>
      </a>
      <?php print $return ?>
    </div>
    <hr>
  <?php endif; ?>

  <?php if (!empty($throws)): ?>
    <div id="docs-api-throws">
      <a href="#throws" class="uk-link-muted docs-link-anchor">
        <h3 id="throws"><?php print t('Throws') ?><i class="uk-icon uk-icon-link uk-text-muted"></i></h3>
      </a>
      <?php print $throws ?>
    </div>
    <hr>
  <?php endif; ?>

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
