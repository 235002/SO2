#include <iostream>
#include <thread>
#include <ncurses.h>
#include <time.h>
#include <unistd.h>
#include <mutex>

using namespace std;
mutex mtx;

const int N = 5;
bool forkEnable[N];
int status[N];
int numOfBites[N];
int eatStatus[N];
int numOfThougths[N];
int thinkStatus[N];
bool endProgram = false;

void pickUp(int id){
	forkEnable[id]=false;
	forkEnable[((2*N + id - 1)%N)]=false;
}

void putDown(int id){
	forkEnable[id]=true;
	forkEnable[((2*N + id - 1)%N)]=true;
}

void showStatus(){
	mtx.lock();
	mvprintw(0,0,"Philosophers(0->thinking, 1->eating): ");
	mvprintw(1,0,"Forks(1->able, 0->enable): ");
	mvprintw(4,0,"Philosoph ID |");
	mvprintw(4,15,"Status |");
	mvprintw(4,24,"Number of bites |");
	mvprintw(4,41,"Per. of eating |");
	mvprintw(4,58,"Numeber of thoughts |");
	mvprintw(4,80,"Per. of thiniknig |");
	for (int i=0; i<N; i++)
	{
		mvprintw(0,i*5+39,"%d",status[i]);
		mvprintw(1,i*5+39,"%d",forkEnable[i]);
		mvprintw(i+5,5,"%d",i);
		if(status[i] == 1) {
			mvprintw(i+5,15,"eating");
		} else if(status[i] == 0) {
			mvprintw(i+5,15,"thinking");
		}
		mvprintw(i+5,32,"%d",numOfBites[i]);
		mvprintw(i+5,49,"%d",eatStatus[i]);
		mvprintw(i+5,69,"%d",numOfThougths[i]);
		mvprintw(i+5,85,"%d",thinkStatus[i]);
		refresh();
	}
	mtx.unlock();
}

void startThread(int id) {
	while(!endProgram) {
		if(getch() == 27) {
			endProgram = true;
			break;
		}
		mtx.lock();
		if((forkEnable[id] && forkEnable[(((2*N) + id - 1)%N)]) && 
		(numOfBites[id] <= numOfBites[(2*N + id - 1)%N]) && 
		(numOfBites[id] <= numOfBites[(2*N + id + 1)%N])) {
			pickUp(id);
			status[id] = 1;	
			numOfBites[id]++;	
		}
		mtx.unlock();
		eatStatus[id] = 0;
		for(int i=1; i<=10; i++) {
			if(status[id] == 1) {
				this_thread::sleep_for(chrono::milliseconds(rand() % 200 + 333));
				eatStatus[id] += 10;
				showStatus();
			} else if(status[id] == 0) {
				break;
			}
		}
		eatStatus[id] = 0;
		clear();
		showStatus();

		mtx.lock();
		if(status[id] == 1) {
			putDown(id);
			status[id] = 0;		
		} else if(status[id] == 0) {
			numOfThougths[id]++;
		}
		mtx.unlock();

		thinkStatus[id] = 0;
		for(int i=1; i<=10; i++) {
			this_thread::sleep_for(chrono::milliseconds(rand() % 300 + 444));
			thinkStatus[id] += 10;
			showStatus();
		}
		thinkStatus[id] = 0;
		clear();
		showStatus();	
	}	
}
int main(){
	srand(time(NULL));
	for(int i=0;i<N;i++)
	{
		forkEnable[i]=true;
		status[i]=0;
	}
	thread t[N];
	initscr();
	nodelay(stdscr,TRUE);
	refresh();
	for (int i = 0; i < N; i++)
	{
		t[i] = thread(startThread, i);
	}
	for (int i = 0; i < N; i++)
	{
		t[i].join();
	}
	endwin();
	return 0;
}
