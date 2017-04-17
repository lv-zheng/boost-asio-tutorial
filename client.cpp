#include <array>
#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <string>
using boost::asio::ip::tcp;
int main(int argc, char* argv[])
{
	boost::asio::io_service io_service;
	tcp::resolver resolver(io_service);
	tcp::resolver::query query("192.168.1.86", "9876");
	tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
	tcp::socket socket(io_service);
	boost::asio::connect(socket, endpoint_iterator);
        boost::system::error_code error;

	std::string my_name = "Zheng Lv";
	boost::asio::write(socket, boost::asio::buffer(my_name), error);

	std::array<char, 256> input_buffer;
	std::size_t rsize = socket.read_some(
			boost::asio::buffer(input_buffer), error);
	std::cout << std::string(input_buffer.data(), input_buffer.data() + rsize) << std::endl;
	return 0;
	
}
