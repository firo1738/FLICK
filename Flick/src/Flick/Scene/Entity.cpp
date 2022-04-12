#include "fipch.h"
#include "Entity.h"

namespace Flick {

	Entity::Entity(entt::entity handle, Scene* scene)
		:m_EntityHandle(handle), m_Scene(scene) 
	{}
}