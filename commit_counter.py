#
# usage:
#   python commit_counter.py username [since]
#   - username: github username
#   - since: optional date value, 2019-08-05T00:00:00Z will be used if not present
#            date format ISO 8601: YYYY-MM-DDTHH:MM:SSZ
#
import requests
import sys
import json

base = 'https://api.github.com'
user = sys.argv[1]
since = '2019-08-05T00:00:00Z'
if len(sys.argv) > 2:
    since = sys.argv[2]


resp = requests.get(base + '/users/' +  user + '/repos')

if resp.status_code == 200:
    repos = json.loads(resp.content)
    for repo in repos:
        print(repo['full_name'])
        commits_resp = requests.get(base + '/repos/' + repo['full_name'] + '/commits?author=' + user + '&since=' + since)
        if commits_resp.status_code == 200:
            commits = json.loads(commits_resp.content)
            print(len(commits))
