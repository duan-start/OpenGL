#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <string>

class shader
{
public:
	//id
	unsigned int m_ID;
	//利用源码（不是这个类内的，是属于外部给的）
	shader(const char* vertexpath, const char* fragmentpath);
	//激活着色器
	void Init(const char* vertexpath, const char* fragmentpath);
	void use();
	//使用uniform 工具
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string&  name, int  value) const;
	void setFloat(const std::string& name, float value) const;
	void setMatrix4fv(const std::string& name,float* value) const;
private:
    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
	void checkCompileErrors(unsigned int shader, std::string type);
    
};

#endif