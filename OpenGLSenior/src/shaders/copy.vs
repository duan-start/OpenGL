#version 330 core

// 输入顶点数据
layout(location = 0) in vec3 aPos;      // 顶点位置
layout(location = 1) in vec2 aTexCoord; // 顶点纹理坐标

// 输出到片段着色器的变量
out vec2 TexCoords;

// 顶点着色器主函数
void main() {
    // 设置顶点位置
    gl_Position = vec4(aPos, 1.0);

    // 将纹理坐标传递到片段着色器
    TexCoords = vec2(aPos.x,aPos.y);
}