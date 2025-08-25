module LuciansLusciousLasagna

let expectedMinutesInOven = 40

let remainingMinutesInOven elapsed = expectedMinutesInOven - elapsed

let preparationTimeInMinutes layers = layers * 2

let elapsedTimeInMinutes layers timeInOven = 
    let prepTime = preparationTimeInMinutes layers
    prepTime + timeInOven
