const std = @import("std");

pub fn convert(buffer: []u8, n: u32) []const u8 {
    var pos: usize = 0;
    if (n % 3 == 0) {
        @memcpy(buffer.ptr + pos, "Pling");
        pos += 5;
    }
    if (n % 5 == 0) {
        @memcpy(buffer.ptr + pos, "Plang");
        pos += 5;
    }
    if (n % 7 == 0) {
        @memcpy(buffer.ptr + pos, "Plong");
        pos += 5;
    }
    if (pos == 0) {
        pos += std.fmt.printInt(buffer, n, 10, std.fmt.Case.lower, .{});
    }
    
    return buffer[0..pos];
}
