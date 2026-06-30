// FUNC_NAME: DefinitionLoader::deserializeFromStream
void __thiscall DefinitionLoader::deserializeFromStream(int thisPtr, int streamHandle)
{
    char hasMore;
    int readType;
    int fieldPtr;
    float* floatPtr;
    float clampedVal;
    int* intPtr;
    int* vecPtr;

    // Stream reader initialization
    streamInit(streamHandle);
    streamReaderSetMagic(streamHandle, 0x8e19a048);
    hasMore = streamHasMoreFields(streamHandle);
    while (hasMore == '\0') {
        streamAdvanceToNextField(streamHandle);
        readType = streamReadFieldType(streamHandle);
        switch (readType) {
        case 0:
            // Child object deserialization
            fieldPtr = thisPtr + 0x58;  // +0x58: childObjectBuffer
            int childBuffer = fieldPtr;
            streamAdvanceToNextField(fieldPtr);
            streamReadChildObject(childBuffer);
            int childStream = streamReadSubstream(fieldPtr, 0);
            streamCreateObject(childStream, 0x38523fc3, &streamHandle);
            streamCloseObject(streamHandle);
            break;
        case 1:
            fieldPtr = streamReadFieldValue(streamHandle);
            *(int*)(thisPtr + 0xa0) = *(int*)(fieldPtr + 8); // +0xa0: fieldInt1
            break;
        case 2:
            fieldPtr = streamReadFieldValue(streamHandle);
            *(int*)(thisPtr + 0xa4) = *(int*)(fieldPtr + 8); // +0xa4: fieldInt2
            break;
        case 3:
            fieldPtr = streamReadFieldValue(streamHandle);
            *(int*)(thisPtr + 0xa8) = *(int*)(fieldPtr + 8); // +0xa8: fieldInt3
            break;
        case 4:
            fieldPtr = streamReadFieldValue(streamHandle);
            *(int*)(thisPtr + 0xac) = *(int*)(fieldPtr + 8); // +0xac: fieldInt4
            break;
        case 5:
            fieldPtr = streamReadFieldValue(streamHandle);
            *(int*)(thisPtr + 0xb0) = *(int*)(fieldPtr + 8); // +0xb0: fieldInt5
            break;
        case 6:
            fieldPtr = streamReadFieldValue(streamHandle);
            *(int*)(thisPtr + 0xb4) = *(int*)(fieldPtr + 8); // +0xb4: fieldInt6
            break;
        case 7:
            fieldPtr = streamReadFieldValue(streamHandle);
            *(int*)(thisPtr + 0xb8) = *(int*)(fieldPtr + 8); // +0xb8: fieldInt7
            break;
        case 8:
            fieldPtr = streamReadFieldValue(streamHandle);
            *(int*)(thisPtr + 0xbc) = *(int*)(fieldPtr + 8); // +0xbc: fieldInt8
            break;
        case 9:
            fieldPtr = streamReadFieldValue(streamHandle);
            *(int*)(thisPtr + 0xc0) = *(int*)(fieldPtr + 8); // +0xc0: fieldInt9
            break;
        case 10:
            fieldPtr = streamReadFieldValue(streamHandle);
            *(int*)(thisPtr + 0xc4) = *(int*)(fieldPtr + 8); // +0xc4: fieldInt10
            break;
        case 0xb:
            fieldPtr = streamReadFieldValue(streamHandle);
            *(int*)(thisPtr + 200) = *(int*)(fieldPtr + 8); // +0xc8: fieldInt11
            break;
        case 0xc:
            fieldPtr = streamReadFieldValue(streamHandle);
            *(float*)(thisPtr + 0xcc) = *(float*)(fieldPtr + 8) * DAT_00e445c8; // +0xcc: scaledFloat1
            break;
        case 0xd:
            fieldPtr = streamReadFieldValue(streamHandle);
            *(float*)(thisPtr + 0xd0) = *(float*)(fieldPtr + 8) * DAT_00e445c8; // +0xd0: scaledFloat2
            break;
        case 0xe:
            fieldPtr = streamReadFieldValue(streamHandle);
            *(float*)(thisPtr + 0xd4) = *(float*)(fieldPtr + 8) * DAT_00e445c8; // +0xd4: scaledFloat3
            break;
        case 0xf:
            fieldPtr = streamReadFieldValue(streamHandle);
            *(int*)(thisPtr + 0xd8) = *(int*)(fieldPtr + 8); // +0xd8: fieldInt12
            break;
        case 0x10:
            fieldPtr = streamReadFieldValue(streamHandle);
            *(int*)(thisPtr + 0xdc) = *(int*)(fieldPtr + 8); // +0xdc: fieldInt13
            break;
        case 0x11:
            fieldPtr = streamReadFieldValue(streamHandle);
            *(int*)(thisPtr + 0xe0) = *(int*)(fieldPtr + 8); // +0xe0: fieldInt14
            break;
        case 0x12:
            // Read Vector3
            streamReadFieldValue(streamHandle);
            vecPtr = (int*)streamReadRawData(streamHandle);
            *(int*)(thisPtr + 0xe4) = vecPtr[0]; // +0xe4: vector3.x
            *(int*)(thisPtr + 0xe8) = vecPtr[1]; // +0xe8: vector3.y
            *(int*)(thisPtr + 0xec) = vecPtr[2]; // +0xec: vector3.z
            break;
        case 0x13:
            fieldPtr = streamReadFieldValue(streamHandle);
            *(int*)(thisPtr + 0x68) = *(int*)(fieldPtr + 8); // +0x68: fieldInt15
            break;
        case 0x14:
            fieldPtr = streamReadFieldValue(streamHandle);
            *(int*)(thisPtr + 0x70) = *(int*)(fieldPtr + 8); // +0x70: fieldInt16
            break;
        case 0x15:
            fieldPtr = streamReadFieldValue(streamHandle);
            *(int*)(thisPtr + 0x6c) = *(int*)(fieldPtr + 8); // +0x6c: fieldInt17
            break;
        case 0x16:
            fieldPtr = streamReadFieldValue(streamHandle);
            *(int*)(thisPtr + 0x74) = *(int*)(fieldPtr + 8); // +0x74: fieldInt18
            break;
        case 0x17:
            fieldPtr = streamReadFieldValue(streamHandle);
            *(int*)(thisPtr + 0x78) = *(int*)(fieldPtr + 8); // +0x78: fieldInt19
            break;
        case 0x18:
            // Clamped float with min 0.0f and max DAT_00d5780c
            fieldPtr = streamReadFieldValue(streamHandle);
            clampedVal = 0.0f;
            if ((0.0f < *(float*)(fieldPtr + 8)) &&
                (fieldPtr = streamReadFieldValue(streamHandle), clampedVal = _DAT_00d5780c, *(float*)(fieldPtr + 8) < _DAT_00d5780c)) {
                fieldPtr = streamReadFieldValue(streamHandle);
                clampedVal = *(float*)(fieldPtr + 8);
            }
            *(float*)(thisPtr + 0x7c) = clampedVal; // +0x7c: clampedFloat1
            break;
        case 0x19:
            // Clamping with max DAT_00d5780c
            fieldPtr = streamReadFieldValue(streamHandle);
            clampedVal = _DAT_00d5780c;
            if (_DAT_00d5780c < *(float*)(fieldPtr + 8)) {
                fieldPtr = streamReadFieldValue(streamHandle);
                clampedVal = *(float*)(fieldPtr + 8);
            }
            *(float*)(thisPtr + 0x80) = clampedVal; // +0x80: clampedFloat2
            break;
        case 0x1a:
            // Clamped float with min 0.0f and max DAT_00d5780c
            fieldPtr = streamReadFieldValue(streamHandle);
            clampedVal = 0.0f;
            if ((0.0f < *(float*)(fieldPtr + 8)) &&
                (fieldPtr = streamReadFieldValue(streamHandle), clampedVal = _DAT_00d5780c, *(float*)(fieldPtr + 8) < _DAT_00d5780c)) {
                fieldPtr = streamReadFieldValue(streamHandle);
                clampedVal = *(float*)(fieldPtr + 8);
            }
            *(float*)(thisPtr + 0x84) = clampedVal; // +0x84: clampedFloat3
            break;
        case 0x1b:
            // Clamped integer: if value > 0.0f, read next as int
            fieldPtr = streamReadFieldValue(streamHandle);
            int clampedInt = 0;
            if (0.0f < *(float*)(fieldPtr + 8)) {
                fieldPtr = streamReadFieldValue(streamHandle);
                clampedInt = *(int*)(fieldPtr + 8);
            }
            *(int*)(thisPtr + 0x88) = clampedInt; // +0x88: clampedInt1
            break;
        case 0x1c:
            fieldPtr = streamReadFieldValue(streamHandle);
            int clampedInt2 = 0;
            if (0.0f < *(float*)(fieldPtr + 8)) {
                fieldPtr = streamReadFieldValue(streamHandle);
                clampedInt2 = *(int*)(fieldPtr + 8);
            }
            *(int*)(thisPtr + 0x8c) = clampedInt2; // +0x8c: clampedInt2
            break;
        }
        streamEndField(streamHandle);
        hasMore = streamHasMoreFields(streamHandle);
    }
    return;
}