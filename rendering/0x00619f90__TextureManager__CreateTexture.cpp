// FUNC_NAME: TextureManager::CreateTexture
// Function address: 0x00619f90
// Purpose: Creates/reconfigures a texture slot with specified parameters (dimension, filtering, addressing, etc.)
// Returns 1 on success, 0 on failure.

#include <cstdint>
#include <cstring>

// Forward declarations of internal engine functions (stubs)
extern char* GetGlobalSettingString(uint32_t settingId);
extern bool IsGlobalSettingEnabled(uint32_t settingId);
extern void* GetRenderDevice(); // returns device handle
extern uint32_t AllocateTextureSlot(void* device, uint32_t flags, void* param2, void* param3, void* param4, uint32_t slotIndex);
extern void FreeTextureSlot(uint32_t slotIndex, bool unknown);

// Global data (addresses from Ghidra)
extern uint8_t* gTextureSlotArrayBase; // DAT_011a0f28
extern uint32_t* gTextureSlotPtrArray; // DAT_011a0f38 (offsets from base)
extern uint8_t gSrgbEnabledFlag; // DAT_0120569f

// Structure of a texture slot entry (size 0x38)
struct TextureSlot {
    uint8_t unknown[0x38];
};

// Global settings IDs (reconstructed)
const uint32_t kSettingTextureDimensionId = 0; // DAT_011f4200
const uint32_t kSettingTextureFilterId = 0;    // DAT_011f421c
const uint32_t kSettingTextureMipFilterId = 0; // DAT_011f4210
const uint32_t kSettingTextureAddressUId = 0;  // DAT_011f4214
const uint32_t kSettingTextureAddressVId = 0;  // DAT_011f4218 (not shown but likely)
// Note: The actual setting IDs are unknown, placeholders used.

int32_t __cdecl TextureManager::CreateTexture(uint32_t slotIndex, void* param2, void* param3, void* param4)
{
    // Validate slot index (max 4095)
    if (slotIndex > 0xFFF) {
        return 0;
    }

    // Check if slot array entry is valid
    TextureSlot* slot = reinterpret_cast<TextureSlot*>(gTextureSlotArrayBase + slotIndex * 0x38);
    if (slot == nullptr) {
        return 0;
    }

    // Check if texture handle pointer is non-zero
    uint32_t* textureHandle = reinterpret_cast<uint32_t*>(gTextureSlotPtrArray + slotIndex * 0x38);
    if (*textureHandle == 0) {
        return 0;
    }

    // Get render device
    void* device = GetRenderDevice();
    if (device == nullptr) {
        return 0;
    }

    // Get device info (used later for texture creation)
    // FUN_0061a9f0 returns some device capability or renderer object
    void* deviceInfo = GetDeviceInfo(); // placeholder: FUN_0061a9f0

    uint32_t flags = 0;

    // Determine texture dimension type
    char* dimStr = GetGlobalString(kSettingTextureDimensionId);
    if (dimStr != nullptr) {
        if (strcmp(dimStr, "2d") == 0) {
            flags |= 0x1; // 2D texture flag
        } else if (strcmp(dimStr, "3d") == 0) {
            flags |= 0x4; // 3D texture flag
        } else if (strcmp(dimStr, "cube") == 0) {
            flags |= 0x2; // Cube map flag
        } else {
            return 0; // Unknown dimension
        }
    } else {
        // If no dimension string, check another global setting
        if (IsGlobalSettingEnabled(kSettingDefault2D)) {
            flags |= 0x1;
        }
    }

    // Check additional global flags
    if (IsGlobalSettingEnabled(kSettingTextureCompressed)) {
        flags |= 0x40; // Compressed?
    }
    if (IsGlobalSettingEnabled(kSettingTextureSRGB)) {
        flags |= 0x10; // sRGB?
    }

    // Texture filtering mode
    char* filterStr = GetGlobalString(kSettingTextureFilterId);
    if (filterStr != nullptr) {
        if (strcmp(filterStr, "linear") == 0) {
            flags |= 0x2000; // Linear filter
        } else if (strcmp(filterStr, "sRGB") == 0) {
            flags |= 0x2000; // Also linear? Or maybe different
        } else {
            return 0; // Unknown filter
        }
    }

    // Mip filter mode
    char* mipFilterStr = GetGlobalString(kSettingTextureMipFilterId);
    if (mipFilterStr != nullptr) {
        if (strcmp(mipFilterStr, "linear") == 0) {
            // No flag set? (kept as is)
        } else if (strcmp(mipFilterStr, "point") == 0) {
            flags |= 0x10000; // Point filter
        } else if (strcmp(mipFilterStr, "aniso") == 0) {
            flags |= 0x20000; // Anisotropic
        } else if (strcmp(mipFilterStr, "ignore") == 0) {
            flags |= 0x30000; // Ignore mip filter
        } else {
            return 0;
        }
    }

    // Apply sRGB override if enabled and no incompatible flags
    if (gSrgbEnabledFlag != 0 && (flags & 0x2000) != 0 && (flags & 0x10006) == 0) {
        flags |= 0x20000; // Force anisotropic? Or another flag
    }

    // Address mode U/V (texture addressing)
    char* addrStr = GetGlobalString(kSettingTextureAddressUId); // Likely U, but both use same setting
    if (addrStr != nullptr) {
        if (strcmp(addrStr, "wrap") == 0) {
            // No flag (default wrap)
        } else if (strcmp(addrStr, "mirror") == 0) {
            flags |= 0x100000; // Mirror
        } else if (strcmp(addrStr, "clamp") == 0) {
            flags |= 0x200000; // Clamp
        } else if (strcmp(addrStr, "border-black") == 0) {
            flags |= 0x300000; // Border black
        } else if (strcmp(addrStr, "border-white") == 0) {
            flags |= 0x400000; // Border white
        } else if (strcmp(addrStr, "ignore") == 0) {
            flags |= 0x700000; // Ignore
        } else {
            return 0;
        }
    }

    // Check if texture has no mipmaps (some internal flag)
    if (*(int32_t*)(textureHandle + 2) == 0) { // offset +8 from handle
        flags |= 0x80; // No mipmaps flag
    }

    // Create the texture slot
    uint32_t result = AllocateTextureSlot(deviceInfo, flags, param2, param3, param4, slotIndex);
    if (result != slotIndex) {
        FreeTextureSlot(slotIndex, 1);
        return 0;
    }

    return 1;
}