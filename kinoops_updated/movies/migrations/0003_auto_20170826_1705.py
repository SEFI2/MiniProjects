# -*- coding: utf-8 -*-
# Generated by Django 1.11.4 on 2017-08-26 11:05
from __future__ import unicode_literals

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('movies', '0002_auto_20170826_1654'),
    ]

    operations = [
        migrations.AlterField(
            model_name='movie',
            name='image',
            field=models.FileField(default='', upload_to='movies'),
        ),
    ]