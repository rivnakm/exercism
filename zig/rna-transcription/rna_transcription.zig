const std = @import("std");
const mem = std.mem;

pub fn toRna(allocator: mem.Allocator, dna: []const u8) mem.Allocator.Error![]const u8 {
    var result = try allocator.alloc(u8, dna.len);
    for (dna, 0..) |nucleotide, i| {
        switch (nucleotide) {
            'G' => result[i] = 'C',
            'C' => result[i] = 'G',
            'T' => result[i] = 'A',
            'A' => result[i] = 'U',
            else => {}
        }
    }
    return result;
}
