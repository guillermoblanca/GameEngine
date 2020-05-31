#pragma once

namespace GB
{
	class UniqueID
	{
	protected:
		static unsigned int nextID;
	public:
		unsigned int id;
		UniqueID();
		UniqueID(const UniqueID& orig);
		UniqueID& operator=(const UniqueID& orig);
	};


}