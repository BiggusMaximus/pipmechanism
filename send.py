import requests
import random

# Replace this URL with the URL of your PHP server
url = 'https://pipmechanism-monitoring-pkmkc.baseengineering-indonesia.com/api.php'

# Data to send via POST request
data = {
    'tegangan': random.uniform(0.0, 100.0),  # Example data generation for tegangan
    'arus': random.uniform(0.0, 100.0),      # Example data generation for arus
}

try:
    response = requests.post(url, data=data)
    if response.status_code == 200:
        print(f'Success! Response Content:\n{response.text}')
    else:
        print(f'Error: {response.status_code}')
except requests.exceptions.RequestException as e:
    print(f'An error occurred: {e}')
