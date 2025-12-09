const std = @import("std");
const math = std.math;

pub fn squareOfSum(number: usize) usize {
    var result: usize = 0;
    for (1..number + 1) |n| {
        result += n;
    }
    return math.powi(usize, result, 2) catch 0;
}

pub fn sumOfSquares(number: usize) usize {
    var result: usize = 0;
    for (1..number + 1) |n| {
        result += math.powi(usize, n, 2) catch 0;
    }
    return result;
}

pub fn differenceOfSquares(number: usize) usize {
    return squareOfSum(number) - sumOfSquares(number);
}
