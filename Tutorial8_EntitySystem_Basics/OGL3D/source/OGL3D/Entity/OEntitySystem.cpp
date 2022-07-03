/*MIT License

C++ OpenGL 3D Game Tutorial Series (https://github.com/PardCode/OpenGL-3D-Game-Tutorial-Series)

Copyright (c) 2021-2022, PardCode

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/

#include <OGL3D/Entity/OEntitySystem.h>
#include <OGL3D/Entity/OEntity.h>

OEntitySystem::OEntitySystem()
{
}

OEntitySystem::~OEntitySystem()
{
}

bool OEntitySystem::createEntityInternal(OEntity* entity, size_t id)
{
	auto ptr = std::unique_ptr<OEntity>(entity);
	m_entities[id].emplace(entity, std::move(ptr));

	entity->m_id = id;
	entity->m_entitySystem = this;

	entity->onCreate();

	return true;
}

void OEntitySystem::removeEntity(OEntity* entity)
{
	m_entitiesToDestroy.emplace(entity);
}

void OEntitySystem::update(f32 deltaTime)
{
	for (auto e : m_entitiesToDestroy)
	{
		m_entities[e->m_id].erase(e);
	}
	m_entitiesToDestroy.clear();


	for (auto&& [id, entities] : m_entities)
	{
		for (auto&& [ptr, entity] : entities)
		{
			entity->onUpdate(deltaTime);
		}
	}



}
