const std = @import("std");
const mem = std.mem;

pub fn sum(allocator: mem.Allocator, factors: []const u32, limit: u32) !u64 {
    const HashContext = struct {
        pub fn hash(self: @This(), s: u32) u32 {
            _ = self;
            return s;
        }
        
        pub fn eql(self: @This(), a: u32, b: u32, b_index: usize) bool {
            _ = self;
            _ = b_index;
            return a == b;
        }
    };
    
    var multiples = std.ArrayHashMap(u32, void, HashContext, false).init(allocator);
    defer multiples.deinit();
    
    for (factors) |factor| {
        if (factor == 0) continue;
        var multiple = factor;
        while (multiple < limit) {
            try multiples.put(multiple, {});
            multiple += factor;
        }
    }
    
    var result: u64 = 0;
    for (multiples.keys()) |key| {
        result += key;
    }
    
    return result;
}
