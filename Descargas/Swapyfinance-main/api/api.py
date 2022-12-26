import main as ob
from fastapi import FastAPI





app = FastAPI()

'''
Tengo que buscar o entender como hacer para que las new ask o bids se me guarden todos en
un mismo ob.OrderBook, como hacer para que no lo pida como variable de entrada sino que sea 
global
'''


Ob = ob.OrderBook()


@app.get("/")
def home():
    print(repr(Ob))
    return Ob

@app.post("/NewAsk")
def api_new_ask(price, quantity, type):
    Ob.new_Ask(price, quantity, type)
    print(repr(Ob))
    return "new ask"

@app.post("/NewBid")
def api_new_bid(price, quantity, type):
    Ob.new_Bid(price,quantity,type)
    print(repr(Ob))
    return "new bid"

@app.get("/OrderBook")
def show_book():
    print(repr(Ob))
    return Ob


@app.post("/Sort")
def sort():
    Ob.sort()
    print(repr(Ob))
    return Ob

@app.post("/MatchYes")
def match_yes():
    Ob.match_yes()
    print(repr(Ob))
    return Ob

@app.post("/MatchNo")
def match_no():
    Ob.match_no()
    print(repr(Ob))
    return Ob