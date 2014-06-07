<?php

/**
 * @file
 * Class definition of IslandoraFeedsFeedsNodeProcessor. Nodes are
 * not created for Islandora objects created by this processor.
 * 
 * @todo:
     -Filter out content models in the config settings form that don't make sense.
 *   -Figure out how to handle thumbnails.
 *   -Figure out how to support deleting content loaded via this module.
 *   -Figure out object validation.
 */

/**
 * Creates Islandora object from feed items.
 */
class IslandoraFeedsFeedsNodeProcessor extends FeedsProcessor {

  /**
   * Define entity type.
   */
  public function entityType() {
    return 'node';
  }

  /**
   * Implements parent::entityInfo().
   */
  protected function entityInfo() {
    $info = parent::entityInfo();
    $info['label plural'] = t('Islandora objects');
    return $info;
  }

  /**
   * Creates a new node in memory and returns it.
   */
  protected function newEntity(FeedsSource $source) {
    $node = new stdClass();
    $node->type = $this->bundle();
    $node->changed = REQUEST_TIME;
    $node->created = REQUEST_TIME;
    $node->language = LANGUAGE_NONE;
    $node->is_new = TRUE;
    node_object_prepare($node);
    // Populate properties that are set by node_object_prepare().
    $node->log = 'Created by FeedsNodeProcessor';
    $node->uid = $this->config['author'];
    return $node;
  }

  /**
   * Check that the user has permission to save a node.
   */
  protected function entitySaveAccess($entity) {
    $access = user_access('administer site configuration');
  }

  /**
   * Validates a node.
   */
  protected function entityValidate($entity) {
    if (!isset($entity->uid) || !is_numeric($entity->uid)) {
       $entity->uid = $this->config['author'];
    }
  }

  /**
   * Save a node.
   */
  public function entitySave($entity) {
    node_save($entity);
  }

  /**
   * Delete a series of nodes.
   * 
   * Currently unsupported.
   */
  protected function entityDeleteMultiple($nids) {
    node_delete_multiple($nids);
  }

  /**
   * Implement expire().
   * 
   * @todo: Figure out best way to determine age of Islandora objects.
   *   Only applies if we support deletions.
   */
  public function expire($time = NULL) {
    return FEEDS_BATCH_COMPLETE;
  }

  /**
   * Return expiry time.
   */
  public function expiryTime() {
    return $this->config['expire'];
  }

  /**
   * Override parent::configDefaults().
   */
  public function configDefaults() {
    return array(
      'collection' => 'islandora:root',
      'cmodel' => 'fedora-system:ContentModel-3.0',
      'namespace' => 'islandora',
      'keepnodes' => FALSE,
      'expire' => FEEDS_EXPIRE_NEVER,
      'author' => 0,
      'authorize' => TRUE,
      'dsid' => 'DATA',
      'dslabel' => 'Change me',
    ) + parent::configDefaults();
  }

