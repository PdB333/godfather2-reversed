// Xbox PDB: SM_DeferredCalcCascVertSpotAttenuationClass::Load
// FUNC_NAME: 0x00491b40 - ShadowRenderer::initialize
// Role: Initializes shadow rendering shader effect and retrieves constant handles.

class ShadowRenderer {
public:
    void initialize();
    // ... other members ...
};

// ShadowRenderer::initialize
void __thiscall ShadowRenderer::initialize() {
    // Get the shadow shader effect from a global pointer
    void* shaderEffect = getShaderEffect(g_pShadowEffect);  // FUN_0060a2e0
    *(void**)(this + 0x14) = shaderEffect;  // Store at this+0x14

    // Additional initialization steps (likely setup of internal structures)
    FUN_004907a0();  // Called without 'this'? Actually, likely member functions,
                     // but Ghidra shows no argument—maybe they are also __thiscall
                     // with 'this' implicit? However, the decompiler may have
                     // missed. We'll treat as member calls with this.
    // Alternative: This->someInitMethod();  We'll keep as direct call for now.

    FUN_00491580();  // Same as above

    // Retrieve handles for shader constants by name
    void* samplerHandle = getShaderConstantHandle(shaderEffect, "g_3rdShadowSampler"); // FUN_0060a580
    *(void**)(this + 0x350) = samplerHandle;  // Store at offset 0x350

    void* viewMatrixHandle = getShaderConstantHandle(shaderEffect, "g_view_to_3rd_shadow"); // FUN_0060a580
    *(void**)(this + 0x354) = viewMatrixHandle; // Store at offset 0x354
}