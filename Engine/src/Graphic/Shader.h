#ifndef _SHADER_H_
#define _SHADER_H_

class Shader
{
public:
	Shader();
	Shader(const char* vsPath, const char* fsPath);
	virtual ~Shader();

	void Active();
	unsigned int m_ShaderId() const;
	unsigned int GetProgram() const;
	unsigned int GetVertexShader() const;
	unsigned int GetFragmentShader() const;
	unsigned int GetAttribute(const char* attribute) const;

	template<typename T>
	void SetAttribute(const char* attribute, T value);
private:
	unsigned int LoadShader(unsigned int type, const char* path);
	unsigned int LoadProgram(unsigned int vertexShader, unsigned int fragmentShader);

	unsigned int m_ShaderId;
	const char* m_ShaderName;

	unsigned int* m_Attributes;
	unsigned int m_VertexShaderId;
	unsigned int m_FragementShaderId;
	unsigned int m_ProgramId;
};

#endif // !_SHADER_H_

