# Brand

[![stability-stable](https://img.shields.io/badge/stability-deprecated-red.svg?style=for-the-badge)](https://github.com/orangemug/stability-badges)
[![License](https://img.shields.io/badge/License-BSD%203--Clause-blue.svg?style=for-the-badge)](https://raw.githubusercontent.com/fubarhouse/brand/master/LICENSE.txt)

An enhanced version of [ThemeKey](https://www.drupal.org/project/themekey) which is focused towards being a **developer-centric experience**.

## Deprecated

This project has been moved into the official Drupal system and will not be receiving any updates.

Bugs #13 and #32 have been fixes in the the development version between version 7.x-1.1 and 7.x-1.2.

You can find the latest version on the [project page](https://www.drupal.org/project/brand) on Drupal.org.

You can also install this module using composer:
````sh
composer require drupal/brand:dev-1.x
````

In addition to the official deprecation of this repository, we will be updating this repository to match version 7.x-1.2 upon its release before archiving this repository. This will mean that this repository will be marked as archive and will exist as read-only.

## Introduction

The Brand module is a powerful theme management system which is designed to handle 'snowflakes' in organisations using Drupal 7.

It is very similar to [ThemeKey](https://www.drupal.org/project/themekey) however bundles features tailored towards enterprise use such as greater visibility for accountability and segmented permissions for control on platforms distributing a single codebase among multiple clients.

## Requirements

None.

## Installation

Installation is [standard](https://drupal.org/documentation/install/modules-themes/modules-7) for Drupal 7 modules.

## Configuration

* After installation, allocate permissions as required.
* Determine if theme controls need to be disabled. **If you do not do this**, themes will not be available to you when creating Brands.
* If applicable, add the themes to the available theme list or disable the theme control on the settings form.
* Under the menu for User Interface, find the link to the Brand module.
* If there are no brands, you can add a new brand using the link above the table, or at the top of the page.
* Follow the prompts, filling out the fields as required.

Brand includes Drush integration, so you can readily add or remove themes from the configured themes list, and you can also enforce or lift the control which enforces the exclusive selection of configured themes.

```sh
drush help brand
```

## Troubleshooting

* Issues and PR's are more than welcome, but please do so if you can produce replicable results.

## Maintainers

* Karl Hepworth ([@fubarhouse](https://twitter.com/fubarhouse))