from django.shortcuts import render
from django.views.generic import View
from markets.models import OrderBook

class HomeView(View):
	template_name = 'home_page.html'

	def get(self, request):
		orderbook_obj = OrderBook.objects.all()
		context = {
			'title'	:	'Home',
			'markets'	:	orderbook_obj,
		}
		return render(request, self.template_name, context)