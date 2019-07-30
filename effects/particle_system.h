#pragma once

#include "particle.h"
#include <list>
#include "..\\core\pool_allocator.h"
#include "..\\external\core\include\core.h"

class ParticleSystem {
public:
	ParticleSystem(size_t size);
	~ParticleSystem();

	void Update(float dt);
	void Draw(Core::Graphics& graphics);

	void Create(const vector2& position, const vector2& velocity, const color& color_, float damping, float lifetime);

private:
	PoolAllocator<Particle>* m_particle_pool;
	std::list<Particle*> m_particles;
};