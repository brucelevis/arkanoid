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
  fx_[0].load("data/assets/sounds/sample.wav");

  /*
  // use this to play a sound
  AudioManager::instance().soloud_.play(AudioManager::instance().fx_[0]);

  // use this to play a sound with a specified volume
  int turbo = AudioManager::instance().soloud_.play(AudioManager::instance().fx_[0]);
  AudioManager::instance().soloud_.setVolume(turbo, 0.025f);
  */
}

/// copy constructor
AudioManager::AudioManager(const AudioManager& copy) {

  soloud_ = copy.soloud_;
  for (unsigned short int i = 0; i < (sizeof(fx_[0]) / sizeof(fx_)); i++){
    fx_[i] = copy.fx_[i];
  }
}

/// destructor
AudioManager::~AudioManager() {

  soloud_.deinit();
}
