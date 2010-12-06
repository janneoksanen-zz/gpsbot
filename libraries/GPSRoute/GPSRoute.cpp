/* GPSRoute.cpp

	Author:  Janne Oksanen
	Email:   janne.oksanen@gmail.com
	Published under GPLv2.
	
	Known bugs: None. If you find any please let me know.		
*/
#include "GPSRoute.h"

GPSRoute::GPSRoute(){
  count = 0;
  first = NULL;
}

Waypoint* GPSRoute::getFirst(){
  return first;
}

void GPSRoute::addNode(Waypoint* wp){
  if (count == 0){
    first = wp;
  } else {
    temp = first;
    first = wp;
    first->setNext(temp);
  }
  count++;
}

int GPSRoute::size(){
  return count;
}
