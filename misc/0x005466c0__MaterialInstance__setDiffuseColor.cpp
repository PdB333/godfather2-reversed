// FUNC_NAME: MaterialInstance::setDiffuseColor
// Function at 0x5466c0: Applies a 3-component color (RGB) from param_2 as a 4-component RGBA uniform,
// using a global alpha constant. The color is passed via a virtual function on an object stored at this+0x2E8.
// Offsets: this+0x2E8 -> pointer to a material parameter object; that object+0xD0 -> vtable pointer; vtable+0x40 -> virtual setter.

void __thiscall MaterialInstance::setDiffuseColor(MaterialInstance* this, float* colorRGB) {
    float localColor[4];                     // RGBA quad for the shader uniform
    localColor[0] = colorRGB[0];             // Red
    localColor[1] = colorRGB[1];             // Green
    localColor[2] = colorRGB[2];             // Blue
    localColor[3] = g_globalAlpha;           // Global alpha constant (DAT_00e2b1a4), likely 1.0f

    // Retrieve the material parameter set from the object
    int* paramSet = *(int**)(this + 0x2E8);

    // Precall (likely a profiler/lock marker)
    FUN_009f2000();

    // Virtual call: paramSet+0xD0 contains a pointer to a vtable,
    // offset 0x40 into that vtable is the "set uniform" function.
    // This function receives the address of the local color array.
    (**(code**)(*(int*)(paramSet + 0xD0) + 0x40))(&localColor);
}