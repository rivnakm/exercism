namespace targets
{
class Alien
{
  public:
    Alien(int x, int y) : x_coordinate(x), y_coordinate(y)
    {
    }

    int x_coordinate, y_coordinate;

    int get_health()
    {
        return _health;
    }

    bool hit()
    {
        if (_health > 0)
        {
            _health--;
        }
        return true;
    }

    bool is_alive()
    {
        return _health > 0;
    }

    bool teleport(int x, int y)
    {
        x_coordinate = x;
        y_coordinate = y;
        return true;
    }

    bool collision_detection(Alien other)
    {
        return x_coordinate == other.x_coordinate and y_coordinate == other.y_coordinate;
    }

  private:
    int _health{3};
};
} // namespace targets
