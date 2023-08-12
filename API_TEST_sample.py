import os
from googleapiclient.discovery import build
from google_auth_oauthlib.flow import InstalledAppFlow
import googleapiclient.errors

# 必要なAPIキーまたは認証情報を設定
YOUTUBE_DATA_API_KEY = "YOUTUBE_DATA_API_KEY"  # YOUTUBE_DATA_APIキーを入力

SCOPES = 'https://www.googleapis.com/auth/youtube.force-ssl'
CLIENT_SECRETS_FILE = "client_secret.json"

YOUTUBE_API_SERVICE_NAME = "youtube"
YOUTUBE_API_VERSION = "v3"

# OAuth 2.0の認証
def get_authenticated_service():
    flow = InstalledAppFlow.from_client_secrets_file(CLIENT_SECRETS_FILE, SCOPES)
    credentials = flow.run_local_server(port=0)
    return credentials

def main():
    # 認証情報を取得
    credentials = get_authenticated_service()

    # YouTube Data APIを構築
    youtube = build(YOUTUBE_API_SERVICE_NAME, YOUTUBE_API_VERSION, developerKey=YOUTUBE_DATA_API_KEY, credentials=credentials)

    try:
        # 自分がチャンネル登録した動画を取得
        subscriptions_request = youtube.subscriptions().list(
            part='snippet',
            mine=True,
            maxResults=50  # 取得する最大件数を指定（最大50件まで）
        )
        subscriptions_response = subscriptions_request.execute()

        for subscription in subscriptions_response['items']:
            channel_title = subscription['snippet']['title']
            print(f"Channel Title: {channel_title}")

    except googleapiclient.errors.HttpError as e:
        print("An error occurred:", e)

if __name__ == "__main__":
    main()