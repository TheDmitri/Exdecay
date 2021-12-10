class Land_EX_Building_Elevator_In extends BuildingSuper
{
	private static ref set< Land_EX_Building_Elevator_In > m_EntranceElevators = new set< Land_EX_Building_Elevator_In >;
	private int m_currentOwner = 0;
	private bool m_DoorState = false;
	private int m_LoiterCount = 0;
	private Land_EX_Building_Elevator_Out destination;


	void Land_EX_Building_Elevator_In()
	{
		m_EntranceElevators.Insert( this );
		RegisterNetSyncVariableInt("m_currentOwner");
		RegisterNetSyncVariableBool("m_DoorState");
	}

	void ~Land_EX_Building_Elevator_In()
	{
		if(!m_EntranceElevators)
			return;

		int i;

		i = m_EntranceElevators.Find( this );
		if ( i >= 0 )
		{
			m_EntranceElevators.Remove( i );
		}
	}

	static set< Land_EX_Building_Elevator_In > GetAll()
	{
		return m_EntranceElevators;
	}

	void OpenDoors()
	{
		//SetAnimationPhase("Door_l",1);
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(OpenDoor, 5000, false, 0);
	}

	void CloseDoors()
	{
		SetAnimationPhase("Door_l",0);
	}

	bool GetDoorState()
	{
		return m_DoorState;
	}

	void SetDoorState(bool state)
	{
		Print("SetDoorState to " + state);
		m_DoorState = state;
		SetSynchDirty();
	}

	void SetOwner(int OwnerID)
	{
		Print("SetOwner to " + OwnerID);
		m_currentOwner = OwnerID;
		SetSynchDirty();
	}

	int GetOwner()
	{
		return m_currentOwner;
	}
	bool IsEmpty()
	{
		ref array<Object> nearest_objects = new array<Object>;
		ref array<CargoBase> proxy_cargos = new array<CargoBase>;

		GetGame().GetObjectsAtPosition( GetPosition(), 4, nearest_objects, proxy_cargos );

		for ( int i = 0; i < nearest_objects.Count(); i++ )
		{
			Object nearest_object = nearest_objects.Get(i);
			if ( nearest_object.IsInherited( PlayerBase ) )
			{
				return false;
			}
		}
		return true;
	}
	void ReleaseOwner()
	{
		Print("ReleaseOwner Start");
		if ( !IsEmpty())
		{
			Print("ReleaseOwner NotEmpty");
			if ( m_LoiterCount < 2)
			{
				Print("ReleaseOwner LoiterCount is less than 2. LoiterCount: " + m_LoiterCount);
				if ( m_LoiterCount != 0)
				{
					ref array<Object> nearest_objects = new array<Object>;
					ref array<CargoBase> proxy_cargos = new array<CargoBase>;

					GetGame().GetObjectsAtPosition( GetPosition(), 4, nearest_objects, proxy_cargos );

					for ( int i = 0; i < nearest_objects.Count(); i++ )
					{
						Object nearest_object = nearest_objects.Get(i);
						if ( nearest_object.IsInherited( PlayerBase ) )
						{
							PlayerBase player = PlayerBase.Cast( nearest_object );
							NotificationSystem.Create(new StringLocaliser("Hideout Elevator"), new StringLocaliser( "Please exit the elevator in a timely manner."), "set:ccgui_enforce image:HudBuild", ARGB( 255, 221, 38, 38 ), 3, player.GetIdentity());
						}
					}
				}
				m_LoiterCount++;

				GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(ReleaseOwner, 25000, false);

			}
			else //<pos x="683.888" z="595.531" />
			{
				Print("ReleaseOwner LoiterCount is more than 2. LoiterCount: " + m_LoiterCount);
				m_LoiterCount = 0;
				//close doors here.
				CloseDoor(0);
				ref array<Object> nearest_objects2 = new array<Object>;
				ref array<CargoBase> proxy_cargos2 = new array<CargoBase>;
				GetGame().GetObjectsAtPosition( GetPosition(), 3, nearest_objects2, proxy_cargos2 );
				for ( int j = 0; j < nearest_objects2.Count(); j++ )
				{
					Object nearest_object2 = nearest_objects2.Get(j);
					if ( nearest_object2.IsInherited( PlayerBase ) )
					{
						PlayerBase player2 = PlayerBase.Cast( nearest_object2 );
						player2.SetPosition("218.9 35 395.1")
						NotificationSystem.Create(new StringLocaliser("Hideout Elevator"), new StringLocaliser( "Do not loiter in the elevators! Your behavior has been logged."), "set:ccgui_enforce image:HudBuild", ARGB( 255, 221, 38, 38 ), 3, player2.GetIdentity());
					}
				}
				Print("ReleaseOwner has kicked loiterers and is setting owner to 0!")
				SetOwner(0);
			}
		}
		else
		{
			Print("ReleaseOwner: Empty and setting owner to 0 and closing door!");
			SetOwner(0);
			CloseDoor(0);
			m_LoiterCount = 0;
		}
	}
	void SetDestination(Land_EX_Building_Elevator_Out dest)
	{
		Print("Destination found!");
		destination = dest;
		destination.SetOwner(this.GetOwner());
	}
	Land_EX_Building_Elevator_Out GetDestination()
	{
		return destination;
	}
	vector GetOffset(vector playerPos)
	{
		Print("Getoffset running. GetPosition: " + GetPosition() + " PlayerPos: " + playerPos);
		Print("The offset is: " + (GetPosition() - playerPos));
		return GetPosition() - playerPos;
	}
	void AssignOutput(bool sendSolo)
	{
		Print("AssignOutput start");
		Print("Exits found: " + Land_EX_Building_Elevator_Out.GetAll().Count());

		for (int i = 0; i < Land_EX_Building_Elevator_Out.GetAll().Count(); i++)
		{
			Land_EX_Building_Elevator_Out outputElevator = Land_EX_Building_Elevator_Out.GetAll()[i];
			Print("Exit owner: " + outputElevator.GetOwner());
			if (outputElevator.GetOwner() == 0)
			{

				SetDestination(outputElevator);
				CloseDoor(0);
				GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(ProcessTransfer, 5000, false, sendSolo);
				return;
			}
		}
	}

	void ProcessTransfer(bool sendSolo) //placeholder for testing
	{
		Print("Transfer begins");
		ref array<Object> nearest_objects = new array<Object>;
		ref array<CargoBase> proxy_cargos = new array<CargoBase>;

		GetGame().GetObjectsAtPosition( GetPosition(), 2, nearest_objects, proxy_cargos );

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
				if (!sendSolo)
					player.SetPosition(WarpTo);
				if (sendSolo )
				{
					if (player.GetIdentity().GetPlainId().Substring(8, 9).ToInt() == GetDestination().GetOwner())
						player.SetPosition(WarpTo);
					else
					{
						player.SetPosition("218.9 35 395.1")
						NotificationSystem.Create(new StringLocaliser("Hideout Elevator"), new StringLocaliser( "The elevator owner chose to go solo, you have been moved back to town."), "set:ccgui_enforce image:HudBuild", ARGB( 255, 221, 38, 38 ), 3, player.GetIdentity());
					}

				}
			}
		}
		Print("Release owner");
		GetDestination().SetupHideout();
		GetDestination().OpenDoors();
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(SetOwner, 5000, false, 0);

	}
	override void SetActions()
	{
		super.SetActions();

		AddAction(ActionExdecaySummonElevator);
		AddAction(ActionExdecayDebugElevator);
		AddAction(ActionExdecaySendElevator);
		AddAction(ActionExdecaySendElevatorSolo);
	}
}
