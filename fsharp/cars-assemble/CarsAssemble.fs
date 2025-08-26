module CarsAssemble

let successRate (speed: int): float =
    if speed = 0 then
        0.0
    elif speed <= 4 then
        1.0
    elif speed <= 8 then
        0.9
    elif speed = 9 then
        0.8
    elif speed = 10 then
        0.77
    else
        raise (System.ArgumentOutOfRangeException(nameof speed))

let productionRatePerHour (speed: int): float =
    let baseRate = 221.0
    successRate speed * baseRate * float speed

let workingItemsPerMinute (speed: int): int =
    let perHour = productionRatePerHour speed
    int (perHour / 60.0)
