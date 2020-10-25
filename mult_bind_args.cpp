#include <iostream>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

void print(const boost::system::error_code& /*e*/, boost::asio::deadline_timer *t, int *count, int *id)
{
  std::cout << boost::posix_time::microsec_clock::local_time() << " : ID=" << *id << " handler called, count = " << *count << '\n';
  
  if (*count < 5)
  {
    ++(*count);

    t->expires_at(t->expires_at() + boost::posix_time::seconds(*id == 1 ? 1 : 2));
    t->async_wait(boost::bind(print, boost::asio::placeholders::error, t, count, id));    
  }
}

int main()
{
  boost::asio::io_service io;

  std::cout << boost::posix_time::microsec_clock::local_time() << " : creating timer\n";

  int count1 = 0;
  int count2 = 0;
  int id1 = 1;
  int id2 = 2;
  boost::asio::deadline_timer t1(io, boost::posix_time::seconds(1));
  boost::asio::deadline_timer t2(io, boost::posix_time::seconds(2));
  t1.async_wait(boost::bind(print, boost::asio::placeholders::error, &t1, &count1, &id1));
  t2.async_wait(boost::bind(print, boost::asio::placeholders::error, &t2, &count2, &id2));

  io.run();
  std::cout << boost::posix_time::microsec_clock::local_time() << " : io_service::run(), count1 = " << count1 << ", count2 = " << count2 <<'\n';

  return 0;
}