/**
 * @file Texture.h 
 * @author Marco Silva (msilva2203)
 */

#pragma once

#include "Utility.h"
#include <string>
#include <unordered_map>

class Texture
{
public:

    enum class EUnit : u08
    {
        TEXTURE1 = 0,
        TEXTURE2,
        TEXTURE3,
        TEXTURE4,
        TEXTURE5,
        TEXTURE6,
        TEXTURE7,
        TEXTURE8
    };

    Texture();
    Texture(const EUnit TextureUnit);
    virtual ~Texture();

    void Load(const std::string& FilePath);

    void Bind();
    void Unbind();

    void SetTextureUnit(const i32 NewValue);

private:

    u32 Id;
    EUnit Unit;

public:

    class Manager {
    public:

        static Texture* GetTexture(const std::string& FilePath);

    private:

        static std::unordered_map<std::string, Texture*> Cache;

    };

};