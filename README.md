# Personalized fork of [tmk/tmk_keyboard/converter/terminal_usb](https://github.com/tmk/tmk_keyboard/tree/master/converter/terminal_usb)
This is a personalized layout based on TMK's 122 terminal usb converter. You may need to change the makefile in order to build, as it needs to include TMK_CORE. I do not include TMK_CORE, because I do not intend to update this repository regularly, and you should ensure you are using the latest TMK_CORE.

Source code: https://github.com/tmk/tmk_keyboard
Article: http://geekhack.org/index.php?topic=27272.0

## PREREQ
`dfu-programmer` or [teensy loader](https://www.pjrc.com/teensy/loader.html) to program chip
`avr-gcc` and `avr-libc` to build the firmware

## BUILD
`git clone https://github.com/hunterking/tmk122.git && cd tmk122` 
`git clone --recurse-submodules https://github.com/tmk/tmk_core.git`
`make`

## FLASH
First, set the teensy to bootloader mode by pressing the button.

### Using dfu-programmer
`dfu-programmer atmega32u4 erase`
`dfu-programmer atmega32u4 flash terminal_lufa.hex`
`dfu-programmer atmega32u4 reset`

### Using the teensy loader
Click the page icon and find the target `.hex` file. Push the reset button on the board, and then click the right-facing arrow icon to flash.

## RESOURCE
* Soarer's Converter: http://geekhack.org/index.php?topic=17458.0
* 102keys(1392595): http://geekhack.org/index.php?topic=10737.0
* 122keys(1390876): http://www.seasip.info/VintagePC/ibm_1390876.html
* KbdBabel: http://www.kbdbabel.org/
* RJ45 Connector: http://www.kbdbabel.org/conn/kbd_connector_ibmterm.png
* DIN Connector: http://www.kbdbabel.org/conn/kbd_connector_ibm3179_318x_319x.png
* WinAVR: http://winavr.sourceforge.net/

EOF
