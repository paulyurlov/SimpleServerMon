import json
from flask import Flask, redirect, render_template


app = Flask(__name__)


def get_data():
    tmp = {}
    with open('/data/cpu_mem.json') as f:
        d = json.load(f)
        tmp['cpu_load'] = float(d['CPU'].split('%')[0])
        used, total = d['MEM'].split(' ')
        if "Gi" in used:
            used = float(used.removesuffix('Gi'))
        elif "Mi" in used:
            used = float(used.removesuffix('Mi')) / 1024
        total = float(total.removesuffix('Gi'))
        tmp['mem_load'] = round(used / total * 100, 2)
    with open('data/info.json') as f:
        d = json.load(f)
        tmp['cpu_temp'] = d["coretemp-isa-0000"]["Package id 0"]["temp1_input"]
        tmp['gpu_temp'] = d["nouveau-pci-0100"]["temp1"]['temp1_input']
    print(tmp)
    return tmp


@app.route('/')
def index():
    return render_template('index.html', data=get_data())


if __name__ == '__main__':
    app.run(port=80)
