from googleapiclient.discovery import build
from google_auth_oauthlib.flow import InstalledAppFlow
import googleapiclient.errors

import json
import os
import pandas as pd
import sys

# YOUTUBE_DATA_APIを使用するためのパラメータ
# API_KEY = "YOUTUBE_DATA_API_KEY"
API_KEY = "YOUTUBE_DATA_API_KEY" #TODO ハードコーディングはよくないので環境変数として登録する
YOUTUBE_API_SERVICE_NAME = "youtube"
YOUTUBE_API_VERSION = "v3"

# YouTube Data APIを構築
youtube = build(YOUTUBE_API_SERVICE_NAME, YOUTUBE_API_VERSION, developerKey=API_KEY)

# csvファイルの読み込んで、チャンネル名を返す
def get_channel_name():
    channel_reports = pd.read_csv('channel_reports_2.csv')

    channel_name = []
    for name in channel_reports['チャンネル名']:
        channel_name.append(name)
    return channel_name

# チャンネル名からチャンネルIdを取得する
def get_channel_Id(search_query):
    youtube = googleapiclient.discovery.build(YOUTUBE_API_SERVICE_NAME, YOUTUBE_API_VERSION, developerKey=API_KEY)
    
    # 自分のチャンネル一覧を取得するリクエストを作成
    channels_request = youtube.search().list(
        part='id',
        type = "channel",
        q=search_query,
        maxResults=1
    ).execute()
    
    # 検索結果からチャンネルIDを取得
    if "items" in channels_request:
        channel_id = channels_request["items"][0]["id"]["channelId"]
        # print("チャンネルID:", channel_id)
    else:
        channel_id = 0
    return channel_id

#TODO チャンネルidから登録チャンネルのホーム画面に移動するプログラム
def get_Channel_Homepage(channel_id):
    return 'https://www.youtube.com/channel/'+channel_id

# チャンネルIDからチャンネルの全動画のプレイリストIDを取得
def get_Channel_PlaylistId(channel_id):
    channel = youtube.channels().list(part='snippet,contentDetails', id=channel_id).execute()
    item = channel['items'][0]
    playlist_id = item['contentDetails']['relatedPlaylists']['uploads']
    return playlist_id

# プレイリストIDからプレイリストに含まれる動画のIDを取得
def get_VideoIds(playlist_id, page_token):
    items_info = youtube.playlistItems().list(part='contentDetails', playlistId=playlist_id, maxResults=10, pageToken=page_token).execute()
    video_ids = list(map(lambda item: item['contentDetails']['videoId'], items_info['items']))
    # if 'nextPageToken' in items_info:
    #     video_ids.extend(getVideoIds(playlist_id, items_info['nextPageToken']))
    return video_ids

# 動画IDから動画の情報を取得
def get_Videos(video_ids):
    videos = []
    for index, video_id in enumerate(video_ids):
        video_info = youtube.videos().list(part='snippet,statistics', id=video_id).execute()
        videos.extend(video_info['items'])
    return videos

channel_name = get_channel_name()

channels = []
for name in channel_name:
    # チャンネル名からチャンネルidを取得
    channel_id = get_channel_Id(name)
    # チャンネルidからチャンネルのホーム画面のURLを取得
    channel_URL = get_Channel_Homepage(channel_id)
    channels.append((name, channel_id, channel_URL))

channel_URLs = pd.DataFrame(channels, columns=["チャンネル名", "channel_id","URL"])
channel_URLs.to_csv("channel_URLs.csv", index=False, encoding='utf-8')

"""
playlist_id = getChannelPlaylistId(channel_id)
video_ids = getVideoIds(playlist_id, None)
videos = getVideos(video_ids)
for video in videos:
    print(video['snippet']['title'], ',', 'https://youtube.com/watch?v=' + video['id'])
"""
    
