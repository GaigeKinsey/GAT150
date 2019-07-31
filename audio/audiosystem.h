#pragma once
#include "..\\engine\system.h"
#include "..\\external\fmod\api\core\inc\fmod.hpp"

#include <string>
#include <map>

class AudioSystem : public System {
public:
	AudioSystem(Engine* engine) : System(engine) {}
public:
	bool Startup();
	void Shutdown();

	void Update();

	void AddSound(const std::string& key, const char* filename);
	void PlaySounds(const std::string& key, bool loop = false);
	void RemoveSound(const std::string& id);

private:
	FMOD::System* m_system = nullptr;
	std::map<std::string, FMOD::Sound*> m_sounds;
};