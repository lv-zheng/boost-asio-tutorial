#include <array>
#include <iostream>
#include <string>

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main()
{
	boost::asio::io_service io_service;
	tcp::acceptor acc(io_service, tcp::endpoint(tcp::v6(), 9876));

	while (1) {
		boost::system::error_code ignored;

		tcp::socket socket(io_service);
		acc.accept(socket);

		std::array<char, 256> input_buffer;
		std::size_t input_size = socket.read_some(
				boost::asio::buffer(input_buffer),
				ignored);
		std::string visitor(input_buffer.data(),
				input_buffer.data() + input_size);

		std::cout << "Visited from " +
			socket.remote_endpoint().address().to_string() +
			" by visitor " << visitor << std::endl;

		std::string message = "Hello, you are " + visitor + "\n";
		boost::asio::write(socket, boost::asio::buffer(message), ignored);

		socket.shutdown(tcp::socket::shutdown_both, ignored);
		socket.close();
	}
	return 0;
}
