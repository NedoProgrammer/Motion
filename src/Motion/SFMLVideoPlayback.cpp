#ifndef MOTION_SFMLVIDEOPLAYBACK_CPP
#define MOTION_SFMLVIDEOPLAYBACK_CPP

#include <Motion/SFMLVideoPlayback.hpp>

namespace mt
{
    SFMLVideoPlayback::SFMLVideoPlayback(DataSource& DataSource, sf::Color BufferColor) :
        VideoPlaybackBase(DataSource),
        m_videotexture(),
        m_videosprite(),
        m_buffercolor(BufferColor)
    { }

    void SFMLVideoPlayback::SetInitialBuffer()
    {
        sf::Image initialbuffer;

        initialbuffer.create(m_videotexture.getSize().x, m_videotexture.getSize().y, m_buffercolor);

        m_videotexture.update(initialbuffer);
    }

    const sf::Color SFMLVideoPlayback::GetBufferColor() const
    {
        return m_buffercolor;
    }

    void SFMLVideoPlayback::SetBufferColor(sf::Color BufferColor)
    {
        m_buffercolor = BufferColor;
        DataSource* datasource = GetDataSource();

        if (datasource && datasource->GetState() == State::Stopped)
            SetInitialBuffer();
    }

    sf::Image SFMLVideoPlayback::GetLastFrame() const
    {
        return m_videotexture.copyToImage();
    }

    void SFMLVideoPlayback::CreateTexture(int Width, int Height)
    {
        m_videotexture.create(Width, Height);
        m_videosprite.setTexture(m_videotexture, true);
    }

    void SFMLVideoPlayback::UpdateTexture(const uint8_t* RGBABuffer)
    {
        m_videotexture.update(RGBABuffer);
    }

    void SFMLVideoPlayback::ClearTexture()
    {
        SetInitialBuffer();
    }

    void SFMLVideoPlayback::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();
        target.draw(m_videosprite, states);
    }
}

#endif
