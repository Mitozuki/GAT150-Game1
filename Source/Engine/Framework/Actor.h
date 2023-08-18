#pragma once
#include "Object.h"
#include "Core/Core.h"
#include "Renderer/Model.h"
#include "Input/InputSystem.h"
#include "Components/Component.h"
#include <memory>

namespace kiko
{ 
	class Actor : public Object
	{
	public:
		CLASS_DECLARATION(Actor)

		Actor() = default;
		Actor(const kiko::Transform& transform) :
			transform{ transform }
		{}

		Actor(const Actor& other);

		virtual bool Initialize() override;
		virtual void OnDestroy() override;


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

	public:
		kiko::Transform transform;
		std::string tag;
		float lifespan = -1.0f;
		bool persistent = false;
		bool destroyed = false;
		bool prototype = false;

	protected:
		std::vector<std::unique_ptr<Component>> components;

	};
	template<typename T>
	inline T* Actor::GetComponent()
	{
		for (auto& component : components)
		{
			T* result = dynamic_cast<T*>(component.get());
			if (result) return result;
		}

		return nullptr;
	}
}