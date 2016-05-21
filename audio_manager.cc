/**
 *
 * @project Arkanoid
 * @brief AudioManager Class
 * @author Toni Marquez
 *
 **/

#include "audio_manager.h"

#if !defined(WITH_WASAPI)

namespace SoLoud {
	result wasapi_init(Soloud *aSoloud,
                     unsigned int aFlags,
                     unsigned int aSamplerate,
                     unsigned int aBuffer){

		return NOT_IMPLEMENTED;
	}
};

#endif

/// singleton
AudioManager& AudioManager::instance() {

  static AudioManager* singleton = new AudioManager();
  return *singleton;
}

/// constructor
AudioManager::AudioManager() {

  soloud_.init();
	fx_[0].load("data/assets/sounds/start.wav");
	fx_[1].load("data/assets/sounds/bounce.wav");
	fx_[2].load("data/assets/sounds/powerup.wav");
	fx_[3].load("data/assets/sounds/die.wav");
	fx_[4].load("data/assets/sounds/break1.wav");
	fx_[5].load("data/assets/sounds/break2.wav");
	fx_[6].load("data/assets/sounds/break3.wav");

	//music_[0].load("data/assets/sounds/die.wav");
}

/**
 * @brief play a sound sample with a specified volume
 * @param const unsigned short int index, const float volume
 * @return void
 **/
void AudioManager::playFX(const unsigned short int index, const float volume) {

  int sample = soloud_.play(fx_[index]);
  soloud_.setVolume(sample, volume);
}

/**
 * @brief play a music sample with a specified volume
 * @param const unsigned short int index, const float volume
 * @return void
 **/
void AudioManager::playMusic(const unsigned short int index,
														 const float volume) {

  int loop = soloud_.play(music_[index]);
  soloud_.setLooping(loop, 1);
	soloud_.setVolume(loop, volume);
}

/// destructor
AudioManager::~AudioManager() {

  soloud_.deinit();
}
