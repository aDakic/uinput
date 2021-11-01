# uinput
The uinput library utilizes features of the uinput kernel module which makes it possible to emulate input devices from userspace. By writing to /dev/uinput device, a process can create a virtual input device with specific capabilities. Once this virtual device is created, the process can send events through it, that will be delivered to userspace and in-kernel consumers. More details: [uinput](https://www.kernel.org/doc/html/v4.12/input/uinput.html)


## Usage
The central component of the library is `uinput` class which accept features as template parameters. The following features are currently supported:
Name  | Description
------------- | -------------
keyboard_with_keys`<std::uint16_t... KeyCodes>`  | Provides keyboard_press and keyboard_relase for the keycodes defined as KeyCodes..., all supported keycodes are defined in [uinput_defines.hpp](https://github.com/aDakic/uinput/blob/main/include/uinput/uinput_defines.hpp#L48).


![Alt text](.demo/gif.gif)
