#include "calendarexception.h"

CalendarException::~CalendarException()
{

}

bool verifJour(int j,int m,int a){
	if (j == 31
		&& (m == 2
			|| m == 4
			|| m == 6
			|| m == 9
			|| m == 11)) return false;
	if (j == 30 && m == 2) return false;
	if (j == 29 && m == 2 && !(a%4 == 0)) return false;
	if (j>31 || j<=0) return false;

	// TOUS LES CAS ONT ETE VERIFIES

	return true;
}

bool verifMois(int m){
	if (m>12 || m < 1) return false;

	return true;
}
bool verifHeure(int h){
	if (h > 23 || h < 0) return false;
	
	return true;
}
bool verifMinute(int m){
	if (m >= 60 || m < 0) return false;
	
	return true;
}
bool verifSeconde(int s){
	if (s >= 60 || s < 0) return false;
	
	return true;
}