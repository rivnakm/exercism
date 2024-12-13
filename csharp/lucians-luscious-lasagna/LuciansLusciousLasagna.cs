class Lasagna
{
    public int ExpectedMinutesInOven() => 40;

    public int RemainingMinutesInOven(int elapsed)
    {
        return this.ExpectedMinutesInOven() - elapsed;
    }

    public int PreparationTimeInMinutes(int layers)
    {
        return layers * 2;
    }

    public int ElapsedTimeInMinutes(int layers, int elapsedTimeInOven)
    {
        return this.PreparationTimeInMinutes(layers) + elapsedTimeInOven;
    }
}
