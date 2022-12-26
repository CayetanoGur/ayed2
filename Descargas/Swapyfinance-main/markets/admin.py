from django.contrib import admin
from .models import OrderBook, OrderBookOption

# Creating validation for models appearance on admin panel
class OrderBookAdminPanelView(admin.ModelAdmin):
	# This will display the noted model fields in admin panel table
	list_display = ('id', 'name', 'market_type', 'event_date', 'number_of_bids', 'created_by', 'created_on')
	# This will display filter seaction on side with option as registered below
	list_filter = ('market_type', 'created_by', 'created_on')
	search_fields = ['name']

# Creating validation for models appearance on admin panel
class OrderBookOptionsAdminPanelView(admin.ModelAdmin):
	# This will display the noted model fields in admin panel table
	list_display = ('id', 'orderbook', 'name', 'yes_bid_price', 'no_bid_price')

# Registering our models for django's admin panel
# If we don't regsiter a model, it'll not appear in django admin panel
admin.site.register(OrderBook, OrderBookAdminPanelView)
admin.site.register(OrderBookOption, OrderBookOptionsAdminPanelView)