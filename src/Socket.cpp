#include "Socket.h"
#include "PlainSocket.h"
#include "TLSSocket.h"

Socket* Socket::create(boost::asio::io_service& iIoService, boost::asio::ssl::context* ipSslContext, std::string hostname, std::string port) {
	if (ipSslContext == NULL) {
		return new Plain_Socket(iIoService, hostname, port);
	}
   return new TLS_Socket(iIoService, *ipSslContext, hostname, port);
}

Socket::~Socket(){}

size_t Socket::_read(void *ipData, size_t iLength) {
	return boost::asio::read(getSocketForAsio(), boost::asio::buffer(ipData, iLength));
}
size_t Socket::_write(const void *ipData, size_t iLength) {
	return boost::asio::write(getSocketForAsio(), boost::asio::buffer(ipData, iLength));
}
