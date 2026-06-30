// FUNC_NAME: SHLightingEffect::LoadSHQuadricMatrices
void __thiscall SHLightingEffect::LoadSHQuadricMatrices(void)
{
    // Call base initialization (likely sets up shader device or base class members)
    this->InitBase();

    // Retrieve handles for spherical harmonics quadric matrix constants (R, G, B)
    // +0x14 is presumably a pointer to the rendering device or shader resource manager
    // +0x1c0, +0x1c4, +0x1c8 are members storing these handles
    this->quadricMtxR_Handle = this->GetShaderConstantHandle(this->devicePtr + 0x14, "g_SHQuadricMtxR");
    this->quadricMtxG_Handle = this->GetShaderConstantHandle(this->devicePtr + 0x14, "g_SHQuadricMtxG");
    this->quadricMtxB_Handle = this->GetShaderConstantHandle(this->devicePtr + 0x14, "g_SHQuadricMtxB");
}