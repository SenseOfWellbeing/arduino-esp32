import random
import time
import paho.mqtt.client as mqtt_client

broker = "172.17.104.141"
port = 1883
topic = 'temp'

msg = 0

# generate client ID with pub prefix randomly
client_id = "fe514e7d-a92d-4661-9723-a7a5d99ebb52"
username = 'SenseOfWellbeing'
password = 'admin01'

def connect_mqtt():
    def on_connect(client, userdata, flags, rc):
        if rc == 0:
            print("Connected to MQTT Broker!")
        else:
            print("Failed to connect, return code %d\n", rc)

    client = mqtt_client.Client(client_id)
    client.username_pw_set(username, password)
    client.on_connect = on_connect
    client.connect(broker, port)
    return client

def publish(client, msg):
    msg_count = 0
    while True:
        time.sleep(3)

        if(msg > 30):
            msg = msg - 1
        else:
            msg = msg + 1

        result = client.publish(topic, msg)
        # result: [0, 1]
        status = result[0]
        if status == 0:
            print(f"Send `{msg}` to topic `{topic}`")
        else:
            print(f"Failed to send message to topic {topic}")
        

def run():
    client = connect_mqtt()
    client.loop_start()
    publish(client, msg)


if __name__ == '__main__':
    run()
