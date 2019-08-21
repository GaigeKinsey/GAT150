#include "particle_system.h"
#include "..\\core\assert.h"
#include "..\\engine\engine.h"
#include "..\\renderer\renderer.h"
#include "..\\renderer\texture.h"

ParticleSystem::ParticleSystem(Engine* engine) : System(engine)
{
	m_particle_pool = new PoolAllocator<Particle>(1000);
}

ParticleSystem::~ParticleSystem()
{
	delete m_particle_pool;
}

void ParticleSystem::Update()
{
	for (Particle* particle : m_particles)
	{
		particle->lifetime = particle->lifetime - g_timer.dt();
		particle->active = (particle->lifetime > 0.0f);

		if (particle->active)
		{
			particle->position = particle->position + (particle->velocity * g_timer.dt());
			particle->velocity = particle->velocity * particle->damping;
		}
	}

	auto iter = m_particles.begin();
	while (iter != m_particles.end())
	{
		if ((*iter)->active == false)
		{
			m_particle_pool->Free(*iter);
			iter = m_particles.erase(iter);
		}
		else
		{
			iter++;
		}
	}
}

void ParticleSystem::Draw()
{
	for (Particle* particle : m_particles)
	{
		Texture* texture = GetEngine()->GetResourceManager()->Get<Texture>(particle->texture_name);
		texture->Draw(particle->position, 0.0f, particle->scale, vector2(0.5f, 0.5f));

		//Renderer::Instance()->Draw(graphics, particle->position, particle->prev_position);
	}
}

void ParticleSystem::Create(const Name& texture_name, const vector2& position, const vector2& velocity, const vector2& scale, float damping, float lifetime)
{
	Particle* particle = m_particle_pool->Get();
	if (particle)
	{
		particle->texture_name = texture_name;
		particle->active = true;
		particle->lifetime = lifetime;

		particle->position = position;
		particle->velocity = velocity;
		particle->scale = scale;
		particle->damping = damping;

		m_particles.push_back(particle);
	}
}

