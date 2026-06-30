// FUNC_NAME: ItemDefinition::loadFromStream
void __thiscall ItemDefinition::loadFromStream(int thisPtr, int streamPtr)
{
    // +0x70: flags (bit0=useDefaultTexture?)
    // +0x50: string1 (name?)
    // +0x58: string2 (description?)
    // +0x60: string3 (model?)
    // +0x68: string4 (icon?)
    // +0x74-0x80: 128-bit GUID1 (item ID?)
    // +0x8c-0x98: 128-bit GUID2 (parent ID?)
    // +0x84, +0x9c: version (same)
    // +0xa4-0xc0: 8 ints (stats array, e.g., damage, rate)

    int defaultVersion = 0; // from tag type 0xf
    bool done = false;

    stream_beginRead(streamPtr); // FUN_0046c710
    stream_setResourceId(streamPtr, 0x100351e6); // FUN_0043aff0
    while (!stream_isEnd(streamPtr)) // FUN_0043b120
    {
        stream_advanceToNextTag(streamPtr); // FUN_0043b210
        int tagType = stream_getTagType(streamPtr); // FUN_0043ab70
        switch (tagType)
        {
        case 0: // tag type 0: flag field
        {
            int data = stream_readIntData(streamPtr); // FUN_0043b210 -> index, then read +8
            *(int*)(thisPtr + 0x70) = *(int*)(data + 8); // assign flags
            break;
        }
        case 1: // tag type 1: name string
        {
            stream_advanceToNextTag(streamPtr); // skip? (already advanced? actually this read data before, but logic: call advance, then read string)
            const char* name = stream_readString(streamPtr); // FUN_0043ab90
            stringCopy(thisPtr + 0x50, name); // FUN_004089b0
            break;
        }
        case 2: // tag type 2: description string
        {
            stream_advanceToNextTag(streamPtr);
            const char* desc = stream_readString(streamPtr);
            stringCopy(thisPtr + 0x58, desc);
            break;
        }
        case 3: // tag type 3: some int at +0xa4
        {
            int data = stream_readIntData(streamPtr);
            *(int*)(thisPtr + 0xa4) = *(int*)(data + 8);
            break;
        }
        case 4: // tag type 4: some int at +0xa8
        {
            int data = stream_readIntData(streamPtr);
            *(int*)(thisPtr + 0xa8) = *(int*)(data + 8);
            break;
        }
        case 5: // tag type 5: some int at +0xac
        {
            int data = stream_readIntData(streamPtr);
            *(int*)(thisPtr + 0xac) = *(int*)(data + 8);
            break;
        }
        case 6: // tag type 6: some int at +0xb0
        {
            int data = stream_readIntData(streamPtr);
            *(int*)(thisPtr + 0xb0) = *(int*)(data + 8);
            break;
        }
        case 7: // tag type 7: some int at +0xb4
        {
            int data = stream_readIntData(streamPtr);
            *(int*)(thisPtr + 0xb4) = *(int*)(data + 8);
            break;
        }
        case 8: // tag type 8: some int at +0xb8
        {
            int data = stream_readIntData(streamPtr);
            *(int*)(thisPtr + 0xb8) = *(int*)(data + 8);
            break;
        }
        case 9: // tag type 9: some int at +0xbc
        {
            int data = stream_readIntData(streamPtr);
            *(int*)(thisPtr + 0xbc) = *(int*)(data + 8);
            break;
        }
        case 10: // tag type 10: some int at +0xc0
        {
            int data = stream_readIntData(streamPtr);
            *(int*)(thisPtr + 0xc0) = *(int*)(data + 8);
            break;
        }
        case 0xb: // tag type 11: 128-bit GUID1
        {
            stream_advanceToNextTag(streamPtr);
            int* guid = stream_readGUID(streamPtr); // returns 4 ints
            if (guid[0] != 0 || guid[1] != 0 || guid[2] != 0 || guid[3] != 0)
            {
                *(int*)(thisPtr + 0x74) = guid[0];
                *(int*)(thisPtr + 0x78) = guid[1];
                *(int*)(thisPtr + 0x7c) = guid[2];
                *(int*)(thisPtr + 0x80) = guid[3];
            }
            break;
        }
        case 0xc: // tag type 12: 128-bit GUID2
        {
            stream_advanceToNextTag(streamPtr);
            int* guid = stream_readGUID(streamPtr);
            if (guid[0] != 0 || guid[1] != 0 || guid[2] != 0 || guid[3] != 0)
            {
                *(int*)(thisPtr + 0x8c) = guid[0];
                *(int*)(thisPtr + 0x90) = guid[1];
                *(int*)(thisPtr + 0x94) = guid[2];
                *(int*)(thisPtr + 0x98) = guid[3];
            }
            break;
        }
        case 0xd: // tag type 13: model string
        {
            stream_advanceToNextTag(streamPtr);
            const char* model = stream_readString(streamPtr);
            stringCopy(thisPtr + 0x60, model);
            break;
        }
        case 0xe: // tag type 14: icon string
        {
            stream_advanceToNextTag(streamPtr);
            const char* icon = stream_readString(streamPtr);
            stringCopy(thisPtr + 0x68, icon);
            break;
        }
        case 0xf: // tag type 15: version
        {
            int data = stream_readIntData(streamPtr);
            defaultVersion = *(int*)(data + 8);
            break;
        }
        case 0x10: // tag type 16: version (same as type 15 but also sets +0x84 and +0x9c)
        {
            int data = stream_readIntData(streamPtr);
            int version = *(int*)(data + 8);
            *(int*)(thisPtr + 0x84) = version;
            *(int*)(thisPtr + 0x9c) = version;
            break;
        }
        }
        stream_endTag(streamPtr); // FUN_0043b1a0
    } // end while

    // Fallback: if version not set by tag 0x10, use value from tag 0xf (if present)
    if (*(int*)(thisPtr + 0x9c) == 0)
    {
        int resolvedVersion = resolveDefaultVersion(defaultVersion); // thunk_FUN_0042a9a0
        *(int*)(thisPtr + 0x84) = resolvedVersion;
        *(int*)(thisPtr + 0x9c) = resolvedVersion;
    }

    // Copy default texture/model if flagged and global exists
    if ((*(byte*)(thisPtr + 0x70) & 1) != 0 && gDefaultTextureModel != 0)
    {
        stringCopy(thisPtr + 0x3c, gDefaultTextureModel, 0x8000); // FUN_00408900
    }
}