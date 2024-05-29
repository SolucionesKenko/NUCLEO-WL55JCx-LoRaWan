import requests
import json
from datetime import timedelta, datetime

API_KEY = "XXXXXX"
PROJECT_ID = "XXXXX"
base_url = 'https://api.golioth.io/v1/projects/' + PROJECT_ID


def getStream(start, end, fields):
    encodedQuery = json.dumps({
        "fields": fields
    })
    startParam = start.isoformat()+'Z'
    endParam = end.isoformat()+'Z'
    print(startParam)
    return false
    url = base_url + '/stream?encodedQuery=' + \
        encodedQuery + "&start="+startParam+"&end="+endParam
    print(url)
    headers = {'X-API-Key': API_KEY}
    response = requests.get(url, headers=headers)
    return response.json()


def getStreamWithPost(start, end, fields):
    url = base_url + '/stream'
    headers = {'X-API-Key': API_KEY}
    body = json.dumps({
        'start': start.isoformat()+'Z',
        'end': end.isoformat()+'Z',
        'query': {
            "fields": fields
        }
    })
    print(body)
    response = requests.post(url, body, headers=headers)
    return response.json()


end = datetime.now()
start = end - timedelta(days=7)
'''
# Use GET request on stream endpoint
data = getStream(start, end, [{
    "path": "time"
}, {
    "path": "deviceId"
}, {
    "path": "*"
}])
'''
# Use POST request on stream endpoint
data = getStreamWithPost(start, end, [{
    "path": "time"
}, {
    "path": "deviceId"
}, {
    "path": "*"
}])
print(data)
print("Found: " + str(data['total']) + " records")
for d in data['list']:
    print(d)