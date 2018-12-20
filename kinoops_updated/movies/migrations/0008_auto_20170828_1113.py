# -*- coding: utf-8 -*-
# Generated by Django 1.11.4 on 2017-08-28 05:13
from __future__ import unicode_literals

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('movies', '0007_auto_20170827_1214'),
    ]

    operations = [
        migrations.AlterModelOptions(
            name='movie',
            options={'ordering': ('upload_date',)},
        ),
        migrations.AlterField(
            model_name='movie',
            name='actors',
            field=models.ManyToManyField(blank=True, to='movies.Actor'),
        ),
        migrations.AlterField(
            model_name='movie',
            name='categories',
            field=models.ManyToManyField(blank=True, to='movies.Category'),
        ),
        migrations.AlterField(
            model_name='movie',
            name='countries',
            field=models.ManyToManyField(blank=True, to='movies.Country'),
        ),
        migrations.AlterField(
            model_name='movie',
            name='directors',
            field=models.ManyToManyField(blank=True, to='movies.Director'),
        ),
        migrations.AlterField(
            model_name='movie',
            name='genres',
            field=models.ManyToManyField(blank=True, to='movies.Genre'),
        ),
        migrations.AlterField(
            model_name='movie',
            name='image',
            field=models.ImageField(blank=True, default='images/car1.jpg', upload_to=''),
        ),
        migrations.AlterField(
            model_name='movie',
            name='links',
            field=models.ManyToManyField(blank=True, to='movies.Link'),
        ),
        migrations.AlterField(
            model_name='movie',
            name='movie_date',
            field=models.DateField(blank=True),
        ),
        migrations.AlterField(
            model_name='movie',
            name='overview',
            field=models.TextField(blank=True, max_length=1000),
        ),
    ]
