import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError

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

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///reviews.db")


@app.route("/")
#@login_required
def index():
    return render_template("index.html")

@app.route("/italy")
#@login_required
def italy():
    return render_template("italy.html")

@app.route("/spain")
#@login_required
def spain():
    return render_template("spain.html")

@app.route("/sweden")
#@login_required
def sweden():
    return render_template("sweden.html")

@app.route("/denmark")
#@login_required
def denmark():
    return render_template("denmark.html")

@app.route("/netherlands")
#@login_required
def netherlands():
    return render_template("netherlands.html")

@app.route("/rewAll")
#@login_required
def rewAll():

    reviews = db.execute("SELECT * FROM rew")

    return render_template("rewAll.html", reviews=reviews)

@app.route("/rewSpain")
#@login_required
def rewSpain():

    reviews = db.execute("SELECT * FROM rew")

    return render_template("rewSpain.html", reviews=reviews)

@app.route("/rewItaly")
#@login_required
def rewItaly():

    reviews = db.execute("SELECT * FROM rew")

    return render_template("rewItaly.html", reviews=reviews)

@app.route("/rewSweden")
#@login_required
def rewSweden():

    reviews = db.execute("SELECT * FROM rew")

    return render_template("rewSweden.html", reviews=reviews)

@app.route("/rewDenmark")
#@login_required
def rewDenmark():

    reviews = db.execute("SELECT * FROM rew")

    return render_template("rewDenmark.html", reviews=reviews)

@app.route("/rewNetherlands")
#@login_required
def rewNetherlands():

    reviews = db.execute("SELECT * FROM rew")

    return render_template("rewNetherlands.html", reviews=reviews)

@app.route("/reviews")
#@login_required
def reviews():

    reviews = db.execute("SELECT * FROM rew")

    return render_template("rewAll.html", reviews=reviews)

@app.route("/addreview", methods=["GET", "POST"])
#@login_required
def addreview():
    if request.method == "POST":

        name = request.form.get("name")
        university = request.form.get("university")
        country = request.form.get("country")
        rating = request.form.get("rate")
        comment = request.form.get("comment")

        if not name:
            return render_template("error.html")
        if not university:
            return render_template("error.html")
        if not country:
            return render_template("error.html")
        if not rating:
            return render_template("error.html")
        if not comment:
            return render_template("error.html")

        db.execute("INSERT INTO rew (name, university, country, rating, comment) VALUES (?, ?, ?, ?, ?)", name, university, country, rating, comment)

        flash("Done!")
        return redirect("/reviews")

    else:
        return render_template("addreview.html")