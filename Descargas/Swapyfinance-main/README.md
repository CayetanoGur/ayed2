# Swapy Finance

# Instuctions on how to run the web application

1. Create a virtual environment anywhere on your PC with this command...
	python -m venv swapy_venv

2. Navigate to virtual environment directory, and run this commad to activate your venv...
	scripts/activate

3. Once your virtaul environment is ready clone your repo inside the environment directory

4. Install all of the required libraries in your venv with this command...
	pip install -r requirements.txt

5. Migrate your Dn with this command...
	python manage.py migrate

6. Create your super user account to get access to Django admin panel. Run this command and provide the info required...
	python manage.py createsuperuser

7. Now you're ready to use the applciation. Please run the server with this command and access the website...
	python manage.py runserver


# How to access Django admin panel
You can access the admin panel by adding /admin at the end of your main url, e.g localhost:8000/admin or 127.0.0.1:8000/admin
# Note: Only super user or staff user can login to django admin panel.

You can add new users to application through users model in admin panel (Check the images below)

1. Create new User
	Click the add button to create new user and provide all the details.
	![Add Users](https://github.com/CayetanoGur/Swapyfinance/blob/main/core/static/Github%20Assets/User%201.png)
	![Add Users Form](https://github.com/CayetanoGur/Swapyfinance/blob/main/core/static/Github%20Assets/User%202.ng.png)

2. Give superuser role to required users
	Open any users profile and check the superuser checkbox and save the updates.
	![Give admin access](https://github.com/CayetanoGur/Swapyfinance/blob/main/core/static/Github%20Assets/User%203.png)


# How to create new markets for your application...

1. Please open the order book data through "Order Books" option in markets table
	![Order Book Table](https://github.com/CayetanoGur/Swapyfinance/blob/main/core/static/Github%20Assets/Order%201.png)

2. Inside Order book table you can check existing markets and create new markets as well through "Add Order Book" option at top right corner
	![Order Book Table](https://github.com/CayetanoGur/Swapyfinance/blob/main/core/static/Github%20Assets/Order%202.png)

3. Provide all details inside the order book creation form. You can ignore the fields "Number of Bids, Slug" as they are optional and handled through backend scripts
	![Create new market](https://github.com/CayetanoGur/Swapyfinance/blob/main/core/static/Github%20Assets/Order%203.png)

4. After adding market you need create options of that market in the table "Order Book Options"
	![Create new option for market](https://github.com/CayetanoGur/Swapyfinance/blob/main/core/static/Github%20Assets/Order%204.png)

5. You can create new order book options through "add order book"
	![alt text](https://github.com/CayetanoGur/Swapyfinance/blob/main/core/static/Github%20Assets/Order%205.png)
	
6. In the form you need to select the market(Order Book) for the new option
7. Then add the name of the option, if its a complex market then provide complete name but if its a simple market then just add "Yes" and "No" for their respective option. Also you need to add bid price as either for Yes or for NO.

That's all