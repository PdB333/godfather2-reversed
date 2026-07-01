// FUNC_NAME: GameObject::loadFromDataStream
void __thiscall GameObject::loadFromDataStream(void* this, uint dataHandle) {
    uint tokenType;
    int* tokenData;
    int boolFlag;

    FUN_008d8680(dataHandle); // InitializeStream
    FUN_0043aff0(dataHandle, 0x346d561a); // ChunkID check

    while (!FUN_0043b120()) { // HasMoreData
        FUN_0043b210(); // AdvanceToNextToken
        tokenType = FUN_0043ab70(); // GetTokenType

        switch (tokenType) {
        case 0: // integer field 1 (offset +0x1B8)
            FUN_0043b210();
            tokenData = FUN_0043ab90(); // ReadIntValue
            FUN_004089b0(this + 0x6e, tokenData); // SetIntField
            break;
        case 1: // integer field 2 (offset +0x1C0)
            FUN_0043b210();
            tokenData = FUN_0043ab90();
            FUN_004089b0(this + 0x70, tokenData);
            break;
        case 2: // float field 1 (offset +0x1C8)
            FUN_0043b210();
            tokenData = FUN_0043ab90();
            FUN_00408980(this + 0x72, tokenData); // SetFloatField
            break;
        case 3: // float field 2 (offset +0x1D0)
            FUN_0043b210();
            tokenData = FUN_0043ab90();
            FUN_00408980(this + 0x74, tokenData);
            break;
        case 4: // float field 3 (offset +0x1D8)
            FUN_0043b210();
            tokenData = FUN_0043ab90();
            FUN_00408980(this + 0x76, tokenData);
            break;
        case 5: // boolean flag (offset +0x1A4, bit 0)
            boolFlag = FUN_0043b210();
            if (*(int*)(boolFlag + 8) == 0) {
                ((int*)this)[0x69] &= 0xfffffffe;
            } else {
                ((int*)this)[0x69] |= 1;
            }
            break;
        case 6: // int field at +0x1A8
            boolFlag = FUN_0043b210();
            ((int*)this)[0x6a] = *(int*)(boolFlag + 8);
            break;
        case 7: // int field at +0x1AC
            boolFlag = FUN_0043b210();
            ((int*)this)[0x6b] = *(int*)(boolFlag + 8);
            break;
        case 8: // int field at +0x1B0
            boolFlag = FUN_0043b210();
            ((int*)this)[0x6c] = *(int*)(boolFlag + 8);
            break;
        case 9: // float field with scale (offset +0x1B4)
            boolFlag = FUN_0043b210();
            ((int*)this)[0x6d] = (int)(*(float*)(boolFlag + 8) * DAT_00e445c8);
            break;
        case 10: // vector4 (offsets +0x190 to +0x19C)
            FUN_0043b210();
            tokenData = (int*)FUN_0043abc0(); // ReadVec4Data
            ((int*)this)[100] = tokenData[0];
            ((int*)this)[0x65] = tokenData[1];
            ((int*)this)[0x66] = tokenData[2];
            ((int*)this)[0x67] = tokenData[3];
            break;
        }
        FUN_0043b1a0(); // EndOfToken
    }

    // Virtual method calls for post-load processing
    if (((code**)this)[0x14c / 4]()) { // vtable+0x14c -> PostLoadCheck
        FUN_008da330(); // PostLoadFunction1
        FUN_008da6d0(); // PostLoadFunction2
    }
}