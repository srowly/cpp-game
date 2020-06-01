
enum CorridorType
{
	Straight,
	Bent,
	ZigZag,
};

#pragma once
class BSPParameters
{
public:
	int minNumRooms;
	int minRoomWidth;
	int minRoomHeight;
	CorridorType corridorType;

	BSPParameters(int minRooms, int minWidth, int minHeight, CorridorType type);
};
