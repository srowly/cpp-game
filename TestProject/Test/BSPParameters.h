#pragma once
class BSPParameters
{
	int minNumRooms;
	int minRoomWidth;
	int minRoomHeight;
	CorridorType corridorType;

	BSPParameters(int minRooms, int minWidth, int minHeight, CorridorType type);
};

enum CorridorType
{
	Straight,
	Bent,
	ZigZag,
};