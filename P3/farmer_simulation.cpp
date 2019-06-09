#include <iostream>
#include <thread>
#include <ncurses.h>
#include <time.h>
#include <unistd.h>
#include <mutex>
#include <condition_variable>

using namespace std;
mutex mtx;
condition_variable cv_field, cv_factoryGrain, cv_cutCereal;

const int numFarmer = 4;
const int numDriver = 2;
const int numProducer = 12;
const int numMiller = 4;
const int numDistiller = 4;
const int numForager = 4;
const int numCustomer = 4;

int fieldStatus = 50;
int cutCereals = 10;
int factoryGrainStatus = 0;

int grainStatus = 0;
int strawStatus = 0;

int counterFarmer[numFarmer];

int flourStatus;
int alcoholStatus;
int forageStatus;

int flourStatusCustomer[numCustomer];
int alcoholStatusCustomer[numCustomer];
int forageStatusCustomer[numCustomer];
int cashCustomer[numCustomer];

int cash;
int growthRate = 1;

void showStatus() {
	mtx.lock();
	
	for (int i=0; i<150; i++) {
		mvprintw(12,25+i,"-");
	}
	for (int i=0; i<45; i++) {
		mvprintw(13+i,25,"|");
	}
	for (int i=0; i<45; i++) {
		mvprintw(12+i,70,"|");
	}
	
	mvprintw(1,4,"Stan pola: %d",fieldStatus);
	mvprintw(2,27,"Ilosc scietego zboza: %d",cutCereals);
	
	mvprintw(1,60,"Fabryka");
	mvprintw(2,60,"Ilosc zboza w fabryce: %d",factoryGrainStatus);
	mvprintw(3,60,"Ziarno: %d",grainStatus);
	mvprintw(4,60,"Sloma: %d",strawStatus);
	
	mvprintw(13,75,"Produkcja ");
	mvprintw(15,75,"Produkcja maki ");
	mvprintw(21,75,"Produkcja spirytusu ");
	mvprintw(27,75,"Produkcja paszy");
	
	mvprintw(13,40,"Sprzedane produkty");
	mvprintw(15,35,"Maka Spirytus Pasza Pieniadze");
	
	refresh();
	mtx.unlock();
}	
   
void showStatusFactoryGrain() {
	mtx.lock();
	mvprintw(2,60,"Ilosc zboza w fabryce : ");
	mvprintw(2,60,"Ilosc zboza w fabryce :  %d",factoryGrainStatus);
	refresh();
	mtx.unlock();
}

void showStatusField() {
	mtx.lock();
	int counter = fieldStatus;
	counter *= 2;
	mvprintw(1,4,"Stan pola: ");
	mvprintw(1,4,"Stan pola:  %d",fieldStatus);
	for(int i=0;  i<10; i++) {
		for(int j=0;  j<20; j++) {
			if(counter > 0) {
				attron(COLOR_PAIR(3));
				mvprintw(i+2,j+2," ");
				attroff(COLOR_PAIR(3));
				counter--;
			} else {
				attron(COLOR_PAIR(2));
				mvprintw(i+2,j+2," ");
				attroff(COLOR_PAIR(2));
				counter--;
			}
		}
	}
	refresh();
	mtx.unlock();	
}

void showStatusFarmer(int tID, bool work) {
	mtx.lock();
	if (work) {
		attron(COLOR_PAIR(2));
		mvprintw(13+tID,2,"Rolnik %d : %d",tID,counterFarmer[tID]);
		attroff(COLOR_PAIR(2));
	} else {
		mvprintw(13+tID,2,"Rolnik %d : %d",tID,counterFarmer[tID]);
	}
	refresh();
	mtx.unlock();
}

void showStatusCutCereals() {
	mtx.lock();
	mvprintw(2,27,"Ilosc scietego zboza: ");
	mvprintw(2,27,"Ilosc scietego zboza: %d", cutCereals);
	
	refresh();
	mtx.unlock();
}

void showStatusFactory() {
	mtx.lock();
	mvprintw(3,60,"Ziarno: ");
	mvprintw(3,60,"Ziarno: %d",grainStatus);
	
	mvprintw(4,60,"Sloma: ");
	mvprintw(4,60,"Sloma: %d",strawStatus);
	
	refresh();
	mtx.unlock();
}

