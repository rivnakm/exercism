#include <boost/date_time/posix_time/ptime.hpp>
#if !defined(GIGASECOND_H)
#define GIGASECOND_H

namespace gigasecond
{
boost::posix_time::ptime advance(boost::posix_time::ptime current);
} // namespace gigasecond

#endif // GIGASECOND_H
