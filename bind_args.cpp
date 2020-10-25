#include <iostream>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

void print(const boost::system::error_code& /*e*/, boost::asio::deadline_timer *t, int *count)
{
  std::cout << boost::posix_time::microsec_clock::local_time() << " : handler called, count = " << *count << '\n';
  
  if (*count < 5)
  {
    ++(*count);

    t->expires_at(t->expires_at() + boost::posix_time::seconds(1));
    t->async_wait(boost::bind(print, boost::asio::placeholders::error, t, count));    
  }
}

int main()
{
  boost::asio::io_service io;

  std::cout << boost::posix_time::microsec_clock::local_time() << " : creating timer\n";

  int count = 0;
  boost::asio::deadline_timer t(io, boost::posix_time::seconds(1));
  t.async_wait(boost::bind(print, boost::asio::placeholders::error, &t, &count));

  io.run();
  std::cout << boost::posix_time::microsec_clock::local_time() << " : io_service::run(), count = " << count << '\n';

  return 0;
}