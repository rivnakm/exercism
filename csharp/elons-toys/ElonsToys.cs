class RemoteControlCar
{
    private int _batteryPercent = 100;
    private int _distanceDrivenMeters = 0;

    public static RemoteControlCar Buy()
    {
        return new RemoteControlCar();
    }

    public string DistanceDisplay()
    {
        return $"Driven {this._distanceDrivenMeters} meters";
    }

    public string BatteryDisplay()
    {
        return this._batteryPercent == 0 ? "Battery empty" : $"Battery at {this._batteryPercent}%";
    }

    public void Drive()
    {
        if (this._batteryPercent > 0)
        {
            this._batteryPercent -= 1;
            this._distanceDrivenMeters += 20;
        }
    }
}
