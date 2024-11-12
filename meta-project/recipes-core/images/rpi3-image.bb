require recipes-core/images/rpi-test-image.bb

IMAGE_FEATURES_append = " ssh-server-dropbear"

IMAGE_INSTALL_append = " python3 python3-flask"
IMAGE_INSTALL_append = " vim"
IMAGE_INSTALL_append = " openssl paho-mqtt-c paho-mqtt-cpp"
IMAGE_INSTALL_append = " led-control-startup"

