set(COMPONENT_SRCS
	main.cpp
	button.cpp
	pin.cpp
	relay.cpp
	)
set(COMPONENT_ADD_INCLUDEDIRS "")
set(JUMPSTART_BOARD pins.hpp)

register_component()

component_compile_options("-DJUMPSTART_BOARD=\"${JUMPSTART_BOARD}\"")
