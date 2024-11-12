DISCRIPTION="cpp application to receive the  mqtt message and turn on/off leds according the value"
SUMMARY="nothing"
LICENSE="CLOSED"
SRC_URI = "\
	file://Application.cpp \
	file://led_control.cpp \
	file://led_control_startup_system.service \
	file://parse_string.cpp \
	file://led_control.hpp \
	file://parse_string.hpp \
	file://mqtt-receive.cpp \
        file://mqtt-receive.hpp \
"

DEPENDS += "openssl paho-mqtt-c paho-mqtt-cpp"

S = "${WORKDIR}"
	
inherit systemd 

CXXFLAGS += "-I${STAGING_DIR_TARGET}/usr/include"
LDFLAGS += "-L${STAGING_DIR_TARGET}/usr/lib"
 

do_compile() {
    ${CXX} ${CXXFLAGS} ${LDFLAGS} Application.cpp mqtt-receive.cpp led_control.cpp parse_string.cpp  -o led_control_application -lpaho-mqttpp3 -lpaho-mqtt3a -lpaho-mqtt3c -lpaho-mqtt3as
}



do_install () {
	install -d ${D}${systemd_system_unitdir}
	install -m 0644 ${WORKDIR}/led_control_startup_system.service ${D}${systemd_system_unitdir}

	install -d ${D}${bindir}
	install -m 0755 led_control_application ${D}${bindir}
}


SYSTEMD_SERVICE_${PN} = "led_control_startup_system.service"
SYSTEMD_AUTO_ENABLE_${PN} = "enable"
SYSTEMD_PACKAGES ?= "${PN}"

