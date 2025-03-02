#include "sprite.hpp"
#include "util.hpp"
#include "raylib/raylib.h"
#include "raylib/raymath.h"
#include <cassert>


Sprite::Sprite(const std::string& textureFilename)
{
	m_texture = TextureManager::GetTexture(textureFilename);
	assert(m_texture != nullptr);

	width = m_texture->width;
	height = m_texture->height;
	m_spritesheetIdx = 0;
	m_framesInRow = 1;
	m_frameCount = 1;
	m_loop = false;
}
Sprite::Sprite(const std::string& textureFilename, int frameWidth, int frameHeight, int frameCount, bool loop)
{
	m_texture = TextureManager::GetTexture(textureFilename);
	assert(m_texture != nullptr);

	width = frameWidth;
	height = frameHeight;
	m_spritesheetIdx = 0;
	m_framesInRow = m_texture->width / frameWidth;
	m_frameCount = frameCount;
	m_loop = loop;
}

void Sprite::FrameStepForward()
{
	m_spritesheetIdx++;
	if (m_spritesheetIdx > m_frameCount - 1)
	{
		if (m_loop)
		{
			m_spritesheetIdx = 0;
			return;
		}

		m_spritesheetIdx--;
	}
}
void Sprite::FrameStepBackward()
{
	if (m_spritesheetIdx - 1 < 0)
	{
		if (m_loop)
			m_spritesheetIdx = m_frameCount - 1;
		return;
	}
	m_spritesheetIdx--;
}
void Sprite::FrameSetIndex(unsigned int idx)
{
	if (idx > m_frameCount - 1)
	{
		m_spritesheetIdx = m_frameCount - 1;
		return;
	}

	m_spritesheetIdx = idx;
}
void Sprite::Draw(Rectangle dst, bool flipX, bool flipY)
{
	Rectangle src{ 0, 0, width, height };
	src.x = width * (m_spritesheetIdx % m_framesInRow);
	src.y = height * (m_spritesheetIdx / m_framesInRow);

	if (flipX)
	{
		//src.x += width;
		src.width *= -1;
	}
	if (flipY)
	{
		//src.y += height;
		src.height *= -1;
	}

	DrawTexturePro(*m_texture, src, dst, Vector2Zeros, 0.f, WHITE);
}