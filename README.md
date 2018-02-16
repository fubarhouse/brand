# Brand

[![stability-stable](https://img.shields.io/badge/stability-stable-green.svg?style=for-the-badge)](https://github.com/orangemug/stability-badges)
[![License](https://img.shields.io/badge/License-BSD%203--Clause-blue.svg?style=for-the-badge)](https://raw.githubusercontent.com/fubarhouse/brand/master/LICENSE)

A **developer-centric experience** in creating and managing Drupal 7 sub-sites through the use of theme management.

**This is essentially a much fancier version of [ThemeKey](https://www.drupal.org/project/themekey)**

## Introduction

This module serves as a practical, managed solution designed specifically to organisations needing to handle 'snowflakes' and 'unicorns' with a simple, powerful and scalable workflow.

When configuring multiple Brands for a single condition, such as a term or book, the system will find the Brand using the lowest weight which is active based upon the date restrictions. If there is more than one Brand for the same page without a specified weight the results are currently untested and unwarrantable. Please submit an issue if you have an idea of how this should be handled.

## Requirements

None.

## Installation

Installation is standard for Drupal 7 modules.

See https://drupal.org/documentation/install/modules-themes/modules-7 for more information.

## Configuration

* Under the administrative options for User Interface, find the link to the Brand module.
* If there are no brands, you can add a new brand using the link above the table, or at the top of the page.
* Follow the prompts, filling out the fields as required.
  Detailed information is available next to the form fields.
* After submitting the form, it's recommended to clear caches - especially if you're expecting anonymous traffic.

## Troubleshooting

* Issues and PR's are more than welcome, but please do so if you can produce replicable results.

## Maintainers

* Karl Hepworth ([@fubarhouse](https://twitter.com/fubarhouse))