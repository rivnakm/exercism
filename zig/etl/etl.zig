const std = @import("std");
const mem = std.mem;

pub fn transform(allocator: mem.Allocator, legacy: std.AutoHashMap(i5, []const u8)) mem.Allocator.Error!std.AutoHashMap(u8, i5) {
    var transformed = std.AutoHashMap(u8, i5).init(allocator);

    var iter = legacy.iterator();
    while (iter.next()) |kv| {
        const value = kv.key_ptr.*;
        for (kv.value_ptr.*) |char|{
            try transformed.put(std.ascii.toLower(char), value);
        }
    }

    return transformed;
}
