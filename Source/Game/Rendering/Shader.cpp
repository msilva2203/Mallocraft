/**
 * @file Shader.cpp 
 * @author Marco Silva (msilva2203)
 */

#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <limits.h>

#include "glad/glad.h"

Shader::Shader() {

}

Shader::~Shader() {

}

void Shader::Load(const std::string& FilePath) {
    enum class EParseState {
        None = 0,
        Vertex,
        Fragment
    };
    
    EParseState ParseState = EParseState::None;

    std::ifstream InputFile(FilePath);

    std::stringstream VertexStream;
    std::stringstream FragmentStream;

    std::string Line;
    while (std::getline(InputFile, Line)) {
        if (Line.size() > 0 && Line.at(0) == '#') {
            if (Line.find("#vertex") != std::string::npos) {
                ParseState = EParseState::Vertex;
                continue;
            } else if (Line.find("#fragment") != std::string::npos) {
                ParseState = EParseState::Fragment;
                continue;
            }
        }

        switch (ParseState) {
            case EParseState::None: {
                break;
            }
            case EParseState::Vertex: {
                VertexStream << Line << std::endl;
                break;
            }
            case EParseState::Fragment: {
                FragmentStream << Line << std::endl;
                break;
            }
            default: {
                break;
            }
        }
    }

    InputFile.close();

    VertexSource = VertexStream.str();
    FragmentSource = FragmentStream.str();

    Compile(VertexSource, FragmentSource);
}

void Shader::Compile(const std::string& VertexSrc, const std::string& FragmentSrc) {
    i32 SuccessStatus;
    i08 InfoLog[512];

    std::cout << "Compiling Shader..." << std::endl;

    std::cout << "Compiling Vertex Shader..." << std::endl;
    u32 VertexShader = glCreateShader(GL_VERTEX_SHADER);
    const i08 *VertexSrcPtr = VertexSrc.c_str();
    glShaderSource(VertexShader, 1, &VertexSrcPtr, NULL);
    glCompileShader(VertexShader);

    glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &SuccessStatus);
    if (!SuccessStatus)
    {
        glGetShaderInfoLog(VertexShader, 512, NULL, InfoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << InfoLog << std::endl;
    }

    std::cout << "Compiling Fragment Shader..." << std::endl;
    u32 FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const i08 *FragmentSrcPtr = FragmentSrc.c_str();
    glShaderSource(FragmentShader, 1, &FragmentSrcPtr, NULL);
    glCompileShader(FragmentShader);

    glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &SuccessStatus);
    if (!SuccessStatus)
    {
        glGetShaderInfoLog(FragmentShader, 512, NULL, InfoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << InfoLog << std::endl;
    }

    std::cout << "Creating Shader Program..." << std::endl;
    Program = glCreateProgram();
    glAttachShader(Program, VertexShader);
    glAttachShader(Program, FragmentShader);
    glLinkProgram(Program);

    glGetProgramiv(Program, GL_LINK_STATUS, &SuccessStatus);
    if (!SuccessStatus) {
        glGetProgramInfoLog(Program, 512, NULL, InfoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << InfoLog << std::endl;
    }

    glDeleteShader(VertexShader);
    glDeleteShader(FragmentShader);

    for (i32 i = 0; i < 16; i++) {
        #define TEXTURE_UNIFORM_NAME(x) "uTexture##x"
        std::cout << TEXTURE_UNIFORM_NAME(i) << std::endl;
        SetInt(TEXTURE_UNIFORM_NAME(i), i);
        #undef TEXTURE_UNIFORM_NAME
    }
}

void Shader::Bind() {
    glUseProgram(Program);
}

void Shader::Unbind() {
    glUseProgram(0);
}

void Shader::SetBool(const std::string& Name, bool bNewValue) {
    i32 Location = GetUniformLocation(Name);
    glUniform1i(Location, (i32)bNewValue);
}

void Shader::SetInt(const std::string& Name, i32 NewValue) {
    i32 Location = GetUniformLocation(Name);
    glUniform1i(Location, (i32)NewValue);
}

void Shader::SetFloat(const std::string& Name, f32 NewValue) {
    i32 Location = GetUniformLocation(Name);
    std::cout << Location << std::endl;
    glUniform1f(Location, NewValue);
}

void Shader::SetFloat2(const std::string& Name, f32 X, f32 Y) {
    i32 Location = GetUniformLocation(Name);
    glUniform2f(Location, X, Y);
}

void Shader::SetFloat3(const std::string& Name, f32 X, f32 Y, f32 Z) {
    i32 Location = GetUniformLocation(Name);
    glUniform3f(Location, X, Y, Z);
}

void Shader::SetFloat4(const std::string& Name, f32 X, f32 Y, f32 Z, f32 W) {
    i32 Location = GetUniformLocation(Name);
    glUniform4f(Location, X, Y, Z, W);
}

void Shader::SetFloatMatrix4(const std::string& Name, const glm::mat4& NewValue) {
    i32 Location = GetUniformLocation(Name);
    glUniformMatrix4fv(Location, 1, GL_FALSE, glm::value_ptr(NewValue));
}

i32 Shader::GetUniformLocation(const std::string& Name) {
    auto It = UniformLocations.find(Name);
    if (It != UniformLocations.end()) {
        return It->second;
    }
    i32 Location = glGetUniformLocation(Program, Name.c_str());
    UniformLocations[Name] = Location;
    return Location;
}

std::unordered_map<std::string, Shader*> Shader::Manager::Cache = std::unordered_map<std::string, Shader*>();
std::vector<Shader*> Shader::Manager::Shaders = std::vector<Shader*>();

Shader* Shader::Manager::GetShader(const std::string& FilePath) {
    auto It = Cache.find(FilePath);
    if (It != Cache.end()) {
        return It->second;
    }
    Shader* NewShader = new Shader();
    NewShader->Load(FilePath);
    Cache[FilePath] = NewShader;
    Shaders.push_back(NewShader);
    return NewShader;
}

std::vector<Shader*> Shader::Manager::GetShaders() {
    return Shaders;
}