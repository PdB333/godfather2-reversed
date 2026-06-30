// FUNC_NAME: TextureManager::initialize
void __thiscall TextureManager::initialize(TextureManager *this)
{
    // Allocate or obtain a shader/texture object handle
    uint shaderHandle = FUN_0060a380();                    // likely returns a handle or ID
    this->shaderHandle = shaderHandle;                     // +0x10

    // Obtain another resource handle from a global pointer DAT_00f174cc
    uint resourceHandle = FUN_0060a2e0(&PTR_DAT_00f174cc); // +0x14
    this->resourceHandle = resourceHandle;

    // Perform engine-level initialization (e.g., reset state)
    FUN_006127d0();

    // Look up the texture named "AlphaTexture" using the resource handle
    uint alphaTexture = FUN_0060a580(this->resourceHandle, "AlphaTexture");
    this->alphaTexture = alphaTexture;                     // +0xa8
}