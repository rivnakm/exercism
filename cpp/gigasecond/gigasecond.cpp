#include "gigasecond.h"
#include <boost/date_time/posix_time/posix_time_duration.hpp>

namespace gigasecond
{
boost::posix_time::ptime advance(boost::posix_time::ptime current)
{
    auto gigasecond = boost::posix_time::seconds(1'000'000'000);
    return current + gigasecond;
}
} // namespace gigasecond
