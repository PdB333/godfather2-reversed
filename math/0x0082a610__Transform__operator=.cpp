// FUNC_NAME: Transform::operator=
int __thiscall Transform::operator=(Transform &thisObj, Transform &sourceObj)
{
    // Copy base class data via helper (likely copies fields before this offset)
    FUN_00820830(&sourceObj);  // Function at 0x00820830 - probably copies base class members

    // Copy four 4-float vectors (rows of a 4x4 matrix or separate components)
    // Offsets: +0x50, +0x54, +0x58, +0x5c (row0)
    //         +0x80, +0x84, +0x88, +0x8c (row3)
    //         +0x60, +0x64, +0x68, +0x6c (row1)
    //         +0x70, +0x74, +0x78, +0x7c (row2)
    // The copy order is non-sequential, possibly due to alignment or cache optimization.

    // Copy first block (0x50-0x5c)
    float uVar1 = *(float *)(&sourceObj + 0x54);
    float uVar2 = *(float *)(&sourceObj + 0x58);
    float uVar3 = *(float *)(&sourceObj + 0x5c);
    *(float *)(&thisObj + 0x50) = *(float *)(&sourceObj + 0x50);
    *(float *)(&thisObj + 0x54) = uVar1;
    *(float *)(&thisObj + 0x58) = uVar2;
    *(float *)(&thisObj + 0x5c) = uVar3;

    // Copy second block (0x80-0x8c)
    uVar1 = *(float *)(&sourceObj + 0x84);
    uVar2 = *(float *)(&sourceObj + 0x88);
    uVar3 = *(float *)(&sourceObj + 0x8c);
    *(float *)(&thisObj + 0x80) = *(float *)(&sourceObj + 0x80);
    *(float *)(&thisObj + 0x84) = uVar1;
    *(float *)(&thisObj + 0x88) = uVar2;
    *(float *)(&thisObj + 0x8c) = uVar3;

    // Copy third block (0x60-0x6c)
    uVar1 = *(float *)(&sourceObj + 0x64);
    uVar2 = *(float *)(&sourceObj + 0x68);
    uVar3 = *(float *)(&sourceObj + 0x6c);
    *(float *)(&thisObj + 0x60) = *(float *)(&sourceObj + 0x60);
    *(float *)(&thisObj + 0x64) = uVar1;
    *(float *)(&thisObj + 0x68) = uVar2;
    *(float *)(&thisObj + 0x6c) = uVar3;

    // Copy fourth block (0x70-0x7c)
    uVar1 = *(float *)(&sourceObj + 0x74);
    uVar2 = *(float *)(&sourceObj + 0x78);
    uVar3 = *(float *)(&sourceObj + 0x7c);
    *(float *)(&thisObj + 0x70) = *(float *)(&sourceObj + 0x70);
    *(float *)(&thisObj + 0x74) = uVar1;
    *(float *)(&thisObj + 0x78) = uVar2;
    *(float *)(&thisObj + 0x7c) = uVar3;

    // Copy fifth block (0x90-0x9c) - another 4-float vector
    *(float *)(&thisObj + 0x90) = *(float *)(&sourceObj + 0x90);
    *(float *)(&thisObj + 0x9c) = *(float *)(&sourceObj + 0x9c);
    *(float *)(&thisObj + 0x94) = *(float *)(&sourceObj + 0x94);
    *(float *)(&thisObj + 0x98) = *(float *)(&sourceObj + 0x98);

    // Copy final two floats (0xa0, 0xa4) - possibly additional state (e.g., timestamp, mass)
    *(float *)(&thisObj + 0xa0) = *(float *)(&sourceObj + 0xa0);
    *(float *)(&thisObj + 0xa4) = *(float *)(&sourceObj + 0xa4);
    return (int)&thisObj;
}