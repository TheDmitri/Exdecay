class ExdecayMap
{
  string MapName;
  bool IsDisable;
  int MaxPlayer;
  int Countdown;
  string ImagePath;
  string MapDescription;
  float X1,Y1,X2,Y2;
  ref array<ref MapPosition>Positions;

  void ExdecayMap(string mapName, bool isDisable, int maxPlayer, int countdown, string imagepath, string mapDescription, float x1, float y1, float x2, float y2)
  {
    MapName   = mapName;
    IsDisable = isDisable;
    MaxPlayer = maxPlayer;
    Countdown = countdown;
    ImagePath = imagepath;
    MapDescription = mapDescription;
    X1        = x1;
    Y1        = y1;
    X2        = x2;
    Y2        = y2;
    Positions = new array<ref MapPosition>;
  }

  void AddPosition(string name, vector position)
  {
    Positions.Insert(new MapPosition(name, position));
  }
}

class MapPosition
{
  string PointName;
  vector PointPosition;

  void MapPosition(string pointName, vector pointPosition)
  {
    PointName = pointName;
    PointPosition = pointPosition;
  }
}
