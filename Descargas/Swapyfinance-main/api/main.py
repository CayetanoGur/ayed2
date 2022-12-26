


class Trader:
    '''The trader class represents the user, it conteins their ID, the portfolio where the events contracts are store and their founds
        Founds will be the money that the user puts on their account
        In the portfolio we store each event that the user bought for example 
        [{"EVENT": event_ID, "AMOUNT": amount_of_contracts, "PRICE": buy_price, "SIDE": side(yes or no)}]
    '''
    def __init__(self,id):
        self.id = id
        self.portfolio = []
        self.funds = 0
        
    def __repr__(self):
        rep = 'ID: ' + str(self.id) + ' Portfolio: ' + str(self.portfolio) + ' Founds: ' + str(self.funds)
        return rep
    
    def add_founds(self, amount):
        self.funds += amount
        return self.funds
    
    def remove_founds(self, amount):
        self.funds -= amount
        return self.funds
    
    def add_contract(self, event, amount, buy_price, side):
        '''This function adds a contract to the user portfolio when they buy one'''
        
        new_contract = {"EVENT": event, "AMOUNT": amount, "PRICE": buy_price, "SIDE": side}
        self.portfolio.append(new_contract)
        return self.portfolio
    
    def remove_contract(self, event, amount, side):
        '''This function removes a given contract (pass by parameters) from a user contract, the function iterates the list of contracts and if the contract is found it removes  '''
        #Iterates untill the contract is found
        for i in self.portfolio:
            if i["EVENT"] == event:
                if i["SIDE"] == side:
                    if i["AMOUNT"] > amount:
                        i["AMOUNT"] -= amount
                    elif i["AMOUNT"] == amount:
                        self.portfolio.remove(i)
                    elif i["AMOUNT"] < amount:
                        #TODO: catch the error
                        #Not enough amount of contracts, the user is trying to sell more contracts than the amount they own
                        print("Insuficient amount of contracts")
            else:
                #The contract wasn't found on their portfolio
                print("Contract no found")

class Bid:
    '''The bid class represents the offers that a user is trying to buy a contract, it could be YES or NO.
    This are the users that are wanting to buy a certein contract, they dont own one yet.'''
    def __init__(self, price, quantity, type, order_id, trader:Trader):
        self.id = order_id
        self.trader = trader
        self.price = price
        self.quantity = quantity
        self.type = type

    def __lt__(self, other):
        return self.price < other.price

    def __repr__(self):
        rep = 'Bid(' + str(self.price) + ',' + str(self.quantity) + ',' + self.type + ')'
        return rep 
    
class Ask:
    '''The ask class represents the offers that a user is trying to sell a contract, it could be YES or NO.
    This are users that are wanting to sell a certein contract, they already own it.'''
    def __init__(self, price, quantity, type, order_id, trader:Trader):
        self.id = order_id
        self.trader = trader
        self.price = price  
        self.quantity = quantity
        self.type = type

    def __lt__(self, other):
        return self.price < other.price

    def __repr__(self):
        rep = 'Ask(' + str(self.price) + ',' + str(self.quantity) + ',' + self.type + ')'
        return rep 


