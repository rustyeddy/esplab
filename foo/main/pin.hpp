#pragma once

enum pin_state_en {
    OPEN	= 0,
    CLOSED	= 1,

    LOW		= 0,
    HIGH	= 1,

    OFF		= 0,
    ON		= 1,
};

class Pin
{
protected:
    int			_gpio_pin;
    pin_state_en	_pin_state;

public:
    Pin(int p, gpio_mode_t m);

    void		open(); 
    void		close();

    bool		is_open()	{ return _pin_state == OPEN; }
    bool		is_closed()	{ return _pin_state == CLOSED; }
    pin_state_en	get_state()	{ return _pin_state; }
    //void		set_state(pin_state_en s);

    int IRAM_ATTR	set_state(pin_state_en s);
    void		toggle();
};
