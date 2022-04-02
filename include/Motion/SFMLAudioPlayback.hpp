#ifndef MOTION_SFMLAUDIOPLAYBACK_HPP
#define MOTION_SFMLAUDIOPLAYBACK_HPP

#include <SFML/Audio/SoundStream.hpp>
#include <Motion/AudioPlaybackBase.hpp>
#include <Motion/Macros.hpp>

namespace mt
{
    class SFMLAudioPlayback : public AudioPlaybackBase, private sf::SoundStream
    {
    private:
        bool onGetData(Chunk& data);
        void onSeek(sf::Time timeOffset);

    public:
        MOTION_API SFMLAudioPlayback(DataSource& DataSource, sf::Time OffsetCorrection = sf::milliseconds(50));
	    MOTION_API const float GetVolume();
	    MOTION_API void SetVolume(float Volume);

    protected:
        void SetupStream(unsigned int ChannelCount, int SampleRate);
        void SetPlaybackSpeed(float PlaybackSpeed);
        void StartStream();
        void PauseStream();
        void StopStream();
    };
}

#endif
