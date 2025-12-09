const std = @import("std");
const math = std.math;

pub const Coordinate = struct {
    x: f32,
    y: f32,

    pub fn init(x_coord: f32, y_coord: f32) Coordinate {
        return Coordinate{
            .x = x_coord,
            .y = y_coord,
        };
    }

    pub fn score(self: Coordinate) usize {
        const distance_from_center: f32 = @abs(math.sqrt(self.x * self.x + self.y * self.y));
        if (distance_from_center <= 1.0) {
            return 10;
        }
        if (distance_from_center <= 5.0) {
            return 5;
        }
        if (distance_from_center <= 10.0) {
            return 1;
        }
        return 0;
    }
};
