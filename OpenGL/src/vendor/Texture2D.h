#pragma once
#include <iostream>
#include "glad/glad.h"
class Texture2D {

public :
	Texture2D(const char* path,unsigned int *ID);
	void Init(const char * path,unsigned int *ID);
	void SetRepeat();

	//这里不是做传引用吗，不可以转化是怎么回事
	void SetMinFilter(GLint MinWay = GL_LINEAR_MIPMAP_LINEAR);
	void SetMagFilter();
	void CheckError();
	~Texture2D();
	inline void Getwidth() const { std::cout << "WIDHT" << m_width; }
	inline void Getheight() const { std::cout << "HEIGHT" << m_height; }
	inline void Getchannels() const { std::cout << "NRCHANNELS" << m_nrchannels; }

private:
	int m_width, m_nrchannels, m_height;
	unsigned char* m_data;
};