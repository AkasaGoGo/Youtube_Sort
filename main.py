import os
from googleapiclient.discovery import build
from google.oauth2.credentials import Credentials
from google_auth_oauthlib.flow import InstalledAppFlow
import googleapiclient.errors
import pandas as pd

import json

SCOPES = 'https://www.googleapis.com/auth/youtube.readonly'
CLIENT_SECRETS_FILE = "client_secret.json"

# maxのAPI_KEY
YOUTUBE_API_KEY = "YOUR_YOUTUBE_API_KEY"  # あなたのAPIキーを入力
YOUTUBE_API_SERVICE_NAME = "youtube"
YOUTUBE_API_VERSION = "v3"


# oauth 2.0 の認証
def get_authenticated_service():
    # OAuth 2.0認証フローの設定
    flow = InstalledAppFlow.from_client_secrets_file(CLIENT_SECRETS_FILE, SCOPES)
    credentials = flow.run_local_server(port=0)

    # 認証されたサービスを作成
    return credentials

def main():
    credentials = get_authenticated_service()
    
    youtube = googleapiclient.discovery.build(YOUTUBE_API_SERVICE_NAME, YOUTUBE_API_VERSION, credentials=credentials)
    
    # 自分のチャンネル一覧を取得するリクエストを作成
    channels_request = youtube.channels().list(
        part='snippet',
        mine=True,
        maxResults=5
    )
    
    channels_response = channels_request.execute()
    
    channels = []
    
    for channel in channels_response.get('items', []):
        if channel["kind"] == "youtube#channel":
            channel_info = (channel['snippet']['channelTitle'], channel['snippet']['title'], channel['id'])
            channels.append(channel_info)
    
    return channels

if __name__ == "__main__":
    result = main()
    print(result)
    
    
    
    
    
    
    
    
    # search_response = youtube.search().list(
    #     part=part,
    #     q=q,
    #     order=order,
    #     type=type
    # ) 
    
    # """
    # youtube: YouTube Data APIのクライアントインスタンスを表します。これにより、APIへのリクエストを行うことができます。
    # search(): 検索操作を行うためのメソッドです。
    # list(): 検索リクエストを実行するためのメソッドです。引数として検索条件を指定できます。
    # part: APIから取得したい情報のパートを指定します。例えば、"snippet"を指定すると、検索結果のスニペット情報（タイトル、説明、サムネイルなど）が返されます。
    # q: 検索クエリを指定します。ここには検索したいキーワードやフレーズを入力します。
    # order: 検索結果の並び順を指定します。例えば、"viewCount"を指定すると、再生回数の多い順に結果が表示されます。
    # type: 検索対象の種類を指定します。例えば、"video"を指定すると動画のみを検索対象とします
    # """
    
    # output = youtube.search().list(
    #     part=part,
    #     q=q,
    #     order=order,
    #     type=type
    # ).execute() # output するデータを生成

    #一度に5件しか取得できないため何度も繰り返して実行
    # for i in range(num):        
    #     dic_list = dic_list + output['items']
    #     search_response = youtube.search().list_next(search_response, output)
    #     output = search_response.execute()

    # df = pd.DataFrame(dic_list)
    # #各動画毎に一意のvideoIdを取得
    # df1 = pd.DataFrame(list(df['id']))['videoId']
    # #各動画毎に一意のvideoIdを取得必要な動画情報だけ取得
    # df2 = pd.DataFrame(list(df['snippet']))[['channelTitle','publishedAt','channelId','title','description']]
    # ddf = pd.concat([df1,df2], axis = 1)

    # return ddf


#TODO C++のプログラムから channel_id を受け取る
def Channellist():
    channels = []
    channel_id = 'kpsJ44NNO9qOr9_0RbLLQg' # 小林悠人のチャンネルID
    search_responses = youtube.search().list(
        part = 'snippet, statistics',
        type = 'video',
        channelId = channel_id,
        maxResults=1,
    ).execute()
    
    for search_response in search_responses["items"]:
        if search_response["kind"] == "youtube#channel":
            # 動画タイトル
            title = search_response['snippet']['title']
            # チャンネル名
            channeltitle = search_response['snippet']['channelTitle']
            # 登録者数
            subscriberCount = search_response['statistics']['subscriberCount']
            # 再生回数
            videoCount = search_response['statistics']['videoCount']
            # 動画の投稿日時
            publishedDate = search_response['snippet']['publishedAt']
            
            channels.append(title, channeltitle, subscriberCount, videoCount, publishedDate)
        
        channel_reports = pd.DataFrame(channels, columns=["動画タイトル", "チャンネル名", "登録者数", "再生回数", "投稿日時"])
    return channel_reports

#TODO C++で開発されたDesktopアプリから検索データが送られてくるので、検索文字列を q に代入する 
# ddf = get_video_info(part='id,snippet', q = 'Python', order='viewCount', type='video', num = 1)
# ddf.to_csv('~/workspace/puroken/Youtube_Sort/Youtube_info.csv', index = None, encoding = "cp932")

#if __name__ == "__main__":
    # Channellist().to_csv("channel_reports.csv", index = None, encoding = 'cp932')
    #   main()
    


