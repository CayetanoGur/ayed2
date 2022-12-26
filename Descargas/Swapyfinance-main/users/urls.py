from . import views
from django.urls import path, reverse_lazy
from django.contrib.auth import views as auth_views
from django.contrib.auth.forms import (
    PasswordResetForm,
    SetPasswordForm,
)

app_name = 'users'

urlpatterns = [
    # Authentication routes
    path('login', views.LoginView.as_view(), name='login'),
    path('logout/', auth_views.LogoutView.as_view(template_name='login.html'), name='logout'),
    path('registration', views.SignUpView.as_view(), name='registration'),
    path('registration-completed', views.RegistrationCompletedView, name='registration-completed'),
    path('activate/<uidb64>/<token>/', views.ActivateAccount.as_view(), name='activate'),
    # Password reset routes
    path('password-reset/', views.ResetPasswordView.as_view(), 
        name='password_reset'
    ),
    path('password-reset/done/', auth_views.PasswordResetDoneView.as_view(
        template_name='reset_password/password_reset_done.html'), 
        name='password_reset_done'
    ),
    path('password-reset-confirm/<uidb64>/<token>/', auth_views.PasswordResetConfirmView.as_view(
        template_name='reset_password/password_reset_confirm.html', 
        form_class=SetPasswordForm, 
        success_url=reverse_lazy('users:password_reset_complete')), 
        name='password_reset_confirm'
    ),
    path('password-reset-complete/', auth_views.PasswordResetCompleteView.as_view(
        template_name='reset_password/password_reset_complete.html'), 
        name='password_reset_complete'
    ),

]
