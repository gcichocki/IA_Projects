#include "WestWolrdGui.h"
#include <QApplication>
#include <QtWidgets>

#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <thread>
#include <mutex>
#include <iostream>
#include <process.h>
#include "Locations.h"
#include "Miner.h"
#include "Drunkard.h"
#include "MinersWife.h"
#include "EntityManager.h"
#include "MessageDispatcher.h"
#include "misc/ConsoleUtils.h"
#include "EntityNames.h"



std::ofstream os;
std::mutex messages_mutex;

void *main_window(int argc, char *argv[]) {
	QApplication app(argc, argv);
	messages_mutex.lock();
	QWidget fenetre;

	fenetre.setWindowTitle("WestWorld Altercation");
	fenetre.setStyleSheet("background-color: white;");
	fenetre.setFixedSize(400, 570);

	QGroupBox *groupbox = new QGroupBox("Etat de depart des agents:", &fenetre);
	QVBoxLayout *vbox = new QVBoxLayout;
	QHBoxLayout *hbox = new QHBoxLayout;
	QHBoxLayout *hbox2 = new QHBoxLayout;
	QHBoxLayout *hbox3 = new QHBoxLayout;


	QLabel *labelMiner = new QLabel("Miner Bob : EnterMineAndDigForNugget", &fenetre);
	QLabel *labelWife = new QLabel("Elsa : VisitBathroom", &fenetre);
	QLabel *labelDrunkard = new QLabel("Ross the Drunkard : SellChewingTobacco", &fenetre);

	QLabel *img_miner = new QLabel(&fenetre);
	img_miner->setPixmap(QPixmap("Resources/miner.png"));
	hbox->addWidget(img_miner);
	hbox->addWidget(labelMiner);

	QLabel *img_wife = new QLabel(&fenetre);
	img_wife->setPixmap(QPixmap("Resources/wife.png"));
	hbox2->addWidget(img_wife);
	hbox2->addWidget(labelWife);

	QLabel *img_drunkard = new QLabel(&fenetre);
	img_drunkard->setPixmap(QPixmap("Resources/drunkard.png"));
	hbox3->addWidget(img_drunkard);
	hbox3->addWidget(labelDrunkard);
	
	vbox->addLayout(hbox);
	vbox->addLayout(hbox2);
	vbox->addLayout(hbox3);
	groupbox->setLayout(vbox);
	groupbox->move(5, 5);
	fenetre.show();
	messages_mutex.unlock();

	return (void*)app.exec();
}


//This function will be called from a thread
void *call_from_thread(BaseGameEntity *entity) {
	for (int i = 0; i<30; ++i)
	{
		messages_mutex.lock();
		entity->Update();
		//dispatch any delayed messages
		Dispatch->DispatchDelayedMessages();
		messages_mutex.unlock();
		Sleep(1000);
	}
	return 0;
}


int main(int argc, char *argv[])
{
	//define this to send output to a text file (see locations.h)
#ifdef TEXTOUTPUT
	os.open("output.txt");
#endif
	//Create a thread for the window
	std::thread thread_Window(main_window, argc, argv);

	if (AllocConsole())
	{
		freopen("CONOUT$", "wt", stdout);
		freopen("CONIN$", "rt", stdin);
		SetConsoleTitle(L"Debug Console");
		std::ios::sync_with_stdio(1);
	}


	//seed random number generator
	srand((unsigned)time(NULL));

	//create a miner
	Miner* Bob = new Miner(ent_Miner_Bob);

	//create his wife
	MinersWife* Elsa = new MinersWife(ent_Elsa);

	//create the drunkard
	Drunkard* Ross = new Drunkard(ent_Drunkard_Ross);

	//register them with the entity manager
	EntityMgr->RegisterEntity(Bob);
	EntityMgr->RegisterEntity(Elsa);
	EntityMgr->RegisterEntity(Ross);

	//Launch a thread
	std::thread thread_Bob(call_from_thread, Bob);
	std::thread thread_Elsa(call_from_thread, Elsa);
	std::thread thread_Ross(call_from_thread, Ross);

	//Join the thread with the main thread
	thread_Bob.join();
	thread_Elsa.join();
	thread_Ross.join();
	thread_Window.join();


	//tidy up
	delete Bob;
	delete Elsa;
	delete Ross;

	//wait for a keypress before exiting
	PressAnyKeyToContinue();

	

	return 0;
}






