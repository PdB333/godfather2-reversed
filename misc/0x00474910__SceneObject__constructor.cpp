// FUNC_NAME: SceneObject::constructor
SceneObject* __thiscall SceneObject::constructor(SceneObject* thisObj, undefined4 parentArg) {
    undefined4 globalData1;
    undefined4 globalData2;

    // Call base class constructor
    BaseClass::constructor(parentArg); // FUN_0046c590

    // Set vtable pointer
    thisObj->vtable = &SceneObject_vtable; // +0x00

    // Initialize various pointers and fields
    thisObj->field_0x3C = &LAB_00e32bcc; // +0x3C
    thisObj->field_0x48 = &LAB_00e32bdc; // +0x48
    thisObj->field_0x50 = 0;            // +0x50
    *(short*)((int)thisObj + 0x54) = 0; // +0x54
    *(short*)((int)thisObj + 0x56) = 0; // +0x56
    thisObj->field_0x58 = 0;            // +0x58
    *(short*)((int)thisObj + 0x5C) = 0; // +0x5C
    *(short*)((int)thisObj + 0x5E) = 0; // +0x5E
    thisObj->field_0x60 = 0;            // +0x60
    *(short*)((int)thisObj + 0x64) = 0; // +0x64
    *(short*)((int)thisObj + 0x66) = 0; // +0x66
    thisObj->field_0x68 = 0;            // +0x68
    *(short*)((int)thisObj + 0x6C) = 0; // +0x6C
    *(short*)((int)thisObj + 0x6E) = 0; // +0x6E
    thisObj->field_0x70 = 0;            // +0x70
    *(short*)((int)thisObj + 0x74) = 0; // +0x74
    *(short*)((int)thisObj + 0x76) = 0; // +0x76

    // Save global value
    globalData1 = DAT_00e2b1a4;
    thisObj->field_0x78 = 0;            // +0x78
    *(short*)((int)thisObj + 0x7C) = 0; // +0x7C
    *(short*)((int)thisObj + 0x7E) = 0; // +0x7E
    globalData2 = DAT_0110ac04;

    // Initialize matrix/transform fields (4x4?)
    thisObj->matrix[0] = 0; // +0xC0
    thisObj->matrix[1] = 0; // +0xC4
    thisObj->matrix[2] = 0; // +0xC8
    thisObj->matrix[3] = 0; // +0xCC
    thisObj->matrix[4] = 0; // +0xD0

    // Debug guard: fill with magic numbers, then clear
    thisObj->guard1 = 0xbadbadba; // +0xD4
    thisObj->guard2 = 0xbeefbeef; // +0xD8
    thisObj->guard3 = 0xeac15a55; // +0xDC
    thisObj->guard4 = 0x91100911; // +0xE0
    thisObj->guard4 = 0;
    thisObj->guard3 = 0;
    thisObj->guard2 = 0;
    thisObj->guard1 = 0;

    // More fields after guards
    thisObj->field_0xF4 = 0; // +0xF4
    thisObj->field_0xF0 = 0; // +0xF0
    thisObj->field_0xEC = 0; // +0xEC
    thisObj->field_0xE4 = 0; // +0xE4
    thisObj->field_0xE8 = 0; // +0xE8

    // Initialize color/light arrays (4 entries, each 4 floats?)
    thisObj->colorA[0] = globalData1; // +0x80
    thisObj->colorA[1] = 0;           // +0x84
    thisObj->colorA[2] = 0;           // +0x88
    thisObj->colorA[3] = 0;           // +0x8C
    thisObj->colorA[4] = 0;           // +0x90
    thisObj->colorB[0] = globalData1; // +0x94
    thisObj->colorB[1] = 0;           // +0x98
    thisObj->colorB[2] = 0;           // +0x9C
    thisObj->colorB[3] = 0;           // +0xA0
    thisObj->colorB[4] = 0;           // +0xA4
    thisObj->colorC[0] = globalData1; // +0xA8
    thisObj->colorC[1] = 0;           // +0xAC
    thisObj->colorC[2] = 0;           // +0xB0
    thisObj->colorC[3] = 0;           // +0xB4
    thisObj->colorC[4] = 0;           // +0xB8
    thisObj->colorD[0] = globalData1; // +0xBC
    thisObj->colorD[1] = 0;           // +0xC0? careful: offset overlaps matrix? Actually matrix was at 0xC0. Need to verify offsets.

    // After color arrays, set another field from globalData2
    thisObj->field_0xF8 = globalData2; // +0xF8

    // Conditionally attach to global objects
    if (DAT_0120e944 != 0) {
        FUN_00407e60(&thisObj->field_0x3C, &DAT_0120e944);
    }
    if (DAT_0120e94c != 0) {
        FUN_00407e60(&thisObj->field_0x3C, &DAT_0120e94c);
    }

    return thisObj;
}