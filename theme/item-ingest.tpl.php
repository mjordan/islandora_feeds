<?php
/**
 * @file
 * This is the ingest template file for the default Islandora Feeds object page.
 */
?>

<fielddata>
 <title label="Title"><?php print $title; ?></title>
 <?php foreach($variables['field_data'] as $field_data): ?>
   <?php foreach($field_data['field_value'] as $field_instance): ?>
     <<?php print $field_data['field_name']; ?> label="<?php print $field_data['field_label']; ?>"><?php print htmlspecialchars(trim($field_instance['value'])); ?> </<?php print $field_data['field_name']; ?>>
   <?php endforeach; ?>
 <?php endforeach; ?>
</fielddata>

