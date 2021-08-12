import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    
    stocks = db.execute("SELECT symbol, name, price, SUM(shares) as total_shares FROM transactions WHERE user_id = ? GROUP BY symbol", session["user_id"])
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
    
    total = cash
    
    for stock in stocks:
        total = total + stock["total_shares"] * stock["price"]
    
    return render_template("index.html", stocks = stocks, cash = usd(cash), total = total)
    


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        quote = lookup(request.form.get("symbol"))
        
        if quote is None:
            return apology("must provide valid symbol")
        
        shares = request.form.get("shares"))
        if not shares.isdigit():
            return apology("You cannot purchase partial shares.")
        
        try:
            shares = int(request.form.get("shares"))
        except ValueError:
            return apology("shares must be a positive integer", 400)
            
        cost = int(request.form.get("shares")) * quote['price']
        
        user_money = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        
        if cost > user_money[0]['cash']:
            return apology("you do not have enough cash for this transaction")
        else:
            db.execute("UPDATE users SET cash = cash - ? WHERE id = ?", cost, session["user_id"]);
            # add transaction to transaction database
            add_transaction = db.execute("INSERT INTO transactions (user_id, shares, price, type, symbol, name) VALUES (?, ?, ?, ?, ?, ?)", session["user_id"], int(request.form.get("shares")), quote['price'], "buy", quote["symbol"], quote['name'])
        
            flash("Transaction successful!")
            return redirect("/")
            
    else:
        return render_template("buy.html")

@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    stocks = db.execute("SELECT * FROM transactions WHERE user_id = ?", session["user_id"])
    return render_template("history.html", stocks = stocks)

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    
    if request.method == "POST":
        quote = lookup(request.form.get("symbol"))
        
        if quote is None:
            return apology("must provide valid symbol")
        else:
            return render_template("quoted.html", name=quote["name"], symbol=quote["symbol"], price=quote["price"])
        
    else:
        return render_template("quote.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        
        if not request.form.get("username"):
            return apology("must provide username")
        if not request.form.get("password"):
            return apology("must provide password")
        if not request.form.get("confirmation"):
            return apology("must confirm password")
        if not request.form.get("password") == request.form.get("confirmation"):
            return apology("password and password confirmation must match")

        # hash password
        hash_p = generate_password_hash(request.form.get("password"))
        
        try:
            result = db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash_p)
            return redirect("/")
        except:
            return apology("username is already registered")
        
        # remember the user
        session["user_id"] = result
        
    elif request.method == "GET":
        return render_template("register.html")



@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        if (not request.form.get("symbol")) or (not request.form.get("shares")):
            return apology("must provide stock symbol and number of shares")
        
        if int(request.form.get("shares")) <= 0:
            return apology("must provide valid number of shares")
        
        quote = lookup(request.form.get("symbol"))
        
        if quote is None:
            return apology("Stock symbol not valid")
        
        shares_owned = db.execute("SELECT shares FROM transactions WHERE user_id = ? AND symbol = ? GROUP BY symbol", session["user_id"], quote['symbol'])[0]["shares"]
        
        if int(request.form.get("shares")) > int(shares_owned):
            return apology("You don't have enough shares")
            
        cost = int(request.form.get("shares")) * quote['price']
        
        current_cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
        
        db.execute("UPDATE users SET cash = ? WHERE id = ?", current_cash + cost, session["user_id"])
        
        db.execute("INSERT INTO transactions (user_id, type, symbol, shares, price, name) VALUES (?, ?, ?, ?, ?, ?)", session["user_id"], "sell", quote['symbol'], -int(request.form.get("shares")), cost, quote['name'])
        
        flash("Sold!")
        return redirect('/')
        
    else:
        symbols = db.execute("SELECT symbol FROM transactions WHERE user_id = ? GROUP BY symbol", session["user_id"])
        return render_template("sell.html", symbols = symbols)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