class OrderBook:
    '''The OrderBook is where all orders are store, now they are on lists but we need to trasnfer it to a db. We have bids and ask for each side(YES and NO)
    also we have a market price for each side (YES and NO) which they repsents the market price (that is the latest match between the buyer and the seller).
    Order ID --> each order has its own id
    Trader ID --> to identify how is creating the order (User id)
    Event --> to identify which event are the users trading, each event will have its own order book, and we will have many events.
    '''
    def __init__(self):
        self.bidsYes = []
        self.asksYes = []
        self.bidsNo = []
        self.asksNo = []
        self.marketPriceYes = 99
        self.marketPriceNo = 99
        self.order_id = 0
        self.trader_id = 0
        self.event = ""

    def __repr__(self):
        rep = 'Bids Yes: ' + str(self.bidsYes) + '\nAsks Yes: ' + str(self.asksYes) +'\nBids No: ' + str(self.bidsNo) +  '\nAsk No: ' + str(self.asksNo) + ''
        return rep
    
    def new_order_id(self):
        self.order_id += 1
        return self.order_id
    
    #I implemented the trader ID inside the order boook just to work inside as a counter, but we need to store it on the db, the traderID helps to find a certein user in order to see tehir portfolio and their founds

    def new_trader(self):
        self.trader_id += 1
        return self.trader_id


    def new_Bid(self,price, quantity, type, trader:Trader):
        '''Function that generates a new bid by a certein trader, it has a price and a quantity given by the users, it also has a type which is the side that the user is willing to buy (YES or NO)
        and a Trader to identify the user.
        '''
        newBid = Bid(price,quantity,type, self.new_order_id(), trader.id)
        if(int(price) >= 100 or int(price) <= 0 ):
            print("Error: Invalid price, enter a price between 0 and 100\n")
            #TODO:
            #Catch the error
            #The price given by the user must be between 0 and 100 (this represents dollar cents)
        else:
            #Also the trader must have enough founds to create the order (the funds needed must be price x quantity + fees)
            if(trader.funds > ((price * quantity) + price * quantity * 0.05 )):    
                if(newBid.type == "Yes"):
                    self.bidsYes.append(newBid)
                elif(newBid.type == "No"):
                    self.bidsNo.append(newBid)
            else:
                print("No Founds")
        return newBid


    def new_Ask(self, price, quantity, type, trader:Trader):
        '''This function generetes a new ask by a trader that is willing to sell a contract of an event, we hace a price and a quantity that the user wants to sell and also a side (YES or NO)
        We also need to check if that trader/user has that event on their portfolio.
        '''
        #To see if the user has the contrat we need t search it on the database
        newAsk = Ask(price,quantity,type, self.new_order_id(), trader.id)
        if(int(price) >= 100 or int(price) <= 0 ):
            print("Error: Invalid price, enter a price between 0 and 100\n")
            #TODO:
            #Catch the error
        else:
            #TODO:
            #We dont need to see if the user has enough funds because the user already owns the contract
            if(newAsk.type == "Yes"):
                self.asksYes.append(newAsk)
            elif(newAsk.type == "No"):
                self.asksNo.append(newAsk)
        return newAsk


    def sort(self):
        '''This function sorts each list in the way we need it, because we need to have the list of asks order from low to high and the list of bids from high to low
        in order to have always the market price in the position 0'''
        self.asksNo.sort()
        self.asksYes.sort()
        self.bidsNo.sort(reverse=True)
        self.bidsYes.sort(reverse=True)
        return self


    def match_yes(self):
        '''This function is in charge of matching all the orders that the users creats (Bids and Asks) on the YES side, match function works as a price time priority, we match the lower ask with a bid at the same price, if not
        found it continues with the next lower ask and so on (Until it finds the lowest).
        When ever a match is done we need to transfer the money from the bid user to the ask user (i have done functions that add and removes funds)
        Also it needs to transfer the contract from the ask user to thee bid user (i have done functions that add and removes contracts)'''
        i = 0
        j = 0
        #The i variable iterates on the bidsYes list
        #The j variable iterates on the asksYes list

        while i<len(self.bidsYes):
            j = 0
            while j<len(self.asksYes):
                if(i < 0 or j < 0):
                    break
                else:
                    if(self.bidsYes[i].price == self.asksYes[j].price):
                        bquant = int(self.bidsYes[i].quantity) - 1
                        self.bidsYes[i].quantity = bquant
                        aquant =  int(self.asksYes[j].quantity) - 1
                        self.asksYes[j].quantity = aquant
                        #TODO:
                        #Here we need to add the contract to the bid user and removes it from the ask user
                        #Also add funds of the self.bidsYes[i].price to the ask trader/user and remove that same price from the bid trader/user funds                      

                        #Here we set the market price which is the latest match of the YES SIDE
                        self.marketPriceYes = self.bidsYes[i]

                        if(self.bidsYes[i].quantity == 0):
                            self.bidsYes.pop(i)
                            i -= 1
                        if(self.asksYes[j].quantity == 0):
                            self.asksYes.pop(j)
                        
                    else:    
                        j = j + 1
            i = i + 1
                    
        return self


    def match_no(self):
        '''This function is in charge of matching all the orders that the users creats (Bids and Asks) on the NO side, match function works as a price time priority, we match the lower ask with a bid at the same price, if not
        found it continues with the next lower ask and so on (Until it finds the lowest).
        When ever a match is done we need to transfer the money from the bid user to the ask user (i have done functions that add and removes funds)
        Also it needs to transfer the contract from the ask user to thee bid user (i have done functions that add and removes contracts)'''
        i = 0
        j = 0
        #The i variable iterates on the bidsNo list
        #The j variable iterates on the asksNO list
        while i < len(self.bidsNo):
            j = 0
            while j < len(self.asksNo):
                if(i < 0 or j < 0):
                    break
                else:
                    if(self.bidsNo[i].price == self.asksNo[j].price):
                        bquant = int(self.bidsNo[i].quantity) - 1
                        self.bidsNo[i].quantity = bquant
                        aquant = int(self.asksNo[j].quantity) - 1
                        self.asksNo[j].quantity = aquant

                        #TODO:
                        #Here we need to add the contract to the bid user and removes it from the ask user
                        #Also add funds of the self.bidsYes[i].price to the ask trader/user and remove that same price from the bid trader/user funds

                        #Here we set the market price of the NO SIDE
                        self.marketPriceNo = self.bidsNo[i].price

                        if(self.bidsNo[i].quantity == 0):
                            self.bidsNo.pop(i)
                            i -= 1
                        if(self.asksNo[j].quantity == 0):
                            self.asksNo.pop(j)
                            j += 1
                    else:
                        j += 1
            i += 1


   
#------------------------------------------------------------------
#ALL THIS IS TO TEST THE CODE YOU CAN ERASE IT
# ob = OrderBook()

# caye = Trader(ob.new_trader())
# tobi = Trader(ob.new_trader())
# salvi = Trader(ob.new_trader())

# caye.add_founds(3000)
# salvi.add_founds(1500)
# tobi.add_founds(5999)
# caye.add_contract("arg", 2, 1000, "Yes")
# print(repr(caye), repr(tobi), repr(salvi))

# ob.new_Bid(35,5,"Yes", caye)
# ob.new_Bid(80,6,"Yes", tobi)
# ob.new_Bid(35,5,"Yes", salvi)

# ob.new_Ask(35,4,"Yes", salvi)
# print("Raw OB: \n")
# print(repr(ob))
# print("Sort OB: \n")
# ob.sort()
# print(repr(ob))
# print("Match OB: \n")
# ob.match_yes()
# ob.match_no()

# print(repr(ob))

# print(repr(caye), repr(tobi), repr(salvi))







    

