#ifndef MOTION_SFMLAUDIOPLAYBACK_CPP
#define MOTION_SFMLAUDIOPLAYBACK_CPP

#include <Motion/SFMLAudioPlayback.hpp>

namespace mt
{
    SFMLAudioPlayback::SFMLAudioPlayback(DataSource& DataSource, sf::Time OffsetCorrection) :
        AudioPlaybackBase(DataSource, OffsetCorrection)
    { }

    bool SFMLAudioPlayback::onGetData(Chunk& data)
    {
        const int16_t* samples = nullptr;
        std::size_t samplecount = 0;

        if (GetNextBuffer(samples, samplecount))
        {
            data.samples = samples;
            data.sampleCount = samplecount;

            return true;
        }
        else
            return false;
    }

    void SFMLAudioPlayback::onSeek(sf::Time timeOffset)
    {
        // nothing to do
    }

    const float SFMLAudioPlayback::GetVolume()
    {
        return getVolume();
    }

    void SFMLAudioPlayback::SetVolume(float Volume)
    {
        setVolume(Volume);
    }

    void SFMLAudioPlayback::SetupStream(unsigned int ChannelCount, int SampleRate)
    {
        initialize(ChannelCount, SampleRate);
    }

    void SFMLAudioPlayback::SetPlaybackSpeed(float PlaybackSpeed)
    {
        setPitch(PlaybackSpeed);
    }

    void SFMLAudioPlayback::StartStream()
    {
        play();
    }

    void SFMLAudioPlayback::PauseStream()
    {
        pause();
    }

    void SFMLAudioPlayback::StopStream()
    {
        stop();
    }
}

#endif
