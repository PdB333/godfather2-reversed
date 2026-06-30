// FUNC_NAME: PropertyBagReader::unpackProperties
// Address: 0x006da710
// This function reads a set of named properties from a binary stream into a struct (this).
// It appears to handle a string field (name) and several integer/float fields.
// Offsets: +0x54 (char name[64], 0x40 bytes), +0x93 (null terminator)
// +0x94, 0x98, 0x9c, 0xa0, 0xa4, 0xa8, 0xac, 0xb0, 0xb4 (int/float fields)

void __thiscall PropertyBagReader::unpackProperties(PropertyBagReader* this, Stream* stream)
{
    char hasMore;
    FieldType fieldType;
    int fieldDataPtr;
    char* sourceStr;
    int valuePtr;
    size_t count;

    beginReading(stream);                                    // FUN_00473dd0 - initialize stream reading
    readTypeCode(stream, 0xfbde1e5c);                       // FUN_0043aff0 - maybe validate header magic
    hasMore = hasMoreFields(stream);                         // FUN_0043b120 - check if more fields exist
    while (hasMore == '\0')
    {
        nextField(stream);                                   // FUN_0043b210 - advance to next field position
        fieldType = getFieldType(stream);                    // FUN_0043ab70 - read field type identifier
        switch (fieldType)
        {
        case 0: // String field (name)
            count = 0x40;                                    // Max 64 bytes
            nextField(stream);                               // FUN_0043b210 - read field value length? Actually used to get value pointer
            sourceStr = (char*)getFieldStringData(stream);   // FUN_0043ab90 - get pointer to string data
            strncpy((char*)(this + 0x54), sourceStr, count); // Copy to name buffer at offset 0x54
            *(char*)(this + 0x93) = '\0';                    // Ensure null termination at offset 0x93
            break;
        case 1: // Field at offset 0xb4
            valuePtr = nextField(stream);                    // FUN_0043b210 - read field header/pointer
            *(int*)(this + 0xb4) = *(int*)(valuePtr + 8);   // Copy value from data+8
            break;
        case 2: // Field at offset 0x94
            valuePtr = nextField(stream);
            *(int*)(this + 0x94) = *(int*)(valuePtr + 8);
            break;
        case 3: // Field at offset 0x98
            valuePtr = nextField(stream);
            *(int*)(this + 0x98) = *(int*)(valuePtr + 8);
            break;
        case 4: // Field at offset 0x9c
            valuePtr = nextField(stream);
            *(int*)(this + 0x9c) = *(int*)(valuePtr + 8);
            break;
        case 5: // Field at offset 0xa0
            valuePtr = nextField(stream);
            *(int*)(this + 0xa0) = *(int*)(valuePtr + 8);
            break;
        case 6: // Field at offset 0xa4
            valuePtr = nextField(stream);
            *(int*)(this + 0xa4) = *(int*)(valuePtr + 8);
            break;
        case 7: // Field at offset 0xa8
            valuePtr = nextField(stream);
            *(int*)(this + 0xa8) = *(int*)(valuePtr + 8);
            break;
        case 8: // Field at offset 0xac
            valuePtr = nextField(stream);
            *(int*)(this + 0xac) = *(int*)(valuePtr + 8);
            break;
        case 9: // Field at offset 0xb0
            valuePtr = nextField(stream);
            *(int*)(this + 0xb0) = *(int*)(valuePtr + 8);
            break;
        }
        advanceToNextField(stream);                          // FUN_0043b1a0 - finalize current field
        hasMore = hasMoreFields(stream);
    }
    return;
}