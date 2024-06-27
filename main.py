import paho.mqtt.client as mqtt
import sqlite3
import datetime

MQTT_HOST = '210.86.239.240'
MQTT_PORT = 8080
MQTT_CLIENT_ID = 'Python MQTT client'
TOPIC = 'nhanhung/#'

DATABASE_DIRECTORY = 'daily_data/'


def on_connect(mqtt_client, user_data, flags, conn_result):
    mqtt_client.subscribe(TOPIC)


def on_message(mqtt_client, user_data, message):
    payload = message.payload

    db_conn = user_data['db_conn']
    current_date = datetime.date.today()
    db_file = f"{DATABASE_DIRECTORY}{current_date}.db"

    # Kết nối hoặc tạo tệp SQLite mới cho ngày hiện tại
    db_conn = sqlite3.connect(db_file)
    cursor = db_conn.cursor()

    # Kiểm tra và tạo bảng nếu chưa tồn tại
    cursor.execute(
        """
        CREATE TABLE IF NOT EXISTS sensors_data (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            topic TEXT NOT NULL,
            payload TEXT NOT NULL,
            created_at DATETIME NOT NULL
        )
        """
    )

    # Lưu trữ dữ liệu vào cơ sở dữ liệu SQLite
    sql = 'INSERT INTO sensors_data (topic, payload, created_at) VALUES (?, ?, ?)'
    dt_now = datetime.datetime.now()
    cursor.execute(sql, (message.topic, payload, dt_now))
    db_conn.commit()

    cursor.close()


def main():
    mqtt_client = mqtt.Client(MQTT_CLIENT_ID)
    mqtt_client.user_data_set({'db_conn': None})

    mqtt_client.on_connect = on_connect
    mqtt_client.on_message = on_message

    mqtt_client.connect(MQTT_HOST, MQTT_PORT)
    mqtt_client.loop_forever()


if __name__ == "__main__":
    # Tạo thư mục lưu trữ nếu chưa tồn tại
    import os
    os.makedirs(DATABASE_DIRECTORY, exist_ok=True)

    main()