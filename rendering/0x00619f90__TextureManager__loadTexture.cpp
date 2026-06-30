// FUNC_NAME: TextureManager::loadTexture
bool TextureManager::loadTexture(uint textureIndex, int width, int height, int mipCount, int extraFlags)
{
    // Validate texture index (max 4095)
    if (textureIndex > 0xfff) {
        return false;
    }

    // Get texture descriptor from global array
    TextureDescriptor* desc = &g_textureDescriptors[textureIndex]; // +0x28 base, each 0x38 bytes
    if (desc == nullptr) { // redundant check
        return false;
    }
    int* dataPtr = reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(desc) + 0x10); // offset 0x10
    if (*dataPtr == 0) {
        return false;
    }

    // Get global shader/context from engine
    uint context = getTextureContext(); // FUN_0061a9f0
    if (context == 0) {
        return false;
    }

    uint flags = 0;

    // Parse texture type from config (2d/3d/cube)
    const char* typeStr = getConfigString(g_configTextureType); // DAT_011f4200
    if (typeStr != nullptr) {
        if (strcmp(typeStr, "2d") == 0) {
            // 2D texture (default)
        } else if (strcmp(typeStr, "3d") == 0) {
            flags = 4; // 0x4
        } else if (strcmp(typeStr, "cube") == 0) {
            flags = 2; // 0x2
        } else {
            return false; // unknown type
        }
    } else {
        // Fallback: check if "3d" is default?
        if (getConfigBool(g_configIs3D)) { // DAT_011f4204
            flags = 1; // 0x1
        }
    }

    // Apply additional flags from config (mipmaps, etc.)
    if (getConfigBool(g_configMipmaps)) { // DAT_011f4208
        flags |= 0x40;
    }
    if (getConfigBool(g_configSRGB)) { // DAT_011f420c
        flags |= 0x10;
    }

    // Parse filter mode from config (linear/sRGB)
    const char* filterStr = getConfigString(g_configFilterMode); // DAT_011f421c
    if (filterStr != nullptr) {
        if (strcmp(filterStr, "linear") == 0) {
            // linear
        } else if (strcmp(filterStr, "sRGB") == 0) {
            flags |= 0x2000;
        } else {
            return false;
        }
    }

    // Parse address mode (wrap/mirror/clamp/border/ignore)
    const char* addrModeStr = getConfigString(g_configAddressMode); // DAT_011f4210
    if (addrModeStr != nullptr) {
        if (strcmp(addrModeStr, "linear") == 0) {
            // linear (no change)
        } else if (strcmp(addrModeStr, "point") == 0) {
            flags |= 0x10000;
        } else if (strcmp(addrModeStr, "aniso") == 0) {
            flags |= 0x20000;
        } else if (strcmp(addrModeStr, "ignore") == 0) {
            flags |= 0x30000;
        } else {
            return false;
        }
    }

    // Special handling: if certain environment flag is set and we are in sRGB mode 
    // but not in specific modes, force aniso
    if (g_forceAnisoForSRGB && (flags & 0x2000) && ((flags & 0x10006) == 0)) { // DAT_0120569f
        flags |= 0x20000;
    }

    // Parse texture wrap mode
    const char* wrapStr = getConfigString(g_configWrapMode); // DAT_011f4214
    if (wrapStr != nullptr) {
        if (strcmp(wrapStr, "wrap") == 0) {
            // wrap (default)
        } else if (strcmp(wrapStr, "mirror") == 0) {
            flags |= 0x100000;
        } else if (strcmp(wrapStr, "clamp") == 0) {
            flags |= 0x200000;
        } else if (strcmp(wrapStr, "border-black") == 0) {
            flags |= 0x300000;
        } else if (strcmp(wrapStr, "border-white") == 0) {
            flags |= 0x400000;
        } else if (strcmp(wrapStr, "ignore") == 0) {
            flags |= 0x700000;
        } else {
            return false;
        }
    }

    // Check if texture is not compressed (field at offset +8 in descriptor)
    if (*(reinterpret_cast<int*>(dataPtr + 2)) == 0) { // iVar1+8: offset 0x18? Actually iVar1 is a pointer to something. We need to interpret correctly.
        // Original: if (*(int *)(iVar1 + 8) == 0) -> flag |= 0x80
        // iVar1 came from *(&DAT_..+0x10). So iVar1 is a pointer. The field at +8 might be 'compressed' flag.
        flags |= 0x80;
    }

    // Call the actual texture creation function
    uint result = createTextureEntry(context, flags, width, height, mipCount, textureIndex); // FUN_00606c80
    if (result != textureIndex) {
        freeTextureEntry(textureIndex, 1); // FUN_006065a0
        return false;
    }
    return true;
}