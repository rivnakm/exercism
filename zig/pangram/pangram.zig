const std = @import("std");

pub fn isPangram(str: []const u8) bool {
    var seen = [_]u8{0} ** 26;
    for (str) |c| {
        if ((c >= 'a' and c <= 'z') or (c >= 'A' and c <= 'Z')) {
            const index = std.ascii.toLower(c) - 'a';
            seen[index] += 1;
        }
    }
    
    for (seen) |count| {
        if (count == 0) return false;
    }
    return true;
}