void showStatusDriver(int tID, int position) {
	mtx.lock();
	if(position == 0) {
		mvprintw(3+tID,27,"Kierowca %d", tID);
		refresh();
	} else {
		mvprintw(3+tID,27,"Kierowca %d jedzie do fabryki", tID);
		refresh();
		usleep(200000);
	}
	mtx.unlock();
} 

void showStatusDriver(int tID) {
	mtx.lock();
	mvprintw(3+tID,27,"Kierowca %d", tID);
	refresh();
	usleep(200000);
	mtx.unlock();
} 

void showStatusMiller(int tID, int position) {
	mtx.lock();
	mvprintw(16+tID,125,"Mlynarz %d: ",tID);
	for (int i=0; i<10; i++) {
		mvprintw(16+tID,136+i," ");
	}
	for (int i=0; i<position; i++) {
		attron(COLOR_PAIR(1));
		mvprintw(16+tID,136+i," ");
		attroff(COLOR_PAIR(1));
	}
	refresh();
	mtx.unlock();
}

void showStatusDistiller(int tID, int position) {
	mtx.lock();
	mvprintw(22+tID,125,"Gorzelnik %d: ",tID);
	for (int i=0; i<10; i++) {
		mvprintw(22+tID,136+i," ");
	}
	for (int i=0; i<position; i++) {
		attron(COLOR_PAIR(3));
		mvprintw(22+tID,136+i," ");
		attroff(COLOR_PAIR(3));
	}
	refresh();
	mtx.unlock();
}

void showStatusForager(int tID, int position) {
	mtx.lock();
	mvprintw(28+tID,125,"Paszarz %d: ",tID);
	for (int i=0; i<10; i++) {
		mvprintw(28+tID,136+i," ");
	}
	for (int i=0; i<position; i++) {
		attron(COLOR_PAIR(4));
		mvprintw(28+tID,136+i," ");
		attroff(COLOR_PAIR(4));
	}
	refresh();
	mtx.unlock();
}

void showStatusFlour() {
	mtx.lock();
	int counter = flourStatus;
	mvprintw(15,95,"Maka : ");
	mvprintw(15,95,"Maka : %d",flourStatus);
	for (int i=0; i<5; i++) {
		for (int j=0; j<10; j++) {
			if(counter > 0) {
				attron(COLOR_PAIR(1));
				mvprintw(i+16,j+95,"M");
				attroff(COLOR_PAIR(1));
				counter--;
			} else {
				mvprintw(i+16,j+95," ");
			}
		}
	}
	refresh();
	mtx.unlock();
}

void showStatusAlcohol() {
	mtx.lock();
	int counter = alcoholStatus;
	mvprintw(21,95,"Spirytus : ");
	mvprintw(21,95,"Spirytus : %d",alcoholStatus);
	for (int i=0; i<5; i++) {
		for (int j=0; j<10; j++) {
			if(counter > 0) {
				attron(COLOR_PAIR(3));
				mvprintw(i+22,j+95,"S");
				attroff(COLOR_PAIR(3));
				counter--;
			} else {
				mvprintw(i+22,j+95," ");
			}
		}
	}
	refresh();
	mtx.unlock();
}

void showStatusForage() {
	mtx.lock();
	int counter = forageStatus;
	mvprintw(27,95,"Pasza : ");
	mvprintw(27,95,"Pasza : %d",forageStatus);
	for (int i=0; i<5; i++) {
		for (int j=0; j<10; j++) {
			if(counter > 0) {
				attron(COLOR_PAIR(4));
				mvprintw(i+28,j+95,"P");
				attroff(COLOR_PAIR(4));
				counter--;
			} else {
				mvprintw(i+28,j+95," ");
			}
		}
	}
	refresh();
	mtx.unlock();
}

void showStatusCustomer(int tID) {
	mtx.lock();
	mvprintw(17+tID,28,"Klient %d: %d    %d       %d     %d",
		tID,flourStatusCustomer[tID],alcoholStatusCustomer[tID],forageStatusCustomer[tID], cashCustomer[tID]);
	refresh();
	mtx.unlock();
}

