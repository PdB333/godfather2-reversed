// FUNC_NAME: setGlobalColorAndApplyToMaterial
void __cdecl setGlobalColorAndApplyToMaterial(uint32* colorPtr) {
    // Copy the 4 DWORDs (RGBA) into global color storage at 0x011f6870
    gGlobalColor[0] = colorPtr[0];
    gGlobalColor[1] = colorPtr[1];
    gGlobalColor[2] = colorPtr[2];
    gGlobalColor[3] = colorPtr[3];

    // If the global material manager singleton exists and has a valid sub-object
    if (gMaterialManager != nullptr && *(void**)(gMaterialManager + 0x58) != nullptr) {
        // Notify the material system to apply the color
        applyColorToMaterial(
            *(void**)(gMaterialManager + 0x10), // material or renderer (at +0x10)
            *(void**)(gMaterialManager + 0x58), // texture or effect (at +0x58)
            colorPtr
        );
    }
}