from django.db import models
import uuid
from django.contrib.auth.models import User
from django.db.models.signals import pre_save
from Swapyfinance.utils import unique_slug_generator

Market_Types = [
	('SK', 'Simple Market'),
	('CK', 'Complex Market')
]

# Main markets table that will store markets information
class OrderBook(models.Model):
	name = models.CharField(max_length=250, verbose_name='Name')
	event_date = models.DateField(verbose_name='Event Date')
	market_type = models.CharField(max_length=5, choices=Market_Types, verbose_name='Market Type')
	number_of_bids = models.PositiveIntegerField(default=0, verbose_name='Number of Bids')
	created_by = models.ForeignKey(User, on_delete=models.CASCADE, related_name='created_by', verbose_name='Created By')
	created_on = models.DateTimeField(auto_now_add=True, auto_now=False, verbose_name = 'Creation Date')
	slug = models.SlugField(max_length=300, blank=True, null=True, verbose_name='Slug')

	def __str__(self):
		return f'OrderBook No: {self.id}, Name: {self.name}'

	# This function is used to get all options of a market from child model 'OrderBookOptions' based on the currently selected market
	def get_book_options(self):
		return OrderBookOption.objects.filter(orderbook=self)

	class Meta:
		verbose_name_plural = "Order Books"

class OrderBookOption(models.Model):
	orderbook = models.ForeignKey(OrderBook, on_delete=models.CASCADE, verbose_name='Order Book')
	name = models.CharField(max_length=250, verbose_name='Name')
	yes_bid_price = models.PositiveIntegerField(blank=True, null=True, verbose_name='Price for Yes')
	no_bid_price = models.PositiveIntegerField(blank=True, null=True, verbose_name='Price for No')

	def __str__(self):
		return f'OrderBook: {self.orderbook}, Option: {self.name}'

	class Meta:
		verbose_name_plural = 'Order Books Options'

# generates slug value according to the instance name on save, update
def slug_generator(sender, instance, *args, **kwargs):
    if not instance.slug:
        instance.slug = unique_slug_generator(instance)

pre_save.connect(slug_generator, sender=OrderBook)