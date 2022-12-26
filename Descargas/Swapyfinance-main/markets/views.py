from django.shortcuts import render, redirect
from django.views.generic import View
from .models import OrderBook
from django.contrib import messages #import messages

class MarketDetailsView(View):
	template_name = 'market-details.html'

	def get(self, request, slug):
		# Fetching market from database
		try:
			market_obj = OrderBook.objects.get(slug=slug)

		except OrderBook.DoesNotExist:
			messages.info(request, "Sorry! The market you're looking for does not exist")
			return redirect('core:home')

		context = {
			'title'	:	'Place Order',
			'market'	:	market_obj,
		}
		return render(request, self.template_name, context)