import json
from flask import Flask, render_template

app = Flask(__name__)


def get_data():
    tmp = {}
    with open('data.json') as f:
        d = json.load(f)
        # {"CPU": "1.6%", "MEM": "541Mi 7.7Gi", "CPU_TEMP": 37, "GPU_TEMP":         GPU Current Temp            : 44 C}
        tmp['cpu_temp'] = float(d["CPU_TEMP"])
        tmp['gpu_temp'] = float(
            ''.join(list(filter(str.isdigit, d["GPU_TEMP"]))))
        used, total = d["MEM"].split()
        if "Mi" in used:
            used = float(used.removesuffix('Mi')) / 1024
        elif "Gi" in used:
            used = float(used.removesuffix('Gi'))
        tmp['mem_load'] = used / float(total.removesuffix('Gi')) * 100
        tmp['cpu_load'] = float(d["CPU"].removesuffix('%'))
    return tmp


@app.route('/')
def index():
    return render_template('index.html', data=get_data())


if __name__ == '__main__':
    app.run(port=69)
