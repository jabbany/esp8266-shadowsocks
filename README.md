# esp8266-shadowsocks
This is an experiment to see if we can implement the shadowsocks protocol on
the cheap esp8266 microcontroller. ESP8266 can be deployed physically discreetly
so a socks5/ss compliant implementation would allow easy (and secure!) access 
into the deployed network.

## Why the ESP8266
I recently got a couple of these for fun. They're quite cheap and I thought 
implementing a SOCKS5/SS proxy would be a good way to test out both the limits
of the hardware and learn the platform.

As such this project is not meant to be terribly high quality. I will try my 
best to be faitful to the protocols and make things generally secure, but this 
is very much a hobby project.

New patches are welcome though!

## License
Parts of this code derive from ESP8266 example code and thus are licensed under
the LGPL. Other parts are licensed under the MIT license. 

Please see LICENSE for more details
