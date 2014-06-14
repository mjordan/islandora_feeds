<?php
/**
 * @file
 * This is the template file for the default Islandora Feeds object page.
 */
?>
<div class="islandora-feeds-object islandora">
  <div class="islandora-feeds-content-wrapper clearfix">
    <?php if (isset($islandora_content)): ?>
      <div class="islandora-feeds-content">
        <pre>
        <?php print $islandora_content; ?>
        </pre>
      </div>
    <?php endif; ?>
  </div>

