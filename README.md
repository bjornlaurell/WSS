WSS
===

WebSocket to TCP Gateway

WSS is a WebSocket to TCP Gateway that was originally created to connect mosquitto.js to an MQTT broker.
It creates a WebSocket server and forwards any WebSocket traffic to a TCP Server.
For every new WebSocket connection a TCP connection to the destination server is created and bound to the corresponding WebSocket connection.
This results in a 1:1 mapping of WebSocket and TCP connections and ensures that the responses of the TCP server arrive at the original WebSocket client.

The goal was initially to create a bridge that is content INsensitive and only transmits the traffic AS IT IS from the broker to websocket clients (and reverse).
However, this approach is not ideal for MQTT as some JavaScript clients (including the reference implementation from Paho) can't handle multiple MQTT messages arriving at once (or fragmented messages arriving partly) in a WebSocket message.
In the mqtt branch of WSS is a version that reads the MQTT header and determins the length of the message. It uses that information to send exactly ONE MQTT message to the WebSocket client so that the JS libraries won't have problems.

The Websocket server uses version 0.2 of websocket++ (https://github.com/zaphoyd/websocketpp/tree/0.2.x) and the Boost C++ Libraries (http://www.boost.org/).

It was developed using the eclipse IDE.
The project configuration assumes that the boost and websocket++ header files and libraries are located in /usr/local/include and /usr/local/lib respectively. For boost headers and libs is searched in /usr/include and /usr/lib. If that doesn't match your setup just edit the eclipse project properties or build manually.

Manual build:
To create an executale that uses shared libraries run

g++ -o WSS_shared -I/usr/local/include -L/usr/local/lib -lpthread -lboost_program_options -lboost_regex -lboost_thread -lboost_system -lwebsocketpp  src/WSS.cpp -O3 -Wall

Make sure that you have all symlinks you need from libwebsocketpp.so.* to libwebsocketpp.so and to libwebsocketpp.so.0 and that the LD_LIBRARY_PATH contains the shared libraries when you execute the program.
To create a static linked executable run

g++ -o WSS_static src/WSS.cpp -I/usr/local/include  /usr/local/lib/libwebsocketpp.a /usr/lib/libboost_thread.a /usr/lib/libboost_regex.a /usr/lib/libboost_system.a /usr/lib/libboost_program_options.a -lpthread -O3 -Wall
