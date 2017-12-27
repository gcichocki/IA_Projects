#ifndef DRUNKARD_OWNED_STATES_H
#define DRUNKARD_OWNED_STATES_H
//------------------------------------------------------------------------
//
//  Name:   DrunkardOwnedStates.h
//
//  Desc:   All the states that can be assigned to the Drunkard class.
//          Note that a global state has not been implemented.
//
//  Author: Noémy ARTIGOUHA - Damien MAVEYRAUD - Guilhem CICHOCKI - 2017 
//
//------------------------------------------------------------------------
#include "fsm/State.h"


class Drunkard;
struct Telegram;



//------------------------------------------------------------------------
//
//  The drunkard will walk in the town and sell chewing tobacco in the
//  street. If the Drunkard gets thristy, he will change his state to 
//  QuenchThirstDrunkard. If the drunkard is tired, he will go home and change his 
//  state to GoHomeAndSnore.
//------------------------------------------------------------------------
class SellChewingTobacco : public State<Drunkard>
{
private:

	SellChewingTobacco() {}

	//copy ctor and assignment should be private
	SellChewingTobacco(const SellChewingTobacco&);
	SellChewingTobacco& operator=(const SellChewingTobacco&);

public:

	//this is a singleton
	static SellChewingTobacco* Instance();

	virtual void Enter(Drunkard* drunkard);

	virtual void Execute(Drunkard* drunkard);

	virtual void Exit(Drunkard* drunkard);

	virtual bool OnMessage(Drunkard* agent, const Telegram& msg);
};



//------------------------------------------------------------------------
//
//  Drunkard will go home and sleep until his fatigue + alcohol level is decreased
//  sufficiently
//------------------------------------------------------------------------
class GoHomeAndSnore : public State<Drunkard>
{
private:
  
  GoHomeAndSnore(){}

  //copy ctor and assignment should be private
  GoHomeAndSnore(const GoHomeAndSnore&);
  GoHomeAndSnore& operator=(const GoHomeAndSnore&);
 
public:

  //this is a singleton
  static GoHomeAndSnore* Instance();

  virtual void Enter(Drunkard* drunkard);

  virtual void Execute(Drunkard* drunkard);

  virtual void Exit(Drunkard* drunkard);

  virtual bool OnMessage(Drunkard* agent, const Telegram& msg);
};


//------------------------------------------------------------------------
//
//  drunkard changes location to the saloon and keeps buying Whiskey until
//  his thirst is quenched. When satisfied another drink makes him drunk.
//------------------------------------------------------------------------
class QuenchThirstDrunkard : public State<Drunkard>
{
private:
  
  QuenchThirstDrunkard(){}

  //copy ctor and assignment should be private
  QuenchThirstDrunkard(const QuenchThirstDrunkard&);
  QuenchThirstDrunkard& operator=(const QuenchThirstDrunkard&);
 
public:

  //this is a singleton
  static QuenchThirstDrunkard* Instance();

  virtual void Enter(Drunkard* drunkard);

  virtual void Execute(Drunkard* drunkard);

  virtual void Exit(Drunkard* drunkard);

  virtual bool OnMessage(Drunkard* agent, const Telegram& msg);
};

//------------------------------------------------------------------------
//
//  drunkard gets drunker and drunker until his alcohol level is high enough
//  or until an altercation occurs
//------------------------------------------------------------------------
class GetDrunkerAndDrunker : public State<Drunkard>
{
private:

	GetDrunkerAndDrunker() {}

	//copy ctor and assignment should be private
	GetDrunkerAndDrunker(const GetDrunkerAndDrunker&);
	GetDrunkerAndDrunker& operator=(const GetDrunkerAndDrunker&);

public:

	//this is a singleton
	static GetDrunkerAndDrunker* Instance();

	virtual void Enter(Drunkard* drunkard);

	virtual void Execute(Drunkard* drunkard);

	virtual void Exit(Drunkard* drunkard);

	virtual bool OnMessage(Drunkard* agent, const Telegram& msg);
};

//------------------------------------------------------------------------
//
//  In this state the drunkard fight the miner and returns to the mine
//------------------------------------------------------------------------
class FightWithMiner : public State<Drunkard>
{
private:

	FightWithMiner() {}

	//copy ctor and assignment should be private
	FightWithMiner(const FightWithMiner&);
	FightWithMiner& operator=(const FightWithMiner&);

public:

	//this is a singleton
	static FightWithMiner* Instance();

	virtual void Enter(Drunkard* miner);

	virtual void Execute(Drunkard* miner);

	virtual void Exit(Drunkard* miner);

	virtual bool OnMessage(Drunkard* agent, const Telegram& msg);
};



#endif