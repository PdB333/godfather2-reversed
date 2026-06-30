// FUNC_NAME: EARSVisualObject::initializeMaterial
// Function address: 0x00493eb0
// Called during initialization of visual objects (props, characters, etc.) 
// Sets up a material/texture handle at offset +0x14 from a global material table
// indexed by the value at +0x2D0 (material index).
void __fastcall EARSVisualObject::initializeMaterial(void)
{
    // Global table of material handles (likely loaded from a resource file)
    extern int *gMaterialTable[]; // 0x011280FC

    // Retrieve material index from object (e.g., a model or prop)
    int materialIndex = *(int *)(this + 0x2D0); // +0x2D0: material lookup index

    // Load the actual material handle via the engine's material system
    // Returns a handle/pointer to the material implementation
    void *materialHandle = FUN_0060a2e0(gMaterialTable[materialIndex]); // 0x0060a2e0: createMaterialFromTable

    // Store the material handle for later rendering
    *(void **)(this + 0x14) = materialHandle; // +0x14: material handle pointer

    // Apply the material to the object and finalize rendering setup
    FUN_004907a0(); // 0x004907a0: applyMaterialToObject
    FUN_00493fc0(); // 0x00493fc0: updateRenderState
}