// FUNC_NAME: SomeClass::isPointBehindPlane
bool __fastcall isPointBehindPlane(int this)
{
    int iVar1;
    
    iVar1 = *(int *)(this + 0x14);
    // Dot product of plane normal (at +0x90, +0x94, +0x98) with direction from plane origin to point
    // Plane normal is stored as three floats at this+0x90, this+0x94, this+0x98
    // Point position is at iVar1+0x10, iVar1+0x14, iVar1+0x18
    if (*(float *)(this + 0x98) * *(float *)(iVar1 + 0x18) +
        *(float *)(this + 0x94) * *(float *)(iVar1 + 0x14) +
        *(float *)(this + 0x90) * *(float *)(iVar1 + 0x10) < 0.0f) {
        return true;
    }
    return false;
}