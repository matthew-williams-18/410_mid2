//============================================================================
// Name        : 410_mid2.cpp
// Description : Please make this code threadsafe by identifying and protecting
//				 the smallest possible critical sections
//============================================================================

#include <iostream>
#include <thread>
using namespace std;

const int ONE_MINUTE=60000;
const int START_VALUE = 10000000;

int isource = START_VALUE;
int idest =0;

//global to control threads
bool bDoWork=true;

void report(int id, string s) {
	cout << "Thread " << id << ":" << s << endl;
}

void transfer(int id, int numbtimestotransfer){
	report(id,string("about to start"));

	for (int i=0; i<numbtimestotransfer; i++){

		//if time to stop then do
		if(!bDoWork){
			report(id,string("ASKED TO STOP"));
			break;
		}

		//take from isource and add to idest
		isource--;
		idest++;

		report(id,string("transfered 1"));
	}

	report(id,string("Exiting"));
}

int main() {
	int numbtotransfer = isource/2;

	thread t1(transfer,1,numbtotransfer);
	thread t2(transfer,2,numbtotransfer);

	//wait 1 minute so threads get going, then ask them to stop
	this_thread::sleep_for(chrono::milliseconds(ONE_MINUTE));
	bDoWork=false;

	t1.join();
	t2.join();

	if((isource+idest)!=START_VALUE)
		cout<<"Problems! Expected "<<START_VALUE<<" got "<<(isource+idest)<<endl;
	else
		cout<<"No worries!"<<endl;

	return 0;
}
