from googleapiclient.discovery import build
from google_auth_oauthlib.flow import InstalledAppFlow
import googleapiclient.errors
import pandas as pd
import sys

# 必要なAPIキーまたは認証情報を設定
API_KEY = "YOUTUBE_DATA_API_KEY"  # あなたのAPIキーを入力　# 最終的に環境変数として指定する

SCOPES = 'https://www.googleapis.com/auth/youtube.force-ssl'

CLIENT_SECRETS_FILE = "client_secret.json" # OAuth 2.0 の認証に必要なファイル

YOUTUBE_API_SERVICE_NAME = "youtube"
YOUTUBE_API_VERSION = "v3"

# OAuth 2.0の認証
def get_authenticated_service():
    flow = InstalledAppFlow.from_client_secrets_file(CLIENT_SECRETS_FILE, SCOPES)
    credentials = flow.run_local_server(port=8087)
    return credentials

def main(channelId):
    # 認証情報を取得
    credentials = get_authenticated_service()

    # YouTube Data APIを構築
    youtube = build(YOUTUBE_API_SERVICE_NAME, YOUTUBE_API_VERSION, developerKey=API_KEY, credentials=credentials)

    try:
        # 自分がチャンネル登録した動画を取得
        subscriptions_request = youtube.subscriptions().list(
            part='snippet',
            channelId = channelId, # youtube の channelId
            maxResults=10  # 取得する最大件数を指定（最大50件まで）
        )
        subscriptions_response = subscriptions_request.execute()
        
        channels = []
        for subscription in subscriptions_response['items']:
            # チャンネルタイトル
            channel_title = subscription['snippet']['title']
            # 動画の投稿日時
            publishedDate = subscription['snippet']['publishedAt']
            # チャンネルId
            channelId = subscription['snippet']['channelId']
            
            channels.append((channel_title, publishedDate, channelId))
            
        # 動画が投稿されていない場合には、AttributeError: 'NoneType' object has no attribute 'replace'　というエラーが発生
        channel_reports = pd.DataFrame(channels, columns=["チャンネル名", "投稿日時", "channelId"])
        print(channel_reports)
        channel_reports.to_csv("channel_reports.csv", index=False, encoding='utf-8')
            
    except googleapiclient.errors.HttpError as e:
        print("An error occurred:", e)

if __name__ == "__main__":
    #TODO フロントからCHANNELIDを取得する
    args = sys.argv
    if 2 == len(args): # .py と channelIdの2つ
        if type(args[1]) is str:
            channelId = args[1]
        else:
            print("Argument is not str")
    else:
        print("Arguments are too short")
    main(channelId)
