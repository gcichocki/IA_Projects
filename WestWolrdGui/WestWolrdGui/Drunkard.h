#ifndef DRUNKARD_H
#define DRUNKARD_H
//------------------------------------------------------------------------
//
//  Name:   Miner.h
//
//  Desc:   A class defining a goldminer.
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include <string>
#include <cassert>
#include <iostream>

#include "BaseGameEntity.h"
#include "Locations.h"
#include "misc/ConsoleUtils.h"
#include "DrunkardOwnedStates.h"
#include "FSM/StateMachine.h"

template <class entity_type> class State; //pre-fixed with "template <class entity_type> " for vs8 compatibility

struct Telegram;

//above this value a drunkard is thirsty
const int ThirstLvl        = 2;
//above this value a drunkard is sleepy
const int TirednessMax = 5;
//above this value a drunkard is full drunk
const int DrunkThreshold = 5;



class Drunkard : public BaseGameEntity
{
private:

  //an instance of the state machine class
  StateMachine<Drunkard>*  m_pStateMachine;
  
  location_type         m_Location;

  //how much cash the Drunkard owns
  int                   m_iCashCarried;


  //the higher the value, the thirstier the drunkard
  int                   m_iThirst;

  //the higher the value, the drunker the drunkard
  int                   m_iDrunk;

  //the higher the value, the more tired the drunkard
  int                   m_iFatigue;

public:

	Drunkard(int id):m_Location(shack),
                          m_iCashCarried(0),
                          m_iThirst(0),
						  m_iDrunk(0),
                          m_iFatigue(0),
                          BaseGameEntity(id)
                               
  {
    //set up state machine
    m_pStateMachine = new StateMachine<Drunkard>(this);
    
    m_pStateMachine->SetCurrentState(GoHomeAndSnore::Instance());

    /* NOTE, A GLOBAL STATE HAS NOT BEEN IMPLEMENTED FOR THE MINER */
  }

  ~Drunkard(){delete m_pStateMachine;}

  //this must be implemented
  void Update();

  //so must this
  virtual bool  HandleMessage(const Telegram& msg);

  
  StateMachine<Drunkard>* GetFSM()const{return m_pStateMachine;}


  
  //-------------------------------------------------------------accessors
  location_type Location()const{return m_Location;}
  void          ChangeLocation(location_type loc){m_Location=loc;}
    
  int           CashCarried()const{return m_iCashCarried;}
  void          SetCashCarried(int val){m_iCashCarried = val;}
  void          AddToCashCarried(int val);

  bool          Fatigued()const;
  void          DecreaseFatigue(){m_iFatigue = 0;}
  void          IncreaseFatigue(){m_iFatigue += 1;}

  bool          Drunk()const;
  void          DecreaseDrunk() { m_iDrunk = 0; }
  void          IncreaseDrunk() { m_iDrunk += 1; }

  bool          Thirsty()const; 
  void          DecreaseThirst() { m_iThirst -= 1; }
  void          IncreaseThirst() { m_iThirst += 1; }
  //This guy has a loyalty card because of his latent alcoholism
  void          BuyAndDrinkAWhiskey() { m_iThirst == 0 ? NULL : m_iThirst -= 1; m_iCashCarried -= 1; }

};



#endif
