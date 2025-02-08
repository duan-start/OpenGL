#include "Texture2D.h"
#include "stb_image.h"


Texture2D::Texture2D(const char* path,unsigned int *ID) {
    Texture2D::Init (path,ID);
}

//不是很舒服，多次右值引用的方式有点问题
 void Texture2D::Init(const char* path,unsigned int *ID) {
	glGenTextures(1, ID);
	glBindTexture(GL_TEXTURE_2D, *ID);

	//应该暴露给使用者的
	 Texture2D::SetRepeat();
	 Texture2D::SetMinFilter();
	 Texture2D::SetMagFilter();
  
	m_data = stbi_load(path, (int*) & m_width,(int *) & m_height, (int*)&m_nrchannels, 0);
	 Texture2D::CheckError();
}

 void Texture2D::SetRepeat() {
	 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
 }

 void Texture2D::SetMinFilter(GLint MinWay) {
	 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,MinWay);
 }

 void Texture2D::SetMagFilter() {
	 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );
 }
 
 void Texture2D::CheckError() {
	 if (m_data)
	 {  //GL_RGB,GL_RGBA,format;
		 glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_data);
		 glGenerateMipmap(GL_TEXTURE_2D);
	 }
	 else
	 {
		 std::cout << "Failed to load texture" << std::endl;
	 }
}

Texture2D::~Texture2D() { stbi_image_free(m_data); }

