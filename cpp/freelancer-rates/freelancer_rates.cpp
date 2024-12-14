#include <cmath>

const int HOURS_PER_DAY = 8;
const int DAYS_PER_MONTH = 22;

// daily_rate calculates the daily rate given an hourly rate
double daily_rate(double hourly_rate)
{
    return hourly_rate * HOURS_PER_DAY;
}

// apply_discount calculates the price after a discount
double apply_discount(double before_discount, double discount)
{
    return before_discount * (1.0 - (discount / 100.0));
}

// monthly_rate calculates the monthly rate, given an hourly rate and a discount
// The returned monthly rate is rounded up to the nearest integer.
int monthly_rate(double hourly_rate, double discount)
{
    auto before_discount = daily_rate(hourly_rate) * DAYS_PER_MONTH;
    return std::ceil(apply_discount(before_discount, discount));
}

// days_in_budget calculates the number of workdays given a budget, hourly rate,
// and discount The returned number of days is rounded down (take the floor) to
// the next integer.
int days_in_budget(int budget, double hourly_rate, double discount)
{
    auto discounted_daily_rate = apply_discount(daily_rate(hourly_rate), discount);
    return std::floor(budget / discounted_daily_rate);
}
