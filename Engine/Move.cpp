#include "Move.h"

Move::Move(Line *start, Line *mid, Line *end)
{
	Warmup = start;
	Main = mid;
	Cooldown = end;
}

Move::~Move()
{
	delete Warmup;
	delete Main;
	delete Cooldown;

	delete Next;
}

Vector2 Move::f(int i)
{
	if (i < Timestamp) { return Vector2(); }
	else if (i < EwuTimestamp) { return Warmup->f((double)(EwuTimestamp-Timestamp) / (i - Timestamp)); }
	else if (i < EmnTimestamp) { return Warmup->f((double)(EmnTimestamp - EwuTimestamp) / (i - EwuTimestamp)); }
	else if (i < End) { return Warmup->f((double)(End - EmnTimestamp) / (i - EmnTimestamp)); }
	return Vector2();
}

void Move::SetTime(int to)
{
	Timestamp = (Timestamp == 0) ? to : Timestamp;
}

int Move::GetTotal(int count, bool GotLast)
{
	if (GotLast)
	{
		count++;

		if (Last != NULL)
		{
			return Last->GetTotal(count,true);
		}
		else
		{
			return count;
		}
	}
	else
	{
		if (Next != NULL)
		{
			return Next->GetTotal();
		}
		else
		{
			count++;
			return Last->GetTotal(count, true);
		}
	}
}