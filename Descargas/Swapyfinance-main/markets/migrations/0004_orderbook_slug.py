# Generated by Django 4.1.3 on 2022-12-02 19:31

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('markets', '0003_alter_orderbook_id'),
    ]

    operations = [
        migrations.AddField(
            model_name='orderbook',
            name='slug',
            field=models.SlugField(blank=True, max_length=300, null=True, verbose_name='Slug'),
        ),
    ]
