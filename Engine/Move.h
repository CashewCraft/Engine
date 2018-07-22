#ifndef MOVE_H
#define MOVE_H

#include "Vector2.h"
#include "Line.h"

class Move
{
	Line *Warmup;
	Line *Main;
	Line *Cooldown;

	//Relative timestamps (each relative to last)
	int EwuTimestamp = 0; //End of warm up timestamp
	int EmnTimestamp = 0; //End of main timestamp

	public:

	Move *Next;
	Move *Last;

	int Timestamp = 0; //Start of move timestamp (for outside reference only)
	int End = 0; //End of cooldown timestamp

	Move(Line *start, Line *mid, Line *end);
	~Move();

	void SetTime(int to);

	int GetTotal(int count = 0,bool GotLast = false);

	Vector2 f(int x);
};

#endif