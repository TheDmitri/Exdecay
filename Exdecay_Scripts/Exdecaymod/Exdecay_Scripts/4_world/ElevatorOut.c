class Land_EX_Building_Elevator_Out extends BuildingSuper
{
	private static ref set< Land_EX_Building_Elevator_Out > m_ExitElevators = new set< Land_EX_Building_Elevator_Out >;
	private int m_currentOwner = 0;
	private Land_EX_Building_Elevator_In destination;


	void Land_EX_Building_Elevator_Out()
	{
		m_ExitElevators.Insert( this );
		RegisterNetSyncVariableInt("m_currentOwner");
	}
	void ~Land_EX_Building_Elevator_Out()
	{
		int i;

		i = m_ExitElevators.Find( this );
		if ( i >= 0 )
		{
			m_ExitElevators.Remove( i );
		}
	}
	static set< Land_EX_Building_Elevator_Out > GetAll()
	{
		return m_ExitElevators;
	}
	void OpenDoors()
	{
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(OpenDoor, 5000, false, 0);
	}
	void CloseDoors()
	{
		SetAnimationPhase("Door_l",0);
	}
	void SetOwner(int OwnerID)
	{
		Print("SetOwner to " + OwnerID);
		if (OwnerID == 0)
		{
			ExdecayStashObject stash;
			if(ExdecayStashObject.GetMapAll().Find(this.GetOwner(), stash))
			{
				stash.SetPosition("52 1 1282");
			}
			else
			{
				for (int i = 0; i < ExdecayStashObject.GetAll().Count(); i++)
				{
					stash = ExdecayStashObject.GetAll()[i];
					if (stash.GetOwner() == this.GetOwner())
					{
						stash.SetPosition("52 1 1282");
					}
				}
			}
		}
		m_currentOwner = OwnerID;
		if ( GetGame().IsServer() )
			SetSynchDirty();
	}

	int GetOwner()
	{
		return m_currentOwner;
	}
	void SetDestination(Land_EX_Building_Elevator_In dest)
	{
		destination = dest;
		destination.SetOwner(this.GetOwner());
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(ProcessTransfer, 7000, false);
	}
	Land_EX_Building_Elevator_In GetDestination()
	{
		return destination;
	}
	vector GetOffset(vector playerPos)
	{
		return GetPosition() - playerPos;
	}
	void AssignOutput()
	{
		for (int i = 0; i < Land_EX_Building_Elevator_In.GetAll().Count(); i++)
		{
			Land_EX_Building_Elevator_In outputElevator = Land_EX_Building_Elevator_In.GetAll()[i];
			if (outputElevator.GetOwner() == 0)
			{
				GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(CloseDoor, 2000, false, 0);
				SetDestination(outputElevator);
				return;
			}
		}
	}
	void SetupHideout()
	{
		bool hasStash = false;
		vector offset = "6.82 0 -6.852";
		vector elevatorPos = this.GetPosition();
		vector stashPos = elevatorPos + offset;
		ref array<Object> nearest_objects = new array<Object>;
		ref array<CargoBase> proxy_cargos = new array<CargoBase>;

		GetGame().GetObjectsAtPosition( stashPos, 1, nearest_objects, proxy_cargos );
		for ( int j = 0; j < nearest_objects.Count(); j++ )
		{
			Object nearest_object = nearest_objects.Get(j);
			if ( nearest_object.IsInherited( ExdecayStashObject ) )
				nearest_object.SetPosition("52 1 1282");
		}
		ExdecayStashObject stash;
		if(ExdecayStashObject.GetMapAll().Find(this.GetOwner(),stash))
		{
			stash.SetPosition(stashPos);
			stash.Lock();
			hasStash = true;
		}
		else
		{
			for (int i = 0; i < ExdecayStashObject.GetAll().Count(); i++)
			{
				stash = ExdecayStashObject.GetAll()[i];
				if (stash.GetOwner() == this.GetOwner())
				{

					stash.SetPosition(stashPos);
					stash.Lock();
					hasStash = true;
				}
			}
		}
		if (!hasStash)
		{
			Print("No stash found, created. ID: " + this.GetOwner());
			ExdecayStashObject newStash = GetGame().CreateObject("ExdecayStashObject", stashPos);
			newStash.SetOwner(this.GetOwner());
			newStash.InitStarterKit();
		}
	}
	void ProcessTransfer() //placeholder for testing
	{
		Print("Transfer begins");
		ref array<Object> nearest_objects = new array<Object>;
		ref array<CargoBase> proxy_cargos = new array<CargoBase>;

		GetGame().GetObjectsAtPosition( GetPosition(), 3, nearest_objects, proxy_cargos );

		for ( int i = 0; i < nearest_objects.Count(); i++ )
		{
			Object nearest_object = nearest_objects.Get(i);
			Print("Transfer found object! Next print should be this or asdf");
			if ( nearest_object.IsInherited( PlayerBase ) )
			{
				Print("asdf");
				PlayerBase player = PlayerBase.Cast( nearest_object );
				Print("Current Player POS: " + player.GetPosition());
				Print("Current Elevator POS: " + this.GetPosition());
				Print("Destination POS: " + GetDestination().GetPosition());
				vector destPos = GetDestination().GetPosition();
				vector offset = this.GetOffset(player.GetPosition());
				vector WarpTo = (destPos - offset);
				player.SetPosition(WarpTo);
				NotificationSystem.Create(new StringLocaliser("Hideout Elevator"), new StringLocaliser( "Please exit the elevator in a timely manner."), "set:ccgui_enforce image:HudBuild", ARGB( 255, 221, 38, 38 ), 3, player.GetIdentity());
			}
		}
		Print("Release owner");
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(SetOwner, 5000, false, 0);
		GetDestination().ReleaseOwner();
		GetDestination().OpenDoors();
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(ClearHideout, 15000, false);
	}

	void ClearHideout() //very much placeholder
	{
		ref array<Object> nearest_objects = new array<Object>;
		ref array<CargoBase> proxy_cargos = new array<CargoBase>;
		GetGame().GetObjectsAtPosition( GetPosition(), 20, nearest_objects, proxy_cargos );

		for ( int i = 0; i < nearest_objects.Count(); i++ )
		{
			Object nearest_object = nearest_objects.Get(i);
			if ( nearest_object.IsInherited( PlayerBase ) )
			{
				PlayerBase player = PlayerBase.Cast( nearest_object );
				player.SetPosition("218.9 35 395.1");
				NotificationSystem.Create(new StringLocaliser("Hideout"), new StringLocaliser( "The owner of this hideout has left so you have been removed."), "set:ccgui_enforce image:HudBuild", ARGB( 255, 221, 38, 38 ), 3, player.GetIdentity());
			};
		};
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(CloseDoor, 2000, false, 0);
	}
	override void SetActions()
	{
		super.SetActions();
		AddAction(ActionExdecayDebugElevator);
		AddAction(ActionExdecaySendElevatorUp);
	}
}
