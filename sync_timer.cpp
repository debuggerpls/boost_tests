#include <iostream>

#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

int main()
{
  boost::asio::io_service io;

  std::cout << boost::posix_time::microsec_clock::local_time() << " : creating timer\n";

  boost::asio::deadline_timer t(io, boost::posix_time::seconds(5));
  t.wait();

  std::cout << boost::posix_time::microsec_clock::local_time() << " : Hello, world!\n";

  return 0;
}