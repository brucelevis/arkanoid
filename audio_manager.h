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

    /// public vars
    SoLoud::Soloud soloud_;
    SoLoud::Wav fx_[1];

  private:

    /// constructor
    AudioManager();

    /// copy constructor
    AudioManager(const AudioManager& copy);

    /// destructor
    ~AudioManager();
};

#endif
