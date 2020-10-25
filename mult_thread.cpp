#include <iostream>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>


class Printer
{
  public:
  explicit Printer(boost::asio::io_service &io);
  ~Printer();

  void print1(const boost::system::error_code& /*e*/);
  void print2(const boost::system::error_code& /*e*/);

  private:
  boost::asio::deadline_timer _t1;
  boost::asio::deadline_timer _t2;
  int _count;
  boost::asio::strand _strand;
};

Printer::Printer(boost::asio::io_service &io) : _t1(io, boost::posix_time::seconds(1)), 
_t2(io, boost::posix_time::seconds(1)), _count(0), _strand(io) 
{
  _t1.async_wait(_strand.wrap(boost::bind(&Printer::print1, this, boost::asio::placeholders::error)));
  _t2.async_wait(_strand.wrap(boost::bind(&Printer::print2, this, boost::asio::placeholders::error)));
}


Printer::~Printer()
{
  std::cout << boost::posix_time::microsec_clock::local_time() << " : Final count = " << _count << '\n';
}


void Printer::print1(const boost::system::error_code& /*e*/)
{
  std::cout << boost::posix_time::microsec_clock::local_time() << " : #1 handler called, count = " << _count << '\n';
  
  if (_count < 5)
  {
    ++_count;

    _t1.expires_at(_t1.expires_at() + boost::posix_time::seconds(1));
    _t1.async_wait(_strand.wrap(boost::bind(&Printer::print1, this, boost::asio::placeholders::error)));    
  }
}

void Printer::print2(const boost::system::error_code& /*e*/)
{
  std::cout << boost::posix_time::microsec_clock::local_time() << " : #2 handler called, count = " << _count << '\n';
  
  if (_count < 5)
  {
    ++_count;

    _t2.expires_at(_t2.expires_at() + boost::posix_time::seconds(1));
    _t2.async_wait(_strand.wrap(boost::bind(&Printer::print2, this, boost::asio::placeholders::error)));    
  }
}

int main()
{
  boost::asio::io_service io;

  std::cout << boost::posix_time::microsec_clock::local_time() << " : constructing Printer\n";

  Printer printer(io);

  boost::thread t(boost::bind(&boost::asio::io_service::run, &io));
  io.run();
  t.join();
  std::cout << boost::posix_time::microsec_clock::local_time() << " : io_service::run()\n";

  return 0;
}