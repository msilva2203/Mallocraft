/**
 * @file Texture.cpp 
 * @author Marco Silva (msilva2203)
 */

#include "Texture.h"
#include "stb_image.h"
#include "glad/glad.h"

#include <iostream>

Texture::Texture() :
    Texture(EUnit::TEXTURE1)
{
    
}

Texture::Texture(const EUnit TextureUnit) : 
    Unit(TextureUnit)
{
    glGenTextures(1, &Id);
}

Texture::~Texture() {
    glDeleteTextures(1, &Id);
}

void Texture::Load(const std::string& FilePath) {
    Bind();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    u08* Data;
    i32 Width, Height, NumChannels;
    stbi_set_flip_vertically_on_load(true); 
    Data = stbi_load(FilePath.c_str(), &Width, &Height, &NumChannels, 0);

    if (Data) { 
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, Data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture: " << FilePath << std::endl;
    }

    stbi_image_free(Data);
}

void Texture::Bind() {
    glActiveTexture(GL_TEXTURE0 + (i32)Unit);
    glBindTexture(GL_TEXTURE_2D, Id);
}

void Texture::Unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

std::unordered_map<std::string, Texture*> Texture::Manager::Cache = std::unordered_map<std::string, Texture*>();

Texture* Texture::Manager::GetTexture(const std::string& FilePath) {
    auto It = Cache.find(FilePath);
    if (It != Cache.end()) {
        return It->second;
    }
    Texture* NewTexture = new Texture();
    NewTexture->Load(FilePath);
    Cache[FilePath] = NewTexture;
    return NewTexture;
}
