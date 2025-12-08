const std = @import("std");
const mem = std.mem;

pub fn abbreviate(allocator: mem.Allocator, words: []const u8) mem.Allocator.Error![]u8 {
    var atWordStart = true;
    var result = std.array_list.Aligned(u8, null).empty;
    defer result.deinit(allocator);

    for (words) |c| {
        if (atWordStart) {
            if (std.ascii.isAlphabetic(c)) {
                try result.append(allocator, std.ascii.toUpper(c));
                atWordStart = false;
            }
        } else if (c == ' ' or c == '-') {
            atWordStart = true;
        }
    }

    return result.toOwnedSlice(allocator);
}
