#ifndef MOTION_DATASOURCE_HPP
#define MOTION_DATASOURCE_HPP

#include <string>
#include <cstdint>
#include <memory>
#include <thread>
#include <chrono>
#include <atomic>
#include <queue>
#include <vector>
#include <iostream>

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Mutex.hpp>
#include <SFML/System/Lock.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>

#include <Motion/priv/AudioPacket.hpp>
#include <Motion/AudioPlaybackBase.hpp>
#include <Motion/priv/VideoPacket.hpp>
#include <Motion/VideoPlaybackBase.hpp>
#include <Motion/State.hpp>
#include <Motion/Macros.hpp>

namespace mt
{
    class VideoPlaybackBase;
    class AudioPlaybackBase;

    class DataSource : private sf::NonCopyable
    {
        friend class VideoPlaybackBase;
        friend class AudioPlaybackBase;

    private:
        struct DecodeData;

        sf::Clock m_updateClock;
        sf::Time m_playingOffset;
        sf::Time m_fileLength;
        sf::Vector2i m_videoSize;
        int m_audioChannelCount;
        float m_playbackSpeed;

        std::unique_ptr<DecodeData> m_data;

        State m_state;
        std::unique_ptr<std::thread> m_decodeThread;
        std::atomic<bool> m_shouldThreadRun;
        std::atomic<bool> m_EOFReached;
        std::atomic<bool> m_PlayingToEOF;

        sf::Mutex m_playbackMutex;
        std::vector<mt::VideoPlaybackBase*> m_videoPlaybacks;
        std::vector<mt::AudioPlaybackBase*> m_audioPlaybacks;

        void Cleanup();
        void StartDecodeThread();
        void StopDecodeThread();
        void DecodeThreadRun();
        bool IsFull();
        void NotifyStateChanged(State NewState);

    public:
        MOTION_API DataSource();
	    MOTION_API ~DataSource();
	    MOTION_API bool LoadFromFile(const std::string& Filename, bool EnableVideo = true, bool EnableAudio = true);
	    MOTION_API void Play();
	    MOTION_API void Pause();
	    MOTION_API void Stop();
	    MOTION_API bool HasVideo() const;
	    MOTION_API bool HasAudio() const;
	    MOTION_API sf::Vector2i GetVideoSize() const;
	    MOTION_API State GetState() const;
	    MOTION_API sf::Time GetVideoFrameTime() const;
	    MOTION_API int GetAudioChannelCount() const;
	    MOTION_API int GetAudioSampleRate() const;
	    MOTION_API sf::Time GetFileLength() const;
	    MOTION_API sf::Time GetPlayingOffset() const;
	    MOTION_API void SetPlayingOffset(sf::Time PlayingOffset);
	    MOTION_API void Update();
	    MOTION_API float GetPlaybackSpeed() const;
	    MOTION_API void SetPlaybackSpeed(float PlaybackSpeed);
	    MOTION_API bool IsEndofFileReached() const;
    };
}

#endif
