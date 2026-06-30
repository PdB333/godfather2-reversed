// FUNC_NAME: VisualObject::setColorFromPreset
// Function at 0x007682a0
// Sets the visual color from a preset indexed by a member at offset 0x5C

// Global array of color presets (likely 32-bit colors or floats)
extern unsigned int colorPresetTable[]; // base: 0x00e51b68

// Helper function: returns an index into colorPresetTable based on some property at +0x5C
int __fastcall getPresetIndex(int param_1); // defined at 0x00767c20

void __fastcall VisualObject::setColorFromPreset(int *this)
{
    int index;
    
    // Retrieve preset index from the object's material/texture ID (offset 0x5C = 0x17 * 4)
    index = getPresetIndex(this[0x17]); // this[0x17] is *(int*)((char*)this + 0x5C)
    
    // Call virtual function at vtable+0x2c (likely setColor or setDiffuse) with:
    // - color from preset table
    // - parameters: 1, 0, 0, 1.0f, 1.0f  (format unknown: maybe alpha, gradient, etc.)
    (*(void (__thiscall**)(void*, unsigned int, int, int, float, float))(*(int*)this + 0x2c))
        (this, colorPresetTable[index], 1, 0, 0, 1.0f, 1.0f);
}