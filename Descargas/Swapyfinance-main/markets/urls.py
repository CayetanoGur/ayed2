from . import views
from django.urls import path
app_name = 'markets'

urlpatterns = [
    path('market/<slug:slug>', views.MarketDetailsView.as_view(), name='market-details')
]
