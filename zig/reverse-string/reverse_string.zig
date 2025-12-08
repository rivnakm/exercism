/// Writes a reversed copy of `s` to `buffer`.
pub fn reverse(buffer: []u8, s: []const u8) []u8 {
    if (s.len == 0) {
        return buffer[0..0];
    }
    for (0..s.len) |i| {
        buffer[s.len - i - 1] = s[i];
    }
    return buffer[0..s.len];
}
