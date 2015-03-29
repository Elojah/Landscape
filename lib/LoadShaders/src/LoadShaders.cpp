#include "LoadShaders.h"
GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path) {
	// Crée les shaders
	GLuint ProgramID;
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	// Lit le code du vertex shader à partir du fichier
	std::string	VertexShaderCode;
	std::ifstream	VertexShaderStream(vertex_file_path, std::ios::in);
	if(VertexShaderStream.is_open()) {
		std::string Line = "";
		while(getline(VertexShaderStream, Line)) {
			VertexShaderCode += "\n" + Line;
		}
		VertexShaderStream.close();
	} else {
		fprintf(stdout, "Shader file not found : %s\n", vertex_file_path);
	}
	// Lit le code du fragment shader à partir du fichier
	std::string	FragmentShaderCode;
	std::ifstream	FragmentShaderStream(fragment_file_path, std::ios::in);
	if(FragmentShaderStream.is_open()) {
		std::string Line = "";
		while(getline(FragmentShaderStream, Line)) {
			FragmentShaderCode += "\n" + Line;
		}
		FragmentShaderStream.close();
	} else {
		fprintf(stdout, "Shader file not found : %s\n", fragment_file_path);
	}
	GLint Result = GL_FALSE;
	int InfoLogLength;
	// Compile le vertex shader
	printf("Compiling shader : %s\n", vertex_file_path);
	const char	*VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	glCompileShader(VertexShaderID);
	// Vérifie le vertex shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char>VertexShaderErrorMessage(InfoLogLength);
	glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
	if (InfoLogLength > 1) {
		fprintf(stdout, "Compiling error : %s\n", &VertexShaderErrorMessage[0]);
	}
	// Compile le fragment shader
	printf("Compiling shader : %s\n", fragment_file_path);
	const char	*FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(FragmentShaderID);
	// Vérifie le fragment shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char>FragmentShaderErrorMessage(InfoLogLength);
	glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
	if (InfoLogLength > 1) {
		fprintf(stdout, "Compiling error : %s\n", &FragmentShaderErrorMessage[0]);
	}
	// Lit le programme
	fprintf(stdout, "Linking program\n");
	ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);
	// Vérifie le programme
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char>ProgramErrorMessage(std::max(InfoLogLength, int(1)));
	glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &(ProgramErrorMessage[0]));
	if (InfoLogLength > 1) {
		fprintf(stdout, "Linking error : %s\n", &(ProgramErrorMessage[0]));
	}
	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);
	return ProgramID;
}
