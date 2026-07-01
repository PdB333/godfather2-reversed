// FUNC_NAME: TimeScaler::applyScale
void __thiscall TimeScaler::applyScale(int *this, float scale)
{
    float fVar1;
    float10 fVar2;
    
    // Convert signed int to float, handling negative values by adding 2^32 (0x100000000.0f)
    fVar1 = (float)*this;
    if (*this < 0) {
        fVar1 = fVar1 + 4294967296.0f; // DAT_00e44578 = 2^32
    }
    
    // Scale the value and store as integer in field +0x04
    this[1] = (int)(fVar1 * scale);
    
    // Call rounding function with scaled float and two other fields (+0x0C and +0x08)
    // The function likely rounds the float to an integer using the provided parameters
    fVar2 = (float10)FUN_004b9c30(fVar1 * scale, this[3], this[2]);
    this[3] = (int)(float)fVar2;
    
    return;
}