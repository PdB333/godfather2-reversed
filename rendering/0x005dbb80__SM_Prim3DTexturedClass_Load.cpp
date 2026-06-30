// Xbox PDB: SM_Prim3DTexturedClass::Load
// FUNC_NAME: TextureManager::constructor
// Address: 0x005dbb80
// Initializes a texture manager object: stores default handles and resolves the "AlphaTexture" resource.

#include <cstdint>

// Forward declarations of engine functions (implemented elsewhere)
uint32_t getDefaultHandle();            // FUN_0060a380 - returns a device/context handle
uint32_t getResourceManager(const char* name); // FUN_0060a2e0 - returns resource manager pointer by string key
void     initRandomSeed();              // FUN_006127d0 - seeds random number generator
uint32_t getTexture(uint32_t resMgr, const char* name); // FUN_0060a580 - retrieves texture handle

// Assumed class layout (offsets relative to this)
// +0x00 ... unknown
// +0x10: uint32_t deviceHandle
// +0x14: uint32_t resourceManager
// +0xa8: uint32_t alphaTexture
class TextureManager {
public:
    void __thiscall constructor();
    // ... other members
};

void __thiscall TextureManager::constructor() {
    // Store the default device/context handle
    uint32_t deviceHandle = getDefaultHandle();
    *(uint32_t*)((uint8_t*)this + 0x10) = deviceHandle;

    // Obtain the resource manager associated with the global string (e.g., "RenderDevice")
    uint32_t resourceManager = getResourceManager((const char*)PTR_DAT_00f174cc);
    *(uint32_t*)((uint8_t*)this + 0x14) = resourceManager;

    // Initialize random seeding (e.g., for texture generation)
    initRandomSeed();

    // Retrieve the "AlphaTexture" resource using the resource manager
    uint32_t alphaTexture = getTexture(resourceManager, "AlphaTexture");
    *(uint32_t*)((uint8_t*)this + 0xa8) = alphaTexture;
}