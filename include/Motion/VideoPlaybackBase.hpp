#ifndef MOTION_VIDEOPLAYBACKBASE_HPP
#define MOTION_VIDEOPLAYBACKBASE_HPP

#include <memory>
#include <queue>
#include <cmath>

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Mutex.hpp>
#include <SFML/System/Lock.hpp>

#include <Motion/DataSource.hpp>
#include <Motion/State.hpp>
#include <Motion/priv/VideoPacket.hpp>
#include <Motion/Macros.hpp>

namespace mt
{
    class DataSource;

    class VideoPlaybackBase : private sf::NonCopyable
    {
        friend class DataSource;

    private:
        DataSource* m_dataSource;
        bool m_initialSetupDone;

        sf::Mutex m_protectionMutex;
        std::queue<priv::VideoPacketPtr> m_queuedVideoPackets;

        sf::Time m_elapsedTime;
        sf::Time m_frameTime;
        int m_frameJump;
        unsigned int m_playedFrameCount;

        void SourceReloaded();
        void StateChanged(State PreviousState, State NewState);
        void Update(sf::Time DeltaTime);

    public:
        MOTION_API virtual ~VideoPlaybackBase();
        MOTION_API unsigned int GetPlayedFrameCount() const;

    protected:
        VideoPlaybackBase(DataSource& DataSource);
        DataSource* GetDataSource();
        virtual void CreateTexture(int Width, int Height) = 0;
        virtual void UpdateTexture(const uint8_t* RGBABuffer) = 0;
        virtual void ClearTexture() = 0;
    };
}

#endif
