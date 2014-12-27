# Islandora Feeds MODS

## Requirements

[Islandora Feeds](https://github.com/mjordan/islandora_feeds)

## Installation

Install as usual, see [this](https://drupal.org/documentation/install/modules-themes/modules-7) for further information.

## Overview

This module provides a sample implementation of creating a MODS datastream from an OBJ datastream created by the Islandora Feeds module. With some development effort, the Islandora Feeds module will allow the direct generation of MODS and other complex XML datastreams. Until then, enjoy this workaround.

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

Only the `<titleInfo>` fragment is provided in this example because that's the only element in the MODS datastream this module populates. It's a sample module.

## Usage

Once enabled, this module creates a MODS datastream for every object created from Feeds data. To see it in action, enable it, generate some Islandora objects using Islandora Feeds, look at thoese objects' MODS datastreams, and modify the module to suit your own needs.

## Troubleshooting/issues/feedback

Use cases are welcome. If you have any questions or comments, please post them to:

* [Islandora Group](https://groups.google.com/forum/?hl=en&fromgroups#!forum/islandora)
* [Islandora Dev Group](https://groups.google.com/forum/?hl=en&fromgroups#!forum/islandora-dev)

