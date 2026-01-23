#pragma once

#include <d3d9.h>

// In je app class
LPDIRECT3DTEXTURE9 cardTexture = nullptr;   
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"  // Download van: https://github.com/nothings/stb/blob/master/stb_image.h

bool LoadTextureFromFile(const char* filename, LPDIRECT3DTEXTURE9* out_texture, int* out_width, int* out_height)
{
    // Laad afbeelding met stb_image
    int width, height, channels;
    unsigned char* data = stbi_load(filename, &width, &height, &channels, 4);
    if (!data)
        return false;

    // Maak DirectX9 texture
    LPDIRECT3DTEXTURE9 texture;
    if (g_pd3dDevice->CreateTexture(width, height, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &texture, nullptr) != D3D_OK)
    {
        stbi_image_free(data);
        return false;
    }

    // Kopieer pixels naar texture
    D3DLOCKED_RECT locked_rect;
    if (texture->LockRect(0, &locked_rect, nullptr, 0) != D3D_OK)
    {
        texture->Release();
        stbi_image_free(data);
        return false;
    }

    for (int y = 0; y < height; y++)
    {
        unsigned char* src = data + y * width * 4;
        unsigned char* dst = (unsigned char*)locked_rect.pBits + y * locked_rect.Pitch;
        for (int x = 0; x < width; x++)
        {
            // RGBA -> BGRA
            dst[0] = src[2];  // B
            dst[1] = src[1];  // G
            dst[2] = src[0];  // R
            dst[3] = src[3];  // A
            src += 4;
            dst += 4;
        }
    }

    texture->UnlockRect(0);
    stbi_image_free(data);

    *out_texture = texture;
    *out_width = width;
    *out_height = height;
    return true;
}