.. _i2c_scanner:

I2C Scanner sample
##################

Overview
********
This sample sends I2C messages without any data (i.e. stop condition
after sending the just the address), and if there is an ACK for the
address, it prints it prints the address as ``FOUND``.

Warning!
--------

This is essentially the SMBus "quick write" command, which is
known to corrupt the Atmel AT24RF08 EEPROM found on many
IBM Thinkpad laptops. Keep this is mind when running. See this_.

.. _this: https://git.kernel.org/pub/scm/utils/i2c-tools/i2c-tools.git/tree/tools/i2cdetect.8#n66


Building and Running
********************
.. zephyr-app-commands::
   :zephyr-app: samples/drivers/i2c_scanner
   :board: nrf52840_blip
   :conf: "prj.conf overlay-nrf52.conf"
   :goals: build flash

