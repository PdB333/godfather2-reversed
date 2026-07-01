// FUNC_NAME: Entity::readFromStream
void __thiscall Entity::readFromStream(int thisPtr, undefined4 stream)
{
    char isEnd;
    undefined4 propertyValue;
    int tagPtr;
    undefined8 transformData[6]; // Actually a struct of 12 floats, but we'll treat as raw
    undefined4 local_118;
    undefined4 local_114;
    undefined8 local_110;
    undefined4 local_108;
    undefined4 local_104;
    undefined8 local_100;
    undefined4 local_f8;
    undefined4 local_f4;
    undefined8 local_f0;
    undefined4 local_e8;
    undefined4 local_e4;

    // Begin reading the stream
    FUN_0043b540(stream);
    // Read a tag (0xb390b11a) - likely a transform marker
    FUN_0043aff0(stream, 0xb390b11a);
    // Read a boolean (1) - maybe "hasTransform"
    FUN_0043af00(1);
    isEnd = FUN_0043b120();
    if (isEnd == '\0') {
        // Read the transform data into local buffer
        transformData[0] = 0; // local_120
        local_118 = 0;
        local_114 = 0;
        local_104 = 0;
        local_f4 = 0;
        local_e4 = _DAT_00d5780c; // Some global constant
        FUN_0043b210(transformData); // Read tag for transform
        FUN_0043ac60(transformData); // Read transform data (matrix/quaternion)
        // Copy transform to object fields
        *(undefined8 *)(thisPtr + 0x100) = local_f0;
        *(undefined8 *)(thisPtr + 0xd0) = local_110;
        *(undefined8 *)(thisPtr + 0xc0) = transformData[0]; // local_120
        *(undefined4 *)(thisPtr + 0x108) = local_e8;
        *(undefined4 *)(thisPtr + 0xd8) = local_108;
        *(undefined8 *)(thisPtr + 0xe0) = local_100;
        *(undefined4 *)(thisPtr + 0xc8) = local_118; // 200 = 0xc8
        *(undefined4 *)(thisPtr + 0xe8) = local_f8;
        // Normalize or finalize transform
        FUN_0043a2a0(thisPtr + 0xc0, thisPtr + 0xc0);
    }
    // Read a tag (0x4307c0f5) - likely start of property list
    FUN_0043aff0(stream, 0x4307c0f5);
    isEnd = FUN_0043b120();
    do {
        if (isEnd != '\0') {
            // End of stream, finalize deserialization
            FUN_00810470(thisPtr);
            return;
        }
        // Read next property tag
        FUN_0043b210();
        int propertyType = FUN_0043ab70(); // Get property type ID
        switch(propertyType) {
        case 0:
            // Read float property at +0xa8
            FUN_0043b210();
            propertyValue = FUN_0043ab90();
            FUN_004089b0(thisPtr + 0xa8, propertyValue);
            break;
        case 1:
            // Read float property at +0xb0
            FUN_0043b210();
            propertyValue = FUN_0043ab90();
            FUN_00408980(thisPtr + 0xb0, propertyValue);
            break;
        case 2:
            // Read property at +0x58 (likely a sub-object)
            tagPtr = thisPtr + 0x58;
            goto LAB_0080faf4;
        case 3:
            // Read property at +0x68
            tagPtr = thisPtr + 0x68;
            FUN_0043b210(tagPtr);
            FUN_0043ad10(tagPtr);
            break;
        case 4:
            // Read property at +0x78
            tagPtr = thisPtr + 0x78;
            FUN_0043b210(tagPtr);
            FUN_0043ad10(tagPtr);
            break;
        case 5:
            // Read property at +0x88
            tagPtr = thisPtr + 0x88;
LAB_0080faf4:
            FUN_0043b210(tagPtr);
            FUN_0043ad10(tagPtr);
            break;
        case 6:
            // Read property at +0x98
            tagPtr = thisPtr + 0x98;
            FUN_0043b210(tagPtr);
            FUN_0043ad10(tagPtr);
            break;
        case 7:
            // Read integer property at +0x10c
            tagPtr = FUN_0043b210();
            *(undefined4 *)(thisPtr + 0x10c) = *(undefined4 *)(tagPtr + 8);
            break;
        case 8:
            // Read integer property at +0x110
            tagPtr = FUN_0043b210();
            *(undefined4 *)(thisPtr + 0x110) = *(undefined4 *)(tagPtr + 8);
            break;
        case 9:
            // Read integer property at +0x114
            tagPtr = FUN_0043b210();
            *(undefined4 *)(thisPtr + 0x114) = *(undefined4 *)(tagPtr + 8);
            break;
        case 10:
            // Read integer property at +0x54
            tagPtr = FUN_0043b210();
            *(undefined4 *)(thisPtr + 0x54) = *(undefined4 *)(tagPtr + 8);
        }
        // Advance stream to next property
        FUN_0043b1a0();
        isEnd = FUN_0043b120();
    } while( true );
}