FROM python:3.9

# 
COPY requirements.txt requirements.txt

# 
RUN pip install --no-cache-dir --upgrade -r requirements.txt

# 
COPY . .

# 
CMD ["uvicorn", "api_main:app", "--host", "0.0.0.0", "--port", "89"]