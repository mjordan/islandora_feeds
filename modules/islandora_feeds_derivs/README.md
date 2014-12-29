# Islandora Feeds MODS

## Requirements

[Islandora Feeds](https://github.com/mjordan/islandora_feeds)

## Installation

Install as usual, see [this](https://drupal.org/documentation/install/modules-themes/modules-7) for further information.

## Overview

This module provides a sample implementation for generating a MODS (or other XML) datastream from an OBJ datastream created by the Islandora Feeds module. With some development effort, the Islandora Feeds module will allow the direct generation of MODS and other complex XML datastreams. Until then, enjoy this workaround.

Given a OBJ datastream like this:

```xml
<fielddata>
  <title label="Title">Object's witty title</title>
  <field_1 label="Field 1">Object's field 1 value</field_1>
  <field_2 label="Field 2">Object's field 2 value</field_2>
</fielddata>
```

this module creates a MODS datastream like this and adds it to the object:

```xml
<!-- MODS markup that precedes titleInfo goes here -->
<titleInfo>
  <title>Object's witty title</title>
  <subTitle/>
</titleInfo>
<!-- MODS markup that follows titleInfo goes here -->
```

Only the `<titleInfo>` fragment is provided in this example because that's the only element in the MODS datastream this module populates.

## Configuration

Once enabled, this module creates a MODS datastream for every object created from Feeds data. You can create other XML datastreams if you can provide an XSL stylesheet that will convert the flat OBJ XML into your target format. All you need to do is drop the stylesheet file into the module's 'xml' directory and it will be detected.

The module can not only generate deriviate XML datastreams from the OBJ, it can:

* share objects that are imported by Islandora Feeds with specific collections
* change the objects' content model on the fly

The admin settings, which are at admin/islandora/tools/feeds/derivs (and which can be accessed from within the admin settings of the Islandora Feeds, if the module is enabled) look like this:

!(Islandora Feeds Derivs)[https://dl.dropboxusercontent.com/u/1015702/linked_to/islandora_feeds_derivs_admin.png]

To see the module in action, enable it, generate some Islandora objects using Islandora Feeds, look at thoese objects' MODS datastreams, and modify the module to suit your own needs.

## Usage

Since Islandora Feeds Derivs can create any XML datastream from the flat XML created by Islandora Feeds, you can use it to create MODS datastreams. The XSL stylesheet provided with the module is a good place to start; it only copies the OBJ's 'title' element into the MODS template, but you can modify it, or copy it and create another stylesheet, to suite your specific needs.

A typical workflow for using Islandora Feeds to import data that will end up in MODS datastreams would be:

1. Create a Drupal content type that has a text field for each element in the MODS records you want to populate.
2. Test the content type by importing some test data from a CSV by running the resulting OBJ datastreams against a stylesheet based on the one provided with the Islandora Feeds Derivs module.
3. When you are satisfied with your tests, configure Islandora Feeds Derivs to use your stylesheet to create MODS datastreams, to delete the OBJ datastream, and to set the preferred target collection and content models for your objects.

## Troubleshooting/issues/feedback

Use cases are welcome. If you have any questions or comments, please post them to:

* [Islandora Group](https://groups.google.com/forum/?hl=en&fromgroups#!forum/islandora)
* [Islandora Dev Group](https://groups.google.com/forum/?hl=en&fromgroups#!forum/islandora-dev)