void showStatusCash() {
	mtx.lock();
	int c = 0;
	for (int i=0; i<numCustomer; i++) {
		c += cashCustomer[i];
	}
	mvprintw(29,28,"Pieniadze: ");
	mvprintw(29,28,"Pieniadze: %d",c);
	mvprintw(30,28,"Wsploczynnik wzrostu: ");
	mvprintw(30,28,"Wsploczynnik wzrostu: %d",growthRate);
	refresh();
	mtx.unlock();
}

//------------------------------------------------------------------------------------------------------------------------

void startTreadField() {
	while (1) {
		showStatusField();
		while (fieldStatus <= 100) {
			usleep(rand()%1000000 + (int)(1000000/growthRate));
			unique_lock<mutex> lck(mtx);
			fieldStatus++;
			lck.unlock();
			cv_field.notify_all();
			showStatusField();
		}
	}
}

void startTreadFarmer(int tID) {
	while (1) {
		bool work = false;
		showStatusFarmer(tID,work);
		usleep(1000000);
		unique_lock<mutex> lck(mtx);
		if (fieldStatus < 25) {
			while (fieldStatus < 50) cv_field.wait(lck);
		}
		lck.unlock();
		
		mtx.lock();
		if ((counterFarmer[tID] <= counterFarmer[(2*numFarmer+tID-1)%numFarmer]) && 
		   (counterFarmer[tID] <= counterFarmer[(2*numFarmer+tID+1)%numFarmer])) {
			if (fieldStatus > 0 && cutCereals < 100) {
				counterFarmer[tID]++;
				fieldStatus--;
				cutCereals++;
				work = true;
			}
		}
		mtx.unlock();
		
		cv_cutCereal.notify_one();
		showStatusField();
		showStatusCutCereals();
		
		if (work) {
			for (int i=0; i<10; i++) {
				showStatusFarmer(tID,work);
				usleep(rand()%100000+100000);
			}
		}
	}
}

void startTreadDriver(int tID) {
	while (1) {
		showStatusDriver(tID, 0);
		unique_lock<mutex> lck(mtx);
		while (cutCereals < 20) cv_cutCereal.wait(lck);
		cutCereals -= 20;
		lck.unlock();
		
		showStatusCutCereals();
		showStatusDriver(tID,1);
		usleep(500000);
		
		lck.lock();
		while (factoryGrainStatus > 80) cv_factoryGrain.wait(lck);
		factoryGrainStatus += 20;
		lck.unlock();
		showStatusFactoryGrain();
		showStatusDriver(tID);
	}
}

void startTreadFactory(int tID) {
	bool make;
	while (1) {
		make = false;
		mtx.lock();
		if (factoryGrainStatus > 0 && grainStatus <= 150 && strawStatus <= 100) {
			factoryGrainStatus--;
			make = true ;
		}
		mtx.unlock();
		cv_factoryGrain.notify_one();
		showStatusFactoryGrain();
		
		if (make) {
			for (int i=0; i<10; i++) {
				usleep(rand()%1000000+1000000);
				grainStatus++;
				showStatusFactory();
				if (i%2 == 1) {
					usleep(rand()%1000000+1000000);
					strawStatus++;
					showStatusFactory();
				}
			}
		}
		if (cash >= 100 && growthRate < 100) {
			cash -= 100;
			growthRate += 10;
			showStatusCash();
		}
		if (growthRate > 50) growthRate = 1;
	}
}

void startTreadMiller(int tID) {
	bool make;
	while (1) {
		make = false;
		mtx.lock();
		if ((grainStatus >= 10) && (flourStatus <= alcoholStatus) && (flourStatus <= forageStatus)){
			grainStatus -= 10;
			make = true;
		}
		mtx.unlock();
		showStatusFactory();
		mtx.lock();
		if (make) {
			for (int i=0; i<=10; i++) {
				usleep(rand()%10000+10000);
				showStatusMiller(tID,1);
			}
			flourStatus++;
			showStatusFlour();
		}
		mtx.unlock();
	}
}

void startTreadDistiller(int tID) {
	bool make;
	while (1) {
		make = false;
		mtx.lock();
		if ((grainStatus >= 20) && (alcoholStatus <= flourStatus) && (alcoholStatus <= forageStatus)){
			grainStatus -= 20;
			make = true;
		}
		mtx.unlock();
		showStatusFactory();
		mtx.lock();
		if (make) {
			for (int i=0; i<=10; i++) {
				usleep(rand()%10000+10000);
				showStatusDistiller(tID,1);
			}
			alcoholStatus++;
			showStatusAlcohol();
		}
		mtx.unlock();
	}
}

