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

# チャンネルIDからチャンネルの全動画のプレイリストIDを取得
# 引数に channel_id をとる。この時点で channel_id は未知（"湊アクア" のようなチャンネル名ではない）
def getChannelPlaylistId(channel_id):
    channel = youtube.channels().list(part='snippet,contentDetails', id=channel_id).execute()
    item = channel['items'][0]
    playlist_id = item['contentDetails']['relatedPlaylists']['uploads']
    return playlist_id

# プレイリストIDからプレイリストに含まれる動画のIDを取得
def getVideoIds(playlist_id, page_token):
    items_info = youtube.playlistItems().list(part='contentDetails', playlistId=playlist_id, maxResults=10, pageToken=page_token).execute()
    video_ids = list(map(lambda item: item['contentDetails']['videoId'], items_info['items']))
    if 'nextPageToken' in items_info:
        video_ids.extend(getVideoIds(playlist_id, items_info['nextPageToken']))
    return video_ids

# 動画IDから動画の情報を取得
def getVideos(video_ids):
    videos = []
    for index, video_id in enumerate(video_ids):
        video_info = youtube.videos().list(part='snippet,statistics', id=video_id).execute()
        videos.extend(video_info['items'])
    return videos

channel_id = 'UC9WJo5ZJVXMZiA5XV2jLx5Q'
playlist_id = getChannelPlaylistId(channel_id)
video_ids = getVideoIds(playlist_id, None)
videos = getVideos(video_ids)

for video in videos:
    print(video['snippet']['title'], ',', 'https://youtube.com/watch?v=' + video['id'])
    
