#pragma once

namespace GB
{

	class RenderTab
	{
	public:

		bool Select(int index);
		void Update();
	private:

		int selectedIndex;
	};

}