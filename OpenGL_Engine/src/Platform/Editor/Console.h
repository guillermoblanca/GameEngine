#pragma once
#include "gbpch.h"
#include "GB\Core.h"
#include "GB\Layer.h"
#include "GB\Log.h"
#include "imgui.h"

namespace GB {

	class GBAPI Debug
	{
	public:
		void Log(const std::string message);
		void Error(const std::string message);
	};

	class GBAPI Console : Layer
	{
	public:
		virtual void OnAttach() override
		{
			m_Commands.push_back("HELP");
			m_Commands.push_back("CLEAR");
		}

		virtual void OnImguiRender() override
		{
			ImGui::Begin("Console");
			if (ImGui::Button("Clear"))
			{
				ClearLog();
			}
			ImGui::End();
		}

		void ClearLog()
		{
			for (int i = 0; i < m_Items.size(); i++)
				free(m_Items[i]);

			m_Items.clear();
			m_ScrollToBottom = true;
		}
		void AddLog(const char * fmt, ...)
		{
			//todo: add log 

		}
	private:
		char m_InputBuf[256];
		std::vector<char*> m_Items;
		bool m_ScrollToBottom;
		std::vector<char*> m_History;
		int m_HistoryPos;
		std::vector<const char*> m_Commands;
	};

}