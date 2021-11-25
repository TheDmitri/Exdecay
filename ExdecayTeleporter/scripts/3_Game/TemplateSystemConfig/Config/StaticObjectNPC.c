class StaticObjectNPC
{
  string Classname;
  vector Position;
  vector Orientation;

  void StaticObjectNPC(string classname, vector position, vector orientation)
  {
    Classname = classname;
    Position = position;
    Orientation = orientation;
  }
}
