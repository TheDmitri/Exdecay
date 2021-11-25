class ExtractionLocations
{
    bool              IsNotificationMsgActive;
    string            MsgOnEnterExtraction;
    string            MsgOnLeaveExtraction;
    ref array<bool>   EnableParticles;
    ref array<bool>   DisableUIs;
    ref array<string> ZoneNames;
    ref array<string> ParticleNames;
    ref array<vector> Positions;
    ref array<vector> Destinations;
    ref array<float>  Radius;
    ref array<int>    Countdowns;

    void ExtractionLocations(){

    }

    void InitExtractionLocations(ExtractionAreaSettings EZAreaSettings)
	  {
      IsNotificationMsgActive = EZAreaSettings.IsNotificationMsgActive;
      MsgOnEnterExtraction = EZAreaSettings.MsgOnEnterExtraction;
      MsgOnLeaveExtraction = EZAreaSettings.MsgOnLeaveExtraction;
      ZoneNames = new array<string>;
      EnableParticles = new array<bool>;
      Positions = new array<vector>;
      Destinations = new array<vector>;
      Countdowns = new array<int>;
      Radius = new array<float>;
      ParticleNames = new array<string>;
      DisableUIs= new array<bool>;
      TransferEZConfig(EZAreaSettings);
    }

    void TransferEZConfig(ExtractionAreaSettings EZAreaSettings)
    {
      for(int i = 0; i<EZAreaSettings.ExtractionAreaLocation.Count() ; i++)
      {
        int SpawnSeed = EZGetTimeStamp();
    		Math.Randomize(SpawnSeed);
        if(EZAreaSettings.ExtractionAreaLocation.Get(i).ProbToSpawn > Math.RandomFloat01())
        {
          GetEZLogger().LogInfo(EZAreaSettings.ExtractionAreaLocation.Get(i).ZoneName + " has been added !");
          ZoneNames.Insert(EZAreaSettings.ExtractionAreaLocation.Get(i).ZoneName);
          Positions.Insert(EZAreaSettings.ExtractionAreaLocation.Get(i).Position);
          Destinations.Insert(EZAreaSettings.ExtractionAreaLocation.Get(i).Destination);
          Radius.Insert(EZAreaSettings.ExtractionAreaLocation.Get(i).Radius);
          Countdowns.Insert(EZAreaSettings.ExtractionAreaLocation.Get(i).Countdown);
          EnableParticles.Insert(EZAreaSettings.ExtractionAreaLocation.Get(i).EnableParticle);
          ParticleNames.Insert(EZAreaSettings.ExtractionAreaLocation.Get(i).ParticleName);
          DisableUIs.Insert(!EZAreaSettings.ExtractionAreaLocation.Get(i).DisableUI);
        }
      }
    }
}
