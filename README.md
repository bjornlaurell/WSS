WSS
===

TLS-enabled-MQTT-aware WebSocket to TCP Gateway

It creates a WebSocket server and forwards any WebSocket traffic to a TCP Server.
For every new WebSocket connection a TCP connection to the destination server is created and bound to the corresponding WebSocket connection.
This results in a 1:1 mapping of WebSocket and TCP connections and ensures that the responses of the TCP server arrive at the original WebSocket client.
TCP traffic from the broker is analyzed so that only complete MQTT messages will be send to the Websocket client; one MQTT message in every WebSocket message. 

It uses version 0.2 of websocket++ (https://github.com/zaphoyd/websocketpp/tree/0.2.x) and the Boost C++ Libraries (http://www.boost.org/).

This version depends on OpenSSL.
The ssl folder contains example key, cert, ca and dh files to play with.

The Websocket Server was developed using the eclipse IDE.
It assumes the boost and websocket++ header files and libraries are located in /usr/local/include and /usr/local/lib respectively. Boost headers are expected to be in /usr/include/boost and libs in /usr/lib/. If that doesn't match your setup just edit the eclipse project properties and/or makefile.

```$ make all``` will compile debug and release versions. For more details see makefile.

```
                       +------------------------------------+
                       |               WSS                  |
                       |------------------------------------|
                       |                                    |
                       |                                    |
                       |                                    |
         --ws-keyfile  |                                    |   --broker-ca
         --ws-chainfile|                                    |
       +--------------->                                    +--------------> MQTT broker
                       |                                    |
                       |                                    |
                       |                                    |
                       |                                    |
                       |                                    |
                       +------------------------------------+
```

TLSv1 is used on the websocket side if both, the required chainfile and key are provided. Otherwise no encryption is used on the websocket side.
If you want to connect to a broker using TLS use the --broker-tls-enabled option. Otherwise an unencrypted connection to the MQTT broker is established.

To configure TLS on the websocket side there are the following parameter: --ws-keyfile <websocket server key file> --ws-chainfile <websocket server certificate file> and optionally --ws-dh-file <diffie-hellman parameter file>

For the MQTT broker side you can provide --broker-ca <MQTT broker CA>. When TLS is enabled (by --broker-tls-enabled) it uses this CA to verify authenticity the broker. By default self- signed broker certificates are accepted. Use --broker-do-not-accept-self-signed-certificates if you do NOT want to trust them. If no broker CA is given but TLS is enabled the remote peer will not be verified.

To use TLS versions other than TLSv1 specify --ws-tls-version <version> and/or --broker-tls-version <version>. This only works if you compiled with boost version 1.54 or later. Otherwise TLSv1 is used regardless of the specified version.
Use 'TLSv11' for version 1.1 or 'TLSv12' for version 1.2

To allow web browsers to trust the certificate used by WSS (when using TLS websockets) an HTTPS request can be send to the websocket server. The user can then accept the certificate and thereby allow the browser to connect to WSS in the future.
Type ```https://<WSS websocket host>:<WSS websocket port>``` into your browser's address bar, (verify the the certificate manually,) and tell your browser to trust the certificate used by WSS. Example: ```https://wsshost:1883``` 

sample invocation:

```$ ./WSS_release 
		--brokerHost wsshost 
		--ws-keyfile ssl/server.key 
		--ws-chainfile ssl/server.pem  
		--ws-dh-file ssl/dh.pem 
		--broker-ca ssl/ca.pem
		--broker-tls-enabled
``` 


