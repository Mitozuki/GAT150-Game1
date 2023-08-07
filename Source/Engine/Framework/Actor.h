#pragma once
#include "Core/Core.h"
#include "Renderer/Model.h"
#include "Input/InputSystem.h"
#include "Components/Component.h"
#include <memory>

namespace kiko
{ 
	class Actor
	{
	public:
		Actor() = default;
		Actor(const kiko::Transform transform, std::shared_ptr<Model> model) :
			m_transform{ transform }
		{}
		Actor(const kiko::Transform& transform) :
			m_transform{ transform }
		{}


		virtual void Update(float dt);
		virtual void Draw(kiko::Renderer& renderer);

		void AddComponent(std::unique_ptr<Component> component);

		template<typename T>
		T* GetComponent();

		//float GetRadius() { return (m_model) ? m_model->GetRadius() * m_transform.scale : 0; }
		float GetRadius() { return (50.0f); } //? m_model->GetRadius() * m_transform.scale : -10000; }
		virtual void OnCollision(Actor* other) {}

		friend class Scene;
		class Scene* m_scene = nullptr;
		class Game* m_game;

		kiko::Transform m_transform;
		std::string m_tag;
		float m_lifespan = -1.0f;

	protected:
		std::vector<std::unique_ptr<Component>> m_components;

		bool m_destroyed = false;
	};
	template<typename T>
	inline T* Actor::GetComponent()
	{
		for (auto& component : m_components)
		{
			T* result = dynamic_cast<T*>(component.get());
			if (result) return result;
		}

		return nullptr;
	}
}