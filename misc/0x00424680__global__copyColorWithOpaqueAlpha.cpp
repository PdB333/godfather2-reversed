// FUNC_NAME: global::copyColorWithOpaqueAlpha
// Address: 0x00424680
// Copies three fields from source (likely RGB) and sets fourth field (alpha) to global constant (presumably 1.0f or 255).
// param_1: dest (output color structure, 4 DWORDs)
// param_2: src (input color structure, 3 DWORDs used)
void copyColorWithOpaqueAlpha(uint* dest, uint* src)
{
    uint globalAlpha = DAT_00e2b1a4; // global constant for opaque alpha (likely 1.0f as float or 255 as byte)

    dest[0] = src[0]; // copy first component
    dest[1] = src[1]; // copy second component
    dest[3] = globalAlpha; // set fourth component (alpha) to opaque
    dest[2] = src[2]; // copy third component
}