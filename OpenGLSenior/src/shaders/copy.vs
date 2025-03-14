#version 330 core

// ���붥������
layout(location = 0) in vec3 aPos;      // ����λ��
layout(location = 1) in vec2 aTexCoord; // ������������

// �����Ƭ����ɫ���ı���
out vec2 TexCoords;

// ������ɫ��������
void main() {
    // ���ö���λ��
    gl_Position = vec4(aPos, 1.0);

    // ���������괫�ݵ�Ƭ����ɫ��
    TexCoords = vec2(aPos.x,aPos.y);
}