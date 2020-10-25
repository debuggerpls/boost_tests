#include <iostream>

#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

void print(const boost::system::error_code& /*e*/)
{
  std::cout << boost::posix_time::microsec_clock::local_time() << " : Hello, world!\n";
}

int main()
{
  boost::asio::io_service io;

  std::cout << boost::posix_time::microsec_clock::local_time() << " : creating timer\n";

  boost::asio::deadline_timer t(io, boost::posix_time::seconds(5));
  t.async_wait(&print);

  io.run();
  std::cout << boost::posix_time::microsec_clock::local_time() << " : io_service::run() \n";

  return 0;
}