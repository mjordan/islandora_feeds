# Islandora Feeds Importer

## Introduction

This module allows users to create Islandora objects using the Feeds contrib module. This is still a very early proof-of-concept module.

## Requirements

[Feeds](https://drupal.org/project/feeds)

## Installation

Install as usual, see [this](https://drupal.org/documentation/install/modules-themes/modules-7) for further information.

## Usage

This module provides a Feeds processor that creates Islandora objects. Currently, the only datastream that is created is an XML file that contains elements mirroring the column headings in the CSV file (or equivalent in other input formats) you are loading using Feeds, with element values that correspond to the values in the columns. Also, this module only imports data, it doesn't provide any way to view the imported data (other than by using Islandora's links to the imported datastream in the object's "Datastreams" tab.

The Processor provided by this module is similar to other Feeds processors. It uses a version of Feeds' Node processor to create a node for each item you are importing. Each node then serves as the source of the Islandora object that is created. You have the option of saving these nodes (for quality assurance) or deleting them immediately after the Islandora object is created.

For each content model you are importing objects into, you need to create a Drupal content type that contains all the fields corresponding to the data in your incoming Feed source. The nodes created during the import are instances of this content type.

After you have created your content type, conigure your Feed importer by going to Structure > Feeds importers > Add impoter and create a new importer. Attach your content type to the importer. Then edit the importer. The only settings you need to configure are the Processor settings. Under the Processor settings, select the Islandora Feeds node processor, and save. Then in the Processor Mappings, map the fields in your CSV (or similar) source to fields in your target content type.

Be sure to select the correct Islandora content model, collection, datastream ID, and datastream label. Also, you have the option to keep the nodes created during the import or have them deleted automatically. Note that these nodes do not have any relationship to the objects ingested into Fedora after the import is complete - they are only used as the source of the ingest and are not synchronized with the objects after the import. 

You should map one of the fields in your source to Title in your target. The only other columns in your source you need to map are the ones you have defined in your target content type - you do not need to map any of the node properties unless you want to.

Once you have configured the importer, you're ready to import your source conent. 

## To do

* Add the ability to inspect/edit/etc. nodes before ingesting the objects into Fedora 

## Troubleshooting/issues/feedback

Use cases are welcome. The goal of this module is to leverage as much of Feeds' built-in functionality as possible while providing the ability to load a wide range of Islandora content types as possible. If you have any questions or comments, please post them to:

* [Islandora Group](https://groups.google.com/forum/?hl=en&fromgroups#!forum/islandora)
* [Islandora Dev Group](https://groups.google.com/forum/?hl=en&fromgroups#!forum/islandora-dev)

