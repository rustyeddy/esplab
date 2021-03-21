idf_component_register(SRCS main.cpp mesh_mqtt_handle.c mqtt_example.c 
                    INCLUDE_DIRS ""
                    REQUIRES mcommon mconfig mwifi mlink mesh_mqtt_handle
)