  /**
   * Override parent::configForm().
   */
  public function configForm(&$form_state) {
    $form = parent::configForm($form_state);

    // We currently don't support updates.
    unset($form['update_existing']);
    unset($form['skip_hash_check']);
    // Islandora objects don't have bodies.
    unset($form['input_format']);

    module_load_include('inc', 'islandora_feeds', 'includes/utilities');
    $collections = islandora_feeds_get_collections_or_content_models('collections');
    $form['collection'] = array(
      '#type' => 'select',
      '#title' => t('Target collection'),
      '#options' => $collections,
      '#description' => t("The Islandora collection you want to import into."),
      '#default_value' => $this->config['collection'],
      '#required' => TRUE,
    );

    $cmodels = islandora_feeds_get_collections_or_content_models('cmodels');
    $form['cmodel'] = array(
      '#type' => 'select',
      '#title' => t('Target content model'),
      '#options' => $cmodels,
      '#description' => t("The Islandora content model you want to import into."),
      '#default_value' => $this->config['cmodel'],
      '#required' => TRUE,
    );

    $form['namespace'] = array(
      '#type' => 'textfield',
      '#title' => t('Namespace'),
      '#description' => t('The PID namespace to use for the imported objects.'),
      '#default_value' => $this->config['namespace'],
      '#required' => TRUE,
    );

    $form['keepnodes'] = array(
      '#type' => 'checkbox',
      '#title' => t('Keep nodes'),
      '#description' => t('Keep the nodes that are created corresponding to the Islandora objects. Uncheck to automatically delete the nodes.'),
      '#default_value' => $this->config['keepnodes'],
    );

    $form['dsid'] = array(
      '#type' => 'textfield',
      '#title' => t('Datastream ID'),
      '#description' => t('DSID of the XML datastream that will hold the imported content.'),
      '#default_value' => $this->config['dsid'],
    );

    $form['dslabel'] = array(
      '#type' => 'textfield',
      '#title' => t('Datastream label'),
      '#description' => t('Label of the XML datastream that will hold the imported content.'),
      '#default_value' => $this->config['dslabel'],
    );

    $author = user_load($this->config['author']);
    $form['author'] = array(
      '#type' => 'textfield',
      '#title' => t('Author'),
      '#description' => t('Select the author of the nodes to be created - leave empty to assign "anonymous".'),
      '#autocomplete_path' => 'user/autocomplete',
      '#default_value' => empty($author->name) ? 'anonymous' : check_plain($author->name),
    );
    $form['authorize'] = array(
      '#type' => 'checkbox',
      '#title' => t('Authorize'),
      '#description' => t('Check that the author has permission to create the node.'),
      '#default_value' => $this->config['authorize'],
    );
    $period = drupal_map_assoc(array(FEEDS_EXPIRE_NEVER, 3600, 10800, 21600, 43200, 86400, 259200, 604800, 2592000, 2592000 * 3, 2592000 * 6, 31536000), 'feeds_format_expire');
    $form['expire'] = array(
      '#type' => 'select',
      '#title' => t('Expire nodes'),
      '#options' => $period,
      '#description' => t("Select after how much time nodes should be deleted. The node's published date will be used for determining the node's age, see Mapping settings."),
      '#default_value' => $this->config['expire'],
    );
    return $form;
  }

  /**
   * Override parent::configFormValidate().
   */
  public function configFormValidate(&$values) {
    if ($author = user_load_by_name($values['author'])) {
      $values['author'] = $author->uid;
    }
    else {
      $values['author'] = 0;
    }
  }

  /**
   * Reschedule if expiry time changes.
   */
  public function configFormSubmit(&$values) {
    if ($this->config['expire'] != $values['expire']) {
      feeds_reschedule($this->id);
    }
    parent::configFormSubmit($values);
  }

  /**
   * Override setTargetElement to operate on a target item that is a node.
   */
  public function setTargetElement(FeedsSource $source, $target_node, $target_element, $value) {
    switch ($target_element) {
      case 'created':
        $target_node->created = feeds_to_unixtime($value, REQUEST_TIME);
        break;

      case 'feeds_source':
        // Get the class of the feed node importer's fetcher and set the source
        // property. See feeds_node_update() how $node->feeds gets stored.
        if ($id = feeds_get_importer_id($this->bundle())) {
          $class = get_class(feeds_importer($id)->fetcher);
          $target_node->feeds[$class]['source'] = $value;
          // This effectively suppresses 'import on submission' feature.
          // See feeds_node_insert().
          $target_node->feeds['suppress_import'] = TRUE;
        }
        break;

      // @todo: do we need user_name and user_mail?
      case 'user_name':
        if ($user = user_load_by_name($value)) {
          $target_node->uid = $user->uid;
        }
        break;

      case 'user_mail':
        if ($user = user_load_by_mail($value)) {
          $target_node->uid = $user->uid;
        }
        break;

      default:
        parent::setTargetElement($source, $target_node, $target_element, $value);
        break;
    }
  }

