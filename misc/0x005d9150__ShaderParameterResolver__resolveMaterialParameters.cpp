// FUNC_NAME: ShaderParameterResolver::resolveMaterialParameters
void __thiscall ShaderParameterResolver::resolveMaterialParameters(ShaderParameterResolver* this)
{
    // Retrieve the effect/resource handle from the parent object at offset -0x110
    // +0x110 before this: pointer to EARS::Effect or equivalent effect resource
    void* effect = *(void**)((uint8_t*)this - 0x110);

    // Fetch and store handles for vertex shader parameters
    this->colorMulHandle = FUN_0060a580(effect, "inColorMul");  // +0x64
    this->colorAddHandle = FUN_0060a580(effect, "inColorAdd");  // +0x60
    this->transUHandle   = FUN_0060a580(effect, "transU");      // -0x78 (relative to this)
    this->transVHandle   = FUN_0060a580(effect, "transV");      // -0x74
    this->mvpHandle      = FUN_0060a580(effect, "ModelViewProj"); // -0xd0
}