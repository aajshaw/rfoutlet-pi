# About rfoutlet-pi

This is a super-simple standalone program for controlling the Etekcity Wireless
Remote Control Electrical Outlet Switches,
[5-pack](http://smile.amazon.com/Etekcity-Wireless-Electrical-Household-Appliances/dp/B00DQELHBS), 
[3-pack](http://smile.amazon.com/Etekcity-Wireless-Electrical-Household-Appliances/dp/B00DQ2KGNK) or
with [British socket](https://www.amazon.co.uk/gp/product/B01FX9U0WA/ref=ppx_yo_dt_b_asin_title_o02_s00?ie=UTF8&psc=1)
and probably other models, from your Raspberry Pi.

The code is based off of that of
[433Utils](https://github.com/ninjablocks/433Utils), although it has been
cleaned up and reduced to the bare bones minimum. It is also written in C
rather than C++. Also changed so command line arguments are used rather than constants

# Requirements

* Raspberry Pi
* Development toolchain; git, gcc, etc.
* RF 433 MHz transmitter module, such as [this one from SMAKN](http://smile.amazon.com/gp/product/B00M2CUALS)

# Installation and Usage

1. Wire the 433 MHz module up to wiringPi ping 0 (Broadcom pin 17)
1. Install wiringpi if you don't have it already; this should be available on your Pi distro of choice
1. Clone this repository
1. Run `make`
1. Run a command like `./rfoutlet 1 on` to turn switch 1 on

# Inspiration and related projects

* [433Utils](https://github.com/ninjablocks/433Utils)
* [rfoutlet](https://github.com/timleland/rfoutlet)