void startTreadForager(int tID) {
	bool make;
	while (1) {
		make = false;
		mtx.lock();
		if ((grainStatus >= 10 && strawStatus >= 15) && (forageStatus <= flourStatus) && (forageStatus <= alcoholStatus)){
			grainStatus -= 10;
			strawStatus -= 15;
			make = true;
		}
		mtx.unlock();
		showStatusFactory();
		mtx.lock();
		if (make) {
			for (int i=0; i<=10; i++) {
				usleep(rand()%10000+10000);
				showStatusForager(tID,1);
			}
			forageStatus++;
			showStatusForage();
		}
		mtx.unlock();
	}
}

void startTreadCustomer(int tID) {
	while (1) {
		int choice = rand()%3+1;
		mtx.lock();
		switch(choice) {
			case 1: 
				if (flourStatus > 0) {
					flourStatus--;
					cash += 10;
					flourStatusCustomer[tID]++;
					cashCustomer[tID] += 10;
				}
				break;
			case 2: 
				if (alcoholStatus > 0) {
					alcoholStatus--;
					cash += 10;
					alcoholStatusCustomer[tID]++;
					cashCustomer[tID] += 10;
				}
				break;
			case 3: 
				if (forageStatus> 0) {
					forageStatus--;
					cash += 10;
					forageStatusCustomer[tID]++;
					cashCustomer[tID] += 10;
				}
				break;
			default: break;
		}
		mtx.unlock();
		showStatusFlour();
		showStatusAlcohol();
		showStatusForage();
		showStatusCustomer(tID);
		showStatusCash();
		usleep(5000000);
	}
}

//--------------------------------------------------------------------------------------------------------------------------------

int main(){
	initscr();
	nodelay(stdscr,TRUE);
	refresh();
	srand(time(NULL));
	clear();
	start_color();
	init_pair(1,COLOR_BLACK,COLOR_RED);
	init_pair(2,COLOR_BLACK,COLOR_YELLOW);
	init_pair(3,COLOR_BLACK,COLOR_GREEN);
	init_pair(4,COLOR_BLACK,COLOR_BLUE);
	init_pair(5,COLOR_BLACK,COLOR_MAGENTA);
	init_pair(6,COLOR_BLACK,COLOR_WHITE);
	init_pair(7,COLOR_BLACK,COLOR_CYAN);
	curs_set(0);

//--------------deklaracja watkow--------------
	thread field;
	thread farmer[numFarmer];
	thread driver[numDriver];
	thread producer[numProducer];
	thread miller[numMiller];
	thread distiller[numDistiller];
	thread forager[numForager];
	thread customer[numCustomer];
	
	showStatus();

//--------------uruchamianie watkow------------
	field = thread(startTreadField);
	for (int i=0; i<numFarmer; i++) {
		farmer[i] = thread(startTreadFarmer,i);
		counterFarmer[i] = 0;
	}
	for (int i=0; i<numDriver; i++) {
		driver[i] = thread(startTreadDriver,i);
	}
	for (int i=0; i<numProducer; i++) {
		producer[i] = thread(startTreadFactory,i);
	}
	for (int i=0; i<numMiller; i++) {
		miller[i] = thread(startTreadMiller,i);
	}
	for (int i=0; i<numDistiller; i++) {
		distiller[i] = thread(startTreadDistiller,i);
	}
	for (int i=0; i<numForager; i++) {
		forager[i] = thread(startTreadForager,i);
	}
	for (int i=0; i<numCustomer; i++) {
		customer[i] = thread(startTreadCustomer,i);
	}
//--------------join watkow------------
	field.join();
	for (int i=0; i<numFarmer; i++) {
		farmer[i].join();
	}
	for (int i=0; i<numDriver; i++) {
		driver[i].join();
	}
	for (int i=0; i<numProducer; i++) {
		producer[i].join();
	}
	for (int i=0; i<numMiller; i++) {
		miller[i].join();
	}
	for (int i=0; i<numDistiller; i++) {
		distiller[i].join();
	}
	for (int i=0; i<numForager; i++) {
		forager[i].join();
	}
	for (int i=0; i<numCustomer; i++) {
		customer[i].join();
	}
	
	endwin();
	return 0;
}


