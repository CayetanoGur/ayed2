from django.shortcuts import render, redirect
from django.contrib.auth.views import LoginView, PasswordResetView
from django.urls import reverse_lazy
from django.views.generic import View
from .forms import SignUpForm
from django.contrib.auth.models import User
from django.contrib import messages
from django.contrib.sites.shortcuts import get_current_site
from django.utils.encoding import force_bytes
from django.utils.http import urlsafe_base64_encode
from django.template.loader import render_to_string
from .tokens import account_activation_token
from django.template.loader import get_template
from django.core.mail import EmailMessage
from django.conf import settings
from django.utils.encoding import force_text
from django.utils.http import urlsafe_base64_decode
from django.contrib.messages.views import SuccessMessageMixin

# Class handling login functionality
class LoginView(LoginView):
    template_name = 'login.html'
    redirect_field_name = 'core:home'

# Class handling user registartion process
class SignUpView(View):
    form_class = SignUpForm
    template_name = 'signup.html'

    def get(self, request, *args, **kwargs):
        form = self.form_class()
        context = {
            'form': form
        }
        return render(request, self.template_name, context)

    def post(self, request, *args, **kwargs):
        form = self.form_class(request.POST)
        if form.is_valid():

            user = form.save(commit=False)
            user.is_active = False # Deactivate account till it is confirmed
            user.save()

            current_site = get_current_site(request)

            email_context = {
                'user': user,
                'domain': current_site.domain,
                'uid': urlsafe_base64_encode(force_bytes(user.pk)),
                'token': account_activation_token.make_token(user),
            }

            try:
                email_template = get_template('email_templates/account_activation_email.html').render(email_context)
                email_msg = EmailMessage(
                    'Activate Your Swapy Account', # Subject
                    email_template,
                    settings.APPLICATION_EMAIL,
                    [user.email],
                    reply_to = [settings.APPLICATION_EMAIL]
                )
                email_msg.content_subtype = 'html'
                email_msg.send(fail_silently=False)

            except Exception as exc:
                user.delete()
                print('Exception error at 636: ',exc)
                print('SMTP Server Error. Please make sure smtp server credentials are correct')
                messages.error(request, 'Opps sorry it looks like we are facing an issue. Please contact the customer support.')
                return redirect('users:login')

            return redirect('users:registration-completed')

        context = {
            'form': form
        }
        return render(request, self.template_name, context)

# Class to handle users account activation
class ActivateAccount(View):
    
    def get(self, request, uidb64, token, *args, **kwargs):
        try:
            uid = force_text(urlsafe_base64_decode(uidb64))
            user = User.objects.get(pk=uid)
        except (TypeError, ValueError, OverflowError, User.DoesNotExist):
            user = None

        if user is not None and account_activation_token.check_token(user, token):
            user.is_active = True
            user.profile.email_confirmed = True
            user.save()
            # login(request, user)
            messages.success(request, ('Your account have been confirmed. You can login now'))
            return redirect('users:login')
        else:
            messages.warning(request, ('The confirmation link was invalid, possibly because it has already been used.'))
            return redirect('users:login')

def RegistrationCompletedView(request):
    return render(request, 'signup_success.html')

class ResetPasswordView(PasswordResetView):
    template_name = 'reset_password/password_reset.html'
    email_template_name = 'reset_password/password_reset_email.html'
    subject_template_name = 'reset_password/password_reset_subject.txt'
    success_url = reverse_lazy('users:password_reset_done')