  /**
   * Return available mapping targets.
   */
  public function getMappingTargets() {
    $type = node_type_get_type($this->bundle());
    $targets = parent::getMappingTargets();

    if ($type && $type->has_title) {
      $targets['title'] = array(
        'name' => t('Title'),
        'description' => t('The title of the node.'),
        'optional_unique' => TRUE,
      );
    }
    $targets['nid'] = array(
      'name' => t('Node ID'),
      'description' => t('The nid of the node. NOTE: use this feature with care, node ids are usually assigned by Drupal.'),
      'optional_unique' => TRUE,
    );
    $targets['uid'] = array(
      'name' => t('User ID'),
      'description' => t('The Drupal user ID of the node author.'),
    );
    $targets['user_name'] = array(
      'name' => t('Username'),
      'description' => t('The Drupal username of the node author.'),
    );
    $targets['user_mail'] = array(
      'name' => t('User email'),
      'description' => t('The email address of the node author.'),
    );
    $targets['status'] = array(
      'name' => t('Published status'),
      'description' => t('Whether a node is published or not. 1 stands for published, 0 for not published.'),
    );
    $targets['created'] = array(
      'name' => t('Published date'),
      'description' => t('The UNIX time when a node has been published.'),
    );
    $targets['promote'] = array(
      'name' => t('Promoted to front page'),
      'description' => t('Boolean value, whether or not node is promoted to front page. (1 = promoted, 0 = not promoted)'),
    );
    $targets['sticky'] = array(
      'name' => t('Sticky'),
      'description' => t('Boolean value, whether or not node is sticky at top of lists. (1 = sticky, 0 = not sticky)'),
    );

    // Include language field if Locale module is enabled.
    if (module_exists('locale')) {
      $targets['language'] = array(
        'name' => t('Language'),
        'description' => t('The two-character language code of the node.'),
      );
    }

    // Include comment field if Comment module is enabled.
    if (module_exists('comment')) {
      $targets['comment'] = array(
        'name' => t('Comments'),
        'description' => t('Whether comments are allowed on this node: 0 = no, 1 = read only, 2 = read/write.'),
      );
    }

    // If the target content type is a Feed node, expose its source field.
    if ($id = feeds_get_importer_id($this->bundle())) {
      $name = feeds_importer($id)->config['name'];
      $targets['feeds_source'] = array(
        'name' => t('Feed source'),
        'description' => t('The content type created by this processor is a Feed Node, it represents a source itself. Depending on the fetcher selected on the importer "@importer", this field is expected to be for example a URL or a path to a file.', array('@importer' => $name)),
        'optional_unique' => TRUE,
      );
    }

    // Let other modules expose mapping targets.
    self::loadMappers();
    $entity_type = $this->entityType();
    $bundle = $this->bundle();
    drupal_alter('feeds_processor_targets', $targets, $entity_type, $bundle);

    return $targets;
  }
}

/**
 * Implements hook_feeds_after_save().
 */
function islandora_feeds_feeds_after_save(FeedsSource $source, $entity, $item, $entity_id) {
  // Get feeds config options.
  $config = $source->importer->getConfig();
  $processor_config = $config['processor']['config'];
  $namespace = $processor_config['namespace'];
  $dsid = $processor_config['dsid'];
  $ds_label = $processor_config['dslabel'];
  $cmodel = $processor_config['cmodel'];
  $collection = $processor_config['collection'];

  module_load_include('inc', 'islandora_feeds', 'includes/utilities');
  islandora_feeds_ingest_object($entity, $item, $namespace, $dsid, $ds_label, $xml_ds, $cmodel, $collection);

  if ($processor_config['keepnodes']) {
    drupal_set_message(t('Nodes have been kept.'), 'status', FALSE);
  }
  else {
    node_delete($entity->nid);
  }
}

