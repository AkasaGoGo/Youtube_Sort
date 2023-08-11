from googleapiclient.discovery import build
from google_auth_oauthlib.flow import InstalledAppFlow
import googleapiclient.errors

import pandas as pd
import os

# YOUTUBE_DATA_APIを使用するためのパラメータ
API_KEY = "AIzaSyDgaMBZf-ZbtdOhthFzXynpMRxUNxn-PkE" 
YOUTUBE_API_SERVICE_NAME = "youtube"
YOUTUBE_API_VERSION = "v3"

# YouTube Data APIを構築
youtube = build(YOUTUBE_API_SERVICE_NAME, YOUTUBE_API_VERSION, developerKey=API_KEY)

# csvファイルの読み込み
def channel_name():
    channel_reports = pd.read_csv('channel_reports_2.csv')

    channel_name = []
    for name in channel_reports['チャンネル名']:
        channel_name.append(name)
    return channel_name

print(channel_name())