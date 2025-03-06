#pragma once
#include "texture_manager.hpp"


struct Rectangle;
class Sprite
{
private:
	Texture* m_texture;
	unsigned int m_frameIdx;
	unsigned int m_framesInRow;
	int m_frameCount;

public:
	int sheetWidth;
	int sheetHeight;
	int width;
	int height;

	Sprite() {};
	/// <summary>
	/// Create individual sprite
	/// </summary>
	/// <param name="textureFilename"></param>
	Sprite(const std::string& textureFilename);
	/// <summary>
	/// Create sprite sheet
	/// </summary>
	/// <param name="textureFilename"></param>
	/// <param name="frameWidth"></param>
	/// <param name="frameHeight"></param>
	/// <param name="frameCount"></param>
	Sprite(const std::string& textureFilename, int rows, int cols);

	void SetFrameIndex(unsigned int idx);
	void Draw(Rectangle dst, bool flipX=false, bool flipY=false);

	friend class Animator;
};