from flask import Flask, jsonify
import requests

app = Flask(__name__)

@app.route("/health")
def health():
    return { "health": "ok" }

app.run(host="0.0.0.0", port=8080)
