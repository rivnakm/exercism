using System;
using System.Linq;

class BirdCount
{
    private int[] birdsPerDay;

    public BirdCount(int[] birdsPerDay)
    {
        this.birdsPerDay = birdsPerDay;
    }

    public static int[] LastWeek()
    {
        return [0, 2, 5, 3, 7, 8, 4];
    }

    public int Today()
    {
        return this.birdsPerDay.Last();
    }

    public void IncrementTodaysCount()
    {
        var index = this.birdsPerDay.Length - 1;
        this.birdsPerDay[index]++;
    }

    public bool HasDayWithoutBirds()
    {
        return this.birdsPerDay.Any(bpd => bpd == 0);
    }

    public int CountForFirstDays(int numberOfDays)
    {
        return this.birdsPerDay.Take(numberOfDays).Sum();
    }

    public int BusyDays()
    {
        return this.birdsPerDay.Where(bpd => bpd >= 5).Count();
    }
}
