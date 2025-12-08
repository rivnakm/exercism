const std = @import("std");

pub fn score(s: []const u8) u32 {
    var result: u32 = 0;
    for (s) |ch| {
        switch (std.ascii.toUpper(ch)) {
            'A', 'E', 'I', 'O', 'U', 'L', 'N', 'R', 'S', 'T' => result += 1,
            'D', 'G' => result += 2,
            'B', 'C', 'M', 'P' => result += 3,
            'F', 'H', 'V', 'W', 'Y' => result += 4,
            'K' => result += 5,
            'J', 'X' => result += 8,
            'Q', 'Z' => result += 10,
            else => {}
        }
    }
    
    return result;
}
