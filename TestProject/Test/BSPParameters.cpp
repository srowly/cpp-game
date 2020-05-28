#include "BSPParameters.h"

BSPParameters::BSPParameters(int minRooms, int minWidth, int minHeight, CorridorType type)
{
	minNumRooms = minRooms;
	minRoomWidth = minWidth;
	minRoomHeight = minHeight;
	corridorType = type;
}