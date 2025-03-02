#pragma once
#include "texture.hpp"


struct Rectangle;
class Sprite
{
private:
	Texture* m_texture;
	unsigned int m_spritesheetIdx;
	unsigned int m_framesInRow;
	int m_frameCount;
	bool m_loop;

public:
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
	Sprite(const std::string& textureFilename, int frameWidth, int frameHeight, int frameCount, bool loop);

	void FrameStepForward(void);
	void FrameStepBackward(void);
	void FrameSetIndex(unsigned int idx);
	void Draw(Rectangle dst, bool flipX=false, bool flipY=false);

};