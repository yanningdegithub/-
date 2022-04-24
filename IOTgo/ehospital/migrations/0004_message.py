# -*- coding: utf-8 -*-
# Generated by Django 1.11 on 2018-07-17 10:58
from __future__ import unicode_literals

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('ehospital', '0003_room'),
    ]

    operations = [
        migrations.CreateModel(
            name='message',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('username', models.CharField(max_length=30, verbose_name='留言人名称')),
                ('roomnum', models.CharField(max_length=10, verbose_name='留言人房间号')),
                ('text', models.CharField(max_length=100, verbose_name='留言信息')),
            ],
            options={
                'verbose_name': '留言',
                'verbose_name_plural': '留言',
            },
        ),
    ]
