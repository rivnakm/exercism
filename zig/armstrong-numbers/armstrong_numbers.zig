const std = @import("std");

pub fn isArmstrongNumber(num: u128) bool {
    var digits: u128 = 0;
    var n = num;
    while (n > 0) {
        digits += 1;
        n /= 10;
    }
    
    var sum: u128 = 0;
    n = num;
    while (n > 0) {
        sum += std.math.powi(u128, n % 10, digits) catch return false;
        n /= 10;
    }
    
    return sum == num;
}
