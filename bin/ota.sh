curl -d '{"state":{"desired":{"ota_url":"https://raw.githubusercontent.com/wiki/espressif/esp-jumpstart/images/hello-world.bin"}}}'         --tlsv1.2 --cert cloud_cfg/device.cert         --key cloud_cfg/device.key         https://a3orti3lw2padm-ats.iot.us-east-1.amazonaws.com:8443/things/7910d9de-999b-4fe0-908e-955731a5dcc5/shadow | python -mjson.tool