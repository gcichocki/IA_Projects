#include "Drunkard.h"

bool Drunkard::HandleMessage(const Telegram& msg)
{
  return m_pStateMachine->HandleMessage(msg);
}


void Drunkard::Update()
{
  SetTextColor(FOREGROUND_BLUE| FOREGROUND_INTENSITY);

 // m_iThirst += 1;
  
  
  m_pStateMachine->Update();
}



void Drunkard::AddToCashCarried(const int val)
{
  m_iCashCarried += val;

  if (m_iCashCarried < 0) m_iCashCarried = 0;
}


bool Drunkard::Thirsty()const
{
  if (m_iThirst >= ThirstLvl){return true;}

  return false;
}


bool Drunkard::Drunk()const
{
	if (m_iDrunk > DrunkThreshold) { return true; }

	return false;
}

bool Drunkard::Fatigued()const
{
  if (m_iFatigue > TirednessMax)
  {
    return true;
  }

  return false;
}
