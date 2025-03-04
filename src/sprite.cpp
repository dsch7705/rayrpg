#include "sprite.hpp"
#include "util.hpp"
#include "raylib/raylib.h"
#include "raylib/raymath.h"
#include <cassert>


Sprite::Sprite(const std::string& textureFilename)
{
	m_texture = TextureManager::GetTexture(textureFilename);
	assert(m_texture != nullptr);

	sheetWidth = m_texture->width;
	sheetHeight = m_texture->height;
	width = sheetWidth;
	height = sheetWidth;
	
	m_frameIdx = 0;
	m_framesInRow = 1;
	m_frameCount = 1;
}
Sprite::Sprite(const std::string& textureFilename, int rows, int cols)
{
	m_texture = TextureManager::GetTexture(textureFilename);
	assert(m_texture != nullptr);

	sheetWidth = m_texture->width;
	sheetHeight = m_texture->height;
	width = sheetWidth / cols;
	height = sheetHeight / rows;
	
	m_frameIdx = 0;
	m_framesInRow = cols;
	m_frameCount = rows * cols;
}

void Sprite::SetFrameIndex(unsigned int idx)
{
	if (idx > m_frameCount - 1)
	{
		m_frameIdx = m_frameCount - 1;
		return;
	}

	m_frameIdx = idx;
}
void Sprite::Draw(Rectangle dst, bool flipX, bool flipY)
{
	Rectangle src{ 0, 0, width, height };
	src.x = width * (m_frameIdx % m_framesInRow);
	src.y = height * (m_frameIdx / m_framesInRow);

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