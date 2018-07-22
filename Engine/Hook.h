#pragma once

#include <SDL.h>
#include <iostream>

#include "Script.h"

class Hook
{
	public:

	bool UD;
	int K;
	bool R;

	Hook(bool UpDown, int Key, bool Repeat = false);
};

inline bool operator==(const Hook& lhs, const Hook& rhs)
{
	return (lhs.UD == rhs.UD) && (lhs.K == rhs.K) && (lhs.R == rhs.R);
}

namespace std {

	template <>
	struct hash<Hook>
	{
		std::size_t operator()(const Hook& k) const
		{
			using std::size_t;
			using std::hash;

			// Compute individual hash values for first,
			// second and third and combine them using XOR
			// and bit shifting:

			return ((hash<int>()(k.K)
				^ (hash<bool>()(k.UD) << 1)) >> 1)
				^ (hash<bool>()(k.R) << 1);
		}
	};

}