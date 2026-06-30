// FUNC_NAME: GameObject::deserializeFromStream
void __thiscall GameObject::deserializeFromStream(int* this, int streamContext)
{
    float floatVal;
    bool hasMoreData;
    int* matrixPtr;
    int tag;
    int result;
    const char* stringPtr;
    int fieldId;
    int value;

    // Read initial 4x4 matrix (likely transform) into fields at offsets 0x2AC-0x2B8
    matrixPtr = readStreamMatrix44(); // FUN_0043ab10
    this[0xab] = matrixPtr[0]; // +0x2AC
    this[0xac] = matrixPtr[1]; // +0x2B0
    this[0xad] = matrixPtr[2]; // +0x2B4
    this[0xae] = matrixPtr[3]; // +0x2B8

    // Start stream with a magic tag (0x4ecfbe13)
    streamBegin(streamContext, 0x4ecfbe13); // FUN_0043aff0

    hasMoreData = streamHasMoreData(); // FUN_0043b120
    while (!hasMoreData) {
        streamAdvanceToNextField(); // FUN_0043b210 – may read 4 bytes ahead
        fieldId = readFieldTag(); // FUN_0043ab70

        switch (fieldId) {
        case 0: // Load a string from field and convert to ID
            streamAdvanceToNextField();
            tag = readStreamInt32(); // FUN_0043ab90 – reads a tag/string?
            convertStringToHash(tag); // FUN_004d3d90
            stringPtr = (const char*)this[0x6e]; // +0x1B8
            if (stringPtr == NULL) {
                stringPtr = (const char*)0x0120546e; // default string address
            }
            result = resolveStringToId(stringPtr); // FUN_004dafd0
            this[0x72] = result; // +0x1C8
            break;

        case 1: // Read int and store at +0x1CC
            value = streamReadIntValue(); // FUN_0043b210 returns pointer? Actually does *(int *)(ret+8)
            this[0x73] = value; // +0x1CC
            break;

        case 2: // Read byte and store at +0x1A8? Actually param_1+0x6a = offset 0x1A8? Wait: param_1[0x6a] is a pointer, but they cast to undefined1? Let's treat as byte.
            value = streamReadIntValue();
            *(char*)(this + 0x6a) = (char)value; // +0x1A8? Actually param_1+0x6a is offset 0x1A8? No: param_1[0x6a] is at 0x6a*4 = 0x1A8, but they treat as byte? The decompiled shows *(undefined1 *)(param_1 + 0x6a) so it's byte at address&this[0x6a]? Actually param_1 is int*, so &this[0x6a] = (int*)this + 0x6a = address of int at offset 0x1A8. But then cast to undefined1* so it's a byte at that address. So it's overwriting the first byte of that int. This might be a bug in decompilation – maybe it's actually *(byte*)(this + 0x1A8) but param_1+0x6a is int*? I'll keep as byte assignment.
            *(char*)(this + 0x6a) = (char)value; // offset 0x1A8? Wait: 0x6a*4 = 0x1A8. So this is byte at 0x1A8.
            break;

        case 3: // Call a virtual function with a string parameter
            value = streamReadIntValue();
            // vtable entry at 0x18c (virtual function #0x63 = 99?)
            (this->vtable[0x18c])((const char*)value); // (*(code **)(*this + 0x18c))(value);
            break;

        case 4: // Read int and store at +0x294? 0xa5*4 = 0x294
            value = streamReadIntValue();
            this[0xa5] = value; // +0x294
            break;

        case 5: // Set a flag (bit 0x800) at +0x1D0? 0x74*4 = 0x1D0
            value = streamReadIntValue();
            if (value == 0) {
                this[0x74] &= 0xFFFFF7FF; // Clear bit 11
            } else {
                this[0x74] |= 0x800; // Set bit 11
            }
            break;

        case 6: // Byte at +0x1A9
            value = streamReadIntValue();
            *(char*)((int)this + 0x1A9) = (char)value; // offset 0x1A9
            break;

        case 7: // Byte at +0x1AA
            value = streamReadIntValue();
            *(char*)((int)this + 0x1AA) = (char)value;
            break;

        case 8: // Byte at +0x1AB
            value = streamReadIntValue();
            *(char*)((int)this + 0x1AB) = (char)value;
            break;

        case 9: // Set flag bit 4 at +0x1D0
            value = streamReadIntValue();
            if (value == 0) {
                this[0x74] &= 0xFFFFFFEF; // Clear bit 4
            } else {
                this[0x74] |= 0x10; // Set bit 4
            }
            break;

        case 10: // Set flag bit 5
            value = streamReadIntValue();
            if (value == 0) {
                this[0x74] &= 0xFFFFFFDF;
            } else {
                this[0x74] |= 0x20;
            }
            break;

        case 0xB: // Set flag bit 3
            value = streamReadIntValue();
            if (value == 0) {
                this[0x74] &= 0xFFFFFFF7;
            } else {
                this[0x74] |= 0x8;
            }
            break;

        case 0xC: // Set flag bit 2
            value = streamReadIntValue();
            if (value == 0) {
                this[0x74] &= 0xFFFFFFFB;
            } else {
                this[0x74] |= 0x4;
            }
            break;

        case 0xD: // Set flag bit 1
            value = streamReadIntValue();
            if (value == 0) {
                this[0x74] &= 0xFFFFFFFD;
            } else {
                this[0x74] |= 0x2;
            }
            break;

        case 0xE: // Copy string to offset +0x298? 0xa6*4 = 0x298
            streamAdvanceToNextField();
            tag = readStreamInt32();
            copyString(this + 0xa6, tag); // FUN_00408980 – string copy
            break;

        case 0xF: // Copy string to offset +0x2A0? 0xa8*4 = 0x2A0
            streamAdvanceToNextField();
            tag = readStreamInt32();
            copyString(this + 0xa8, tag);
            break;

        case 0x10: // Read int and store at +0x1D8? 0x76*4 = 0x1D8
            value = streamReadIntValue();
            this[0x76] = value;
            break;

        case 0x11: // Read int at +0x1DC
            value = streamReadIntValue();
            this[0x77] = value;
            break;

        case 0x12: // Read float, clamp to int, store at +0x2A8? 0xaa*4 = 0x2A8
            floatVal = streamReadFloat(); // Actually *(float*)(iVar5+8)
            value = (int)floatVal;
            if (floatVal < 0.0f) {
                value = 0;
            }
            this[0xaa] = value; // +0x2A8
            break;

        case 0x13: // Read 4x4 matrix to offsets +0x220..0x22C? 0x88*4 = 0x220
            streamAdvanceToNextField();
            matrixPtr = readStreamMatrix44(); // FUN_0043abc0
            this[0x88] = matrixPtr[0];
            this[0x89] = matrixPtr[1];
            this[0x8a] = matrixPtr[2];
            this[0x8b] = matrixPtr[3];
            break;

        case 0x14: // Read matrix to +0x234..0x240? 0x8d*4 = 0x234
            streamAdvanceToNextField();
            matrixPtr = readStreamMatrix44();
            this[0x8d] = matrixPtr[0];
            this[0x8e] = matrixPtr[1];
            this[0x8f] = matrixPtr[2];
            this[0x90] = matrixPtr[3];
            break;

        case 0x15: // Read matrix to +0x244..0x250? 0x91*4 = 0x244
            streamAdvanceToNextField();
            matrixPtr = readStreamMatrix44();
            this[0x91] = matrixPtr[0];
            this[0x92] = matrixPtr[1];
            this[0x93] = matrixPtr[2];
            this[0x94] = matrixPtr[3];
            break;

        case 0x16: // Read int at +0x26C? 0x9b*4 = 0x26C
            value = streamReadIntValue();
            this[0x9b] = value;
            break;

        case 0x17: // Read matrix to +0x258..0x264? 0x96*4 = 0x258
            streamAdvanceToNextField();
            matrixPtr = readStreamMatrix44();
            this[0x96] = matrixPtr[0];
            this[0x97] = matrixPtr[1];
            this[0x98] = matrixPtr[2];
            this[0x99] = matrixPtr[3];
            break;

        case 0x18: // Read matrix to +0x280..0x28C? 0xa0*4 = 0x280
            streamAdvanceToNextField();
            matrixPtr = readStreamMatrix44();
            this[0xa0] = matrixPtr[0];
            this[0xa1] = matrixPtr[1];
            this[0xa2] = matrixPtr[2];
            this[0xa3] = matrixPtr[3];
            break;

        case 0x19: // Read something into offsets +0x188? 0x62*4 = 0x188
            value = streamReadInt(&this[0x62]); // FUN_0043b210 with pointer
            readStreamDataBlock(&this[0x62]); // FUN_0043ad10
            break;

        case 0x1A: // Similar at +0x198? 0x66*4 = 0x198
            value = streamReadInt(&this[0x66]);
            readStreamDataBlock(&this[0x66]);
            break;

        case 0x1B: // Read matrix, possibly create an object
            streamAdvanceToNextField();
            matrixPtr = readStreamMatrix44();
            // Check if matrix is non-zero and if an object doesn't already exist
            if ((matrixPtr[0] != 0 || matrixPtr[1] != 0 || matrixPtr[2] != 0 || matrixPtr[3] != 0) &&
                !isObjectPlaceholder()) {
                result = createObjectFromMatrix(matrixPtr); // FUN_004211e0
                this[0x6d] = result; // +0x1B4
            }
            break;

        case 0x1D: // Byte at +0x1AC? param_1+0x6b = offset 0x1AC? Actually 0x6b*4 = 0x1AC, but they write byte.
            value = streamReadIntValue();
            *(char*)(this + 0x6b) = (char)value;
            break;

        case 0x1E: // Write short at +0x1D4? param_1+0x75 = offset 0x1D4, but they cast to undefined2 (short).
            value = streamReadIntValue();
            *(short*)(this + 0x75) = (short)value;
            break;

        case 0x1F: // Another string conversion like case 0
            streamAdvanceToNextField();
            tag = readStreamInt32();
            convertStringToHash(tag);
            break;
        }

        streamNextField(); // FUN_0043b1a0 – advance to next field
        hasMoreData = streamHasMoreData();
    }

    finalizeDeserialization(); // FUN_00472460
    // Call virtual function at vtable+0x14 (probably OnDeserialized)
    (this->vtable[0x14])(); // (**(code **)(*this + 0x14))();
}