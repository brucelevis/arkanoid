/**
 *
 * @project Arkanoid
 * @brief AudioManager Header
 * @author Toni Marquez
 *
 **/

#ifndef __AUDIOMANAGER_H__
#define __AUDIOMANAGER_H__ 1

#include "soloud.h"
#include "soloud_wav.h"

class AudioManager {

  public:

    /// singleton
    static AudioManager& instance();

    /**
     * @brief play a sound sample with a specified volume
     * @param const unsigned short int index, const float volume
     * @return void
     **/
    void playFX(const unsigned short int index, const float volume);

    /**
     * @brief play a music sample with a specified volume
     * @param const unsigned short int index, const float volume
     * @return void
     **/
    void playMusic(const unsigned short int index, const float volume);

    /// public vars
    SoLoud::Soloud soloud_;
    SoLoud::Wav fx_[4];
    SoLoud::Wav music_[0];

  private:

    /// constructor
    AudioManager();

    /// copy constructor
    AudioManager(const AudioManager& copy);

    /// destructor
    ~AudioManager();
};

#endif
