// Xbox PDB: SM_Prim3DTexturedClass::Load
// FUNC_NAME: Presentation::initTextureSamplers
void __thiscall Presentation::initTextureSamplers(int thisPtr)
{
    int effectManager;
    int effect;

    effectManager = FUN_0060a380();                      // Get effect manager / render device
    *(int *)(thisPtr + 0x10) = effectManager;

    effect = FUN_0060a2e0(&PTR_DAT_00f1102c);            // Load base color shader effect
    *(int *)(thisPtr + 0x14) = effect;

    FUN_006127d0();                                       // Unknown initialization

    *(int *)(thisPtr + 0x114) = *(int *)(thisPtr + 0x14); // Store effect copy for color pass

    // Load additional shader effects for layered rendering
    *(int *)(thisPtr + 0x118) = FUN_0060a2e0(&PTR_DAT_00f1103c); // Alpha effect
    *(int *)(thisPtr + 0x11c) = FUN_0060a2e0(&PTR_DAT_00f1104c); // Depth effect
    *(int *)(thisPtr + 0x120) = FUN_0060a2e0(&PTR_DAT_00f1106c); // YUV effect
    *(int *)(thisPtr + 0x124) = FUN_0060a2e0(&PTR_DAT_00f1107c); // YUV component effect (Y,U,V shared)
    *(int *)(thisPtr + 0x128) = FUN_0060a2e0(&PTR_DAT_00f1105c); // Additional depth effect
    *(int *)(thisPtr + 0x12C) = FUN_0060a2e0(&PTR_DAT_00f1108c); // YCoCg effect

    // Retrieve texture parameter handles from each effect
    *(int *)(thisPtr + 0xe4) = FUN_0060a580(*(int *)(thisPtr + 0x114), "ColorTexture");
    *(int *)(thisPtr + 0xe8) = FUN_0060a580(*(int *)(thisPtr + 0x118), "AlphaTexture");
    *(int *)(thisPtr + 0xec) = FUN_0060a580(*(int *)(thisPtr + 0x11c), "DepthTexture");
    *(int *)(thisPtr + 0xf0) = FUN_0060a580(*(int *)(thisPtr + 0x128), "DepthTexture");
    *(int *)(thisPtr + 0xf4) = FUN_0060a580(*(int *)(thisPtr + 0x120), "YUVTexture");
    *(int *)(thisPtr + 0xf8) = FUN_0060a580(*(int *)(thisPtr + 0x124), "YTexture");
    *(int *)(thisPtr + 0xfc) = FUN_0060a580(*(int *)(thisPtr + 0x124), "UTexture");
    *(int *)(thisPtr + 0x100) = FUN_0060a580(*(int *)(thisPtr + 0x124), "VTexture");
    *(int *)(thisPtr + 0x110) = FUN_0060a580(*(int *)(thisPtr + 0x124), "AlphaTexture");
    *(int *)(thisPtr + 0x104) = FUN_0060a580(*(int *)(thisPtr + 0x124), "YUV_UVscale");
    *(int *)(thisPtr + 0x10c) = FUN_0060a580(*(int *)(thisPtr + 0x12C), "YCoCgTexture");
}
```