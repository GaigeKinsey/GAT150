#include "audiosystem.h"
#include "..\\core\assert.h"

bool AudioSystem::Startup()
{
	FMOD_RESULT result = FMOD::System_Create(&m_system);
	ASSERT_MSG(result == FMOD_OK, "Error creating FMOD system.");

	void* extradriverdata = nullptr;
	result = m_system->init(32, FMOD_INIT_NORMAL, extradriverdata);
	ASSERT_MSG(result == FMOD_OK, "Error initializing FMOD system.");

	return true;
}

void AudioSystem::Shutdown()
{
	for (auto& sound : m_sounds) {
		sound.second->release();
	}
	m_sounds.clear();

	FMOD_RESULT result = m_system->close();
	ASSERT_MSG(result == FMOD_OK, "Error closing FMOD system.");
	result = m_system->release();
	ASSERT_MSG(result == FMOD_OK, "Error releasing FMOD system.");
}

void AudioSystem::Update()
{
	FMOD_RESULT result = m_system->update();
	ASSERT_MSG(result == FMOD_OK, "Error updating FMOD system.");
}

void AudioSystem::AddSound(const std::string& key, const char* filename)
{
	if (m_sounds.find(key) == m_sounds.end()) {
		FMOD::Sound* sound = nullptr;
		FMOD_RESULT result = m_system->createSound(filename, FMOD_DEFAULT, 0, &sound);
		if (result == FMOD_OK) {
			m_sounds[key] = sound;
		}
	}
}

void AudioSystem::PlaySounds(const std::string& key, bool loop)
{
	auto iter = m_sounds.find(key);
	if (iter != m_sounds.end()) {
 		FMOD::Sound* sound = iter->second;
		FMOD_MODE mode = (loop) ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;
		sound->setMode(mode);
		FMOD::Channel* channel = nullptr;
		FMOD_RESULT result = m_system->playSound(sound, 0, false, &channel);
		ASSERT_MSG(result == FMOD_OK, "Error playing sound.");
	}
}

void AudioSystem::RemoveSound(const std::string& id)
{
	auto iter = m_sounds.find(id);
	if (iter != m_sounds.end()) {
		iter->second->release();
		m_sounds.erase(iter);
	}
}
