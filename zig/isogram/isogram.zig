const std = @import("std");

pub fn isIsogram(str: []const u8) bool {
    var seen = [_]u8{0} ** 26;
    for (str) |c| {
        if ((c >= 'a' and c <= 'z') or (c >= 'A' and c <= 'Z')) {
            const index = std.ascii.toLower(c) - 'a';
            if (seen[index] != 0) return false;
            seen[index] = 1;
        }
    }
    return true;
}
