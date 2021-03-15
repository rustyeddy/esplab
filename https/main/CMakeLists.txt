idf_component_register(SRCS main.cpp wss_server.c keep_alive.c
                    INCLUDE_DIRS .
                    EMBED_TXTFILES certs/cacert.pem
                                   certs/prvtkey.pem
 				   certs/ca_cert.pem)
