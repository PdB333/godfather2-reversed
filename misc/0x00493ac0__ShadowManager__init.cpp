// FUNC_NAME: ShadowManager::init
void __thiscall ShadowManager::init(int thisPtr)
{
    // Get the render device/context from the global pointer
    undefined4 device = getRenderDevice(&PTR_DAT_0110a0ec);  // FUN_0060a2e0
    *(undefined4 *)(thisPtr + 0x14) = device; // Store device pointer at offset +0x14

    // Call base class initialization or other setup
    baseClassInit(); // FUN_004907a0
    setupCustom();  // FUN_00493a10

    // Look up shader parameters by name and store their handles
    *(undefined4 *)(thisPtr + 0x290) = getShaderParam(*(undefined4 *)(thisPtr + 0x14), "g_shadowAttenuationBuffer"); // FUN_0060a580
    *(undefined4 *)(thisPtr + 0x298) = getShaderParam(*(undefined4 *)(thisPtr + 0x14), "g_attenuationFactor");       // FUN_0060a580
    return;
}