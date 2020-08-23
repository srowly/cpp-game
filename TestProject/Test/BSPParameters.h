
enum CorridorType
{
	Straight,
	Bent,
	ZigZag,
};

#pragma once
struct BSPParameters
{
public:
	int minNumRooms;
	int minRoomWidth;
	int minRoomHeight;
	CorridorType corridorType;
};
