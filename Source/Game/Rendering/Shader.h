/**
 * @file Shader.h
 * @author Marco Silva (msilva2203)
 */

#pragma once

#include "Utility.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <unordered_map>
#include <vector>

class Shader
{
public:

    Shader();
    virtual ~Shader();

    void Load(const std::string& FilePath);
    void Compile(const std::string& VertexSrc, const std::string& FragmentSrc);

    void Bind();
    void Unbind();

    void SetBool(const std::string& Name, bool bNewValue);
    void SetInt(const std::string& Name, i32 NewValue);
    void SetFloat(const std::string& Name, f32 NewValue);
    void SetFloat2(const std::string& Name, f32 X, f32 Y);
    void SetFloat3(const std::string& Name, f32 X, f32 Y, f32 Z);
    void SetFloat4(const std::string& Name, f32 X, f32 Y, f32 Z, f32 W);
    void SetFloatMatrix4(const std::string& Name, const glm::mat4& NewValue);

private:

    i32 GetUniformLocation(const std::string& Name);

    u32 Program;
    std::string VertexSource;
    std::string FragmentSource;
    std::unordered_map<std::string, i32> UniformLocations;

public:

    class Manager
    {
    public:

        static Shader* GetShader(const std::string& FilePath);
        static std::vector<Shader*> GetShaders();

    private:
    
        static std::unordered_map<std::string, Shader*> Cache;
        static std::vector<Shader*> Shaders;

    };

};