class RemoteControlCar
{
    private int _speed;
    private int _batteryDrain;

    private int _batteryLevel;
    private int _distanceDriven;

    public RemoteControlCar(int speed, int batteryDrain)
    {
        this._speed = speed;
        this._batteryDrain = batteryDrain;

        this._batteryLevel = 100;
        this._distanceDriven = 0;
    }

    public bool BatteryDrained()
    {
        return this._batteryLevel < this._batteryDrain;
    }

    public int DistanceDriven()
    {
        return this._distanceDriven;
    }

    public void Drive()
    {
        if (this.BatteryDrained())
        {
            return;
        }

        this._batteryLevel -= this._batteryDrain;
        this._distanceDriven += this._speed;
    }

    public static RemoteControlCar Nitro()
    {
        return new RemoteControlCar(50, 4);
    }
}

class RaceTrack
{
    private int _distance;

    public RaceTrack(int distance)
    {
        this._distance = distance;
    }

    public bool TryFinishTrack(RemoteControlCar car)
    {
        while (!car.BatteryDrained())
        {
            car.Drive();
        }

        return car.DistanceDriven() >= this._distance;
    }
}
