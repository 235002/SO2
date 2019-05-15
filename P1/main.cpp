#include <iostream>
#include <thread>
#include <cstdlib>
#include <ctime>
#include <array>
#include <iomanip>
#include <string>
#include <ncurses.h>
#include <time.h>
#include <unistd.h>
#include <mutex>
#define N 5 
using namespace std;

bool done = false;

class fork {
private:
	int		id;
	int		owner;
	bool		dirty;

public:

	fork() {
		id = 0;
		owner = 0;
		dirty = true;
	}

	fork(int const forkId, int const ownerId) :
		id(forkId), owner(ownerId), dirty(true)
	{}

	void request(int const ownerId) {
		while (owner != ownerId) {
			if (dirty) {
				dirty = false;
				owner = ownerId;
			}
		}
	}

	void done() {
		dirty = true;
	}
};

class philosopher {
private:
	int		id;
	fork&		left_fork;
	fork&		right_fork;
	thread		lifethread;

public:

	philosopher(int Id, fork &l, fork &r) :
		id(Id), left_fork(l), right_fork(r), lifethread(&philosopher::dine, this)
	{}

	~philosopher() {
		lifethread.join();
	}

	void eat() {
		left_fork.request(id);
		print(" takes left fork. ");
		right_fork.request(id);
		print(" takes right fork. ");

		print(" started eating. ");
		this_thread::sleep_for(chrono::milliseconds(rand() % 3500 + 2500));
		print(" finished eating. ");

		left_fork.done();							//Kiedy filozof skończył jeść pałeczki są zwalniane
		print(" puts left fork. ");
		right_fork.done();							//Zostają ustawione na brudne (wolne)
		print(" puts right fork. ");
	}

	void think() {
		print(" is thinking. ");
		this_thread::sleep_for(chrono::milliseconds(rand() % 2500 + 1500));
	}

	void dine() {
		do {
			eat();
			think(); 
		} while (!done);
		//lifethread.join();
	}

	void print(string const &text) {
		cout << "Philosopher " << id << ": " << text << endl;
	}
};

void dine() {
	array<fork, N> forks{
	   {
		  { 1, 1 },
		  { 2, 2 },
		  { 3, 3 },
		  { 4, 4 },
		  { 5, 5 },
	   }
	};

	array<philosopher, N> philosophers{
	   {
		  { 1, forks[0], forks[1] },		//Każdy z widelców jest podawany filozofowi o niższym ID
		  { 2, forks[1], forks[2] },
		  { 3, forks[2], forks[3] },
		  { 4, forks[3], forks[4] },
		  { 5, forks[4], forks[0] },
	   }
	};
	this_thread::sleep_for(chrono::seconds(10));
	done = true;
	cout << "HERE HERE HERE" << endl;
}

int main() {
	srand(time(NULL));
	cout << "Dining Philophers Problem" << endl;
	dine();
	return 0;
}

