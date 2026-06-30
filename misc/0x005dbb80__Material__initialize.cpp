// FUNC_NAME: Material::initialize
// Address: 0x005dbb80
// Role: Initializes a material object, retrieving device, texture manager, and alpha texture parameter.

void Material::initialize()
{
    // Get the rendering device (likely singleton)
    void* pDevice = getRenderDevice();
    this->m_pDevice = pDevice; // +0x10

    // Get the texture manager from a global pointer
    void* pTextureManager = getTextureManager(PTR_DAT_00f174cc); // +0x14
    this->m_pTextureManager = pTextureManager;

    // Perform some initialization (e.g., create default state)
    initializeDefaultState();

    // Retrieve the alpha texture parameter from the texture manager
    void* hAlphaTexture = getTextureParameter(this->m_pTextureManager, "AlphaTexture");
    this->m_hAlphaTexture = hAlphaTexture; // +0xa8
}