#include "DrunkardOwnedStates.h"
#include "fsm/State.h"
#include "Drunkard.h"
#include "Locations.h"
#include "messaging/Telegram.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "Time/CrudeTimer.h"
#include "EntityNames.h"

#include <iostream>
using std::cout;


#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif


//------------------------------------------------------------------------SellChewingTobacco

SellChewingTobacco* SellChewingTobacco::Instance()
{
	static SellChewingTobacco instance;

	return &instance;
}


void SellChewingTobacco::Enter(Drunkard* pDrunkard)
{
	//if the Drunkard is not already located in the street, he must
	//change location to the street
	if (pDrunkard->Location() != street)
	{
		cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "Walkin' down the street.";

		pDrunkard->ChangeLocation(street);
	}
}


void SellChewingTobacco::Execute(Drunkard* pDrunkard)
{
	//Now the Drunkard is at the goldmine he digs for gold until he
	//is carrying in excess of MaxNuggets. If he gets thirsty during
	//his digging he packs up work for a while and changes state to
	//gp to the saloon for a whiskey.
	pDrunkard->AddToCashCarried(15);
	pDrunkard->IncreaseThirst();
	pDrunkard->IncreaseFatigue();

	cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "Good stuff ma frien'. Gimme dat sweet cash!";
	
	if (pDrunkard->Thirsty())
	{
		pDrunkard->GetFSM()->ChangeState(QuenchThirstDrunkard::Instance());
	}
}


void SellChewingTobacco::Exit(Drunkard* pDrunkard)
{
	cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": "
		<< "Ah'm leavin' the street with mah pockets full o' sweet dollerz!";
}


bool SellChewingTobacco::OnMessage(Drunkard* pDrunkard, const Telegram& msg)
{
	//send msg to global message handler
	return false;
}


//------------------------------------------------------------------------methods for GoHomeAndSnore

GoHomeAndSnore* GoHomeAndSnore::Instance()
{
  static GoHomeAndSnore instance;

  return &instance;
}

void GoHomeAndSnore::Enter(Drunkard* pDrunkard)
{
  if (pDrunkard->Location() != shack)
  {
	cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "*Bluerarghghghgh*";
    cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "Goi'hic home and sl'hic'p with my cat Tom...";
    pDrunkard->ChangeLocation(shack);   
  }
}

void GoHomeAndSnore::Execute(Drunkard* pDrunkard)
{ 
  //if Drunkard is not fatigued start to dig for nuggets again.
  if (!pDrunkard->Fatigued() && !pDrunkard->Drunk())
  {
     cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " 
          << "Aaah feelin' good again. Time to sell some tobacco and gets drunker than yesterday!";

     pDrunkard->GetFSM()->ChangeState(SellChewingTobacco::Instance());
  }

  else 
  {
    //sleep
	  if (pDrunkard->Fatigued())
		  pDrunkard->DecreaseFatigue();
	  else if (pDrunkard->Drunk())
		  pDrunkard->DecreaseDrunk();


    cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "Zrrrr Zrrrr Zrrrr... ";
  } 
}

void GoHomeAndSnore::Exit(Drunkard* pDrunkard)
{ 
}


bool GoHomeAndSnore::OnMessage(Drunkard* pDrunkard, const Telegram& msg)
{
   return false; //send message to global message handler
}

//------------------------------------------------------------------------QuenchThirstDrunkard

QuenchThirstDrunkard* QuenchThirstDrunkard::Instance()
{
  static QuenchThirstDrunkard instance;

  return &instance;
}

void QuenchThirstDrunkard::Enter(Drunkard* pDrunkard)
{
  if (pDrunkard->Location() != saloon)
  {    
    pDrunkard->ChangeLocation(saloon);

    cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "Boii is thusty! Time to get drunk again!";
  }
}

void QuenchThirstDrunkard::Execute(Drunkard* pDrunkard)
{
  pDrunkard->BuyAndDrinkAWhiskey();

  cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "Taste lik' wate. Should take anoth'one to be sure..";
  pDrunkard->IncreaseFatigue();
  if(!pDrunkard->Thirsty())
	pDrunkard->GetFSM()->ChangeState(GetDrunkerAndDrunker::Instance());  
}


void QuenchThirstDrunkard::Exit(Drunkard* pDrunkard)
{ 
  cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "Boii is no thusty anymore. Gotta drink fast.";
}


bool QuenchThirstDrunkard::OnMessage(Drunkard* pDrunkard, const Telegram& msg)
{
  //send msg to global message handler
  return false;
}

//------------------------------------------------------------------------GetDrunkerAndDrunker

GetDrunkerAndDrunker* GetDrunkerAndDrunker::Instance()
{
	static GetDrunkerAndDrunker instance;

	return &instance;
}

void GetDrunkerAndDrunker::Enter(Drunkard* pDrunkard)
{
	//nothing
}

void GetDrunkerAndDrunker::Execute(Drunkard* pDrunkard)
{
	pDrunkard->BuyAndDrinkAWhiskey();
	pDrunkard->IncreaseDrunk();
	pDrunkard->IncreaseFatigue();
	cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "Boiii gimme some real stuf'! Taste lik' buffalo piss!";
	cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "*Buuuuuurp*";
	cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "Speakin' ov bufalo piss, have you seen dis good ol' Bob ?";
	//Taunting Bob if he is here
	Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
		pDrunkard->ID(),        //ID of sender
		ent_Miner_Bob,            //ID of recipient
		Msg_Taunt,   //the message
		NO_ADDITIONAL_INFO);



	if (pDrunkard->Drunk() && pDrunkard->Fatigued())
		pDrunkard->GetFSM()->ChangeState(GoHomeAndSnore::Instance());
}


void GetDrunkerAndDrunker::Exit(Drunkard* pDrunkard)
{

}


bool GetDrunkerAndDrunker::OnMessage(Drunkard* pDrunkard, const Telegram& msg)
{
	switch (msg.Msg)
	{
	case Msg_Taunt:
		SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		cout << "\nMessage handled by " << GetNameOfEntity(pDrunkard->ID())
			<< " at time: " << Clock->GetCurrentTime();

		SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

		cout << "\n" << GetNameOfEntity(pDrunkard->ID())
			<< ": Hic the lion doesn' partner up with the cockcroach!";

		pDrunkard->GetFSM()->ChangeState(FightWithMiner::Instance());

		return true;

	}//end switch

	return false; //send message to global message handler
}


//------------------------------------------------------------------------FightWithMiner

FightWithMiner* FightWithMiner::Instance()
{
	static FightWithMiner instance;

	return &instance;
}


void FightWithMiner::Enter(Drunkard* pDrunkard)
{
	cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": Feel the bite of the coyotee!" << "";
}

void FightWithMiner::Execute(Drunkard* pDrunkard)
{
	cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "*Punch The miner in the nose*";

	pDrunkard->GetFSM()->ChangeState(GoHomeAndSnore::Instance());
}

void FightWithMiner::Exit(Drunkard* pDrunkard)
{
	cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "You stronga than i thought. Take this relic having belonged to a descendant virgin of a divinity prayed by a forgotten civilization!";
	cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "Wat am' I sayin'... Gota go home..";
}


bool FightWithMiner::OnMessage(Drunkard* pDrunkard, const Telegram& msg)
{
	//send msg to global message handler
	return false;
}




