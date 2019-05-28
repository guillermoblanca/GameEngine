#include "gbpch.h"
#include "GameObject.h"

namespace GB
{

	 void GameObject::OnUpdate()
	 {
		 for (auto comp : m_components)
		 {
			 comp->OnUpdate();
		 }
	 }
	 void GameObject::OnRender()
	 {
		 for (auto comp : m_components)
		 {
			 comp->OnRender();
		 }
	 }
}