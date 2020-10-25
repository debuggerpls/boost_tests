#include <iostream>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>


class Printer
{
  public:
  explicit Printer(boost::asio::io_service &io);
  ~Printer();

  void print(const boost::system::error_code& /*e*/);

  private:
  boost::asio::deadline_timer _t;
  int _count;
};

Printer::Printer(boost::asio::io_service &io) : _t(io, boost::posix_time::seconds(1)), _count(0) 
{
  _t.async_wait(boost::bind(&Printer::print, this, boost::asio::placeholders::error));
}


Printer::~Printer()
{
  std::cout << boost::posix_time::microsec_clock::local_time() << " : Final count = " << _count << '\n';
}


void Printer::print(const boost::system::error_code& /*e*/)
{
  std::cout << boost::posix_time::microsec_clock::local_time() << " : handler called, count = " << _count << '\n';
  
  if (_count < 5)
  {
    ++_count;

    _t.expires_at(_t.expires_at() + boost::posix_time::seconds(1));
    _t.async_wait(boost::bind(&Printer::print, this, boost::asio::placeholders::error));    
  }
}

int main()
{
  boost::asio::io_service io;

  std::cout << boost::posix_time::microsec_clock::local_time() << " : constructing Printer\n";

  Printer printer(io);

  io.run();
  std::cout << boost::posix_time::microsec_clock::local_time() << " : io_service::run()\n";

  return 0;
}