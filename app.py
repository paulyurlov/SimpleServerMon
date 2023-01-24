import json
from flask import Flask, render_template

app = Flask(__name__)


def get_data():
    tmp = {}
    with open('/data/data.json') as f:
        d = json.load(f)
        tmp = d
    return tmp


@app.route('/')
def index():
    return render_template('index.html', data=get_data())


if __name__ == '__main__':
    app.run(port=69)
