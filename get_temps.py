import psutil
import GPUtil
import json


dct = {}
dct['cpu_temp'] = psutil.sensors_temperatures()['coretemp'][0].current
gpus = GPUtil.getGPUs()
dct['gpu_temp'] = gpus[0].temperature
dct['cpu_load'] = psutil.cpu_percent()
dct['mem_load'] = psutil.virtual_memory().percent

with open('mon_script/data.json', 'w') as fp:
    json.dump(dct, fp)
