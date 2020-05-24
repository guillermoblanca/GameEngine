#pragma once
#include "gbpch.h"
#include "GB/Core.h"
namespace GB
{
	class EditorMenu
	{
	public:

		EditorMenu();
		void ImguiRender();

		void RemoveAction(/*action to remove*/);
		void AddAction(const std::string& name); //add func value

	private:
		std::string m_MenuName;
		std::map<std::string, int> m_MenuActions; //remove int to function 
	};



	
	class TabMenu
	{

	public:
		TabMenu(std::string name);
		//function to create all the actions that will appear in the tab menu
		virtual void Update() = 0;

		bool& IsActive() { return isActive; }
		const std::string& GetName() const { return m_name; }
	protected:

		void Render();
		bool isActive;
		std::string m_name;

	};
}	