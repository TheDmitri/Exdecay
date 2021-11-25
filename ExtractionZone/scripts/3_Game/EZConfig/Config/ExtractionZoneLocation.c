class ExtractionZoneLocation
{
    string      ZoneName;
    vector      Position;
    vector      Destination;
    float       Radius;
    float       ProbToSpawn;
    int         Countdown;
    bool        EnableParticle;
    string      ParticleName;
    bool        DisableUI;

    void ExtractionZoneLocation(string zonename, vector pos, vector dest, float radius, float probtospawn, int countdown, bool enableparticle, bool disableui, string particlename = "Green")
	  {
      DisableUI = disableui;
      ZoneName = zonename;
      Position = pos;
      Destination = dest;
      Radius = radius;
      ProbToSpawn = probtospawn;
      Countdown = countdown;
      EnableParticle = enableparticle;
      ParticleName = particlename;
    }
};
