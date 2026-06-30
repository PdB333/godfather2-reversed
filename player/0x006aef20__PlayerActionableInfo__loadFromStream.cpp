// FUNC_NAME: PlayerActionableInfo::loadFromStream
void __thiscall PlayerActionableInfo::loadFromStream(int thisPtr, void* stream)
{
    char isEnd;
    int typeId;
    int intVal;
    int* vec4Ptr;
    char* strVal;

    FUN_0046f160(stream); // possibly open/validate stream
    FUN_0043aff0(stream, 0x6f1d0554); // check magic number

    isEnd = FUN_0043b120(); // check end of stream
    while (isEnd == 0) {
        FUN_0043b210(); // read token/advance
        typeId = FUN_0043ab70(); // read entry type

        switch (typeId) {
        case 0: // property 0: integer
            intVal = FUN_0043b210(); // read int32
            *(int*)(thisPtr + 0x184) = *(int*)(intVal + 8); // likely a mapped value
            break;
        case 0xe: // 14
            intVal = FUN_0043b210();
            *(int*)(thisPtr + 0x190) = *(int*)(intVal + 8);
            break;
        case 0xf: // 15
            intVal = FUN_0043b210();
            *(int*)(thisPtr + 0x194) = *(int*)(intVal + 8);
            break;
        case 0x11: // 17
        case 0x12: // 18
        case 0x13: // 19
        case 0x14: // 20
            FUN_0043b210(); // read token
            vec4Ptr = (int*)FUN_0043abc0(); // read Vec4
            if ((((*vec4Ptr != 0) || (vec4Ptr[1] != 0)) || (vec4Ptr[2] != 0)) || (vec4Ptr[3] != 0)) {
                int context = *(int*)(thisPtr + 0x1c);
                // call to set color property
                if (FUN_006aee40(context, *(int*)vec4Ptr) == 0) {
                    // failure fallback
                    int fallbackKey = FUN_0043ab10();
                    FUN_006b6c10(vec4Ptr, fallbackKey);
                }
            }
            break;
        case 0x15: // 21
            FUN_0043b210();
            strVal = FUN_0043ab90(); // read string
            FUN_004089b0(thisPtr + 0x244, strVal); // copy string to field
            break;
        case 0x16: // 22
            FUN_0043b210();
            strVal = FUN_0043ab90();
            FUN_004089b0(thisPtr + 0x24c, strVal);
            break;
        case 0x17: // 23
            FUN_0043b210();
            strVal = FUN_0043ab90();
            FUN_004089b0(thisPtr + 0x23c, strVal);
            break;
        case 0x18: // 24
            FUN_0043b210();
            strVal = FUN_0043ab90();
            FUN_004089b0(thisPtr + 0x25c, strVal);
            break;
        case 0x19: // 25
            FUN_0043b210();
            strVal = FUN_0043ab90();
            FUN_00408980(thisPtr + 0x254, strVal); // assign string with different method
            break;
        case 0x1a: // 26
            FUN_0043b210();
            strVal = FUN_0043ab90();
            FUN_004089b0(thisPtr + 0x2ac, strVal);
            break;
        case 0x1b: // 27
            FUN_0043b210();
            strVal = FUN_0043ab90();
            FUN_00408980(thisPtr + 0x26c, strVal);
            break;
        case 0x1c: // 28
            FUN_0043b210();
            strVal = FUN_0043ab90();
            FUN_00408980(thisPtr + 0x274, strVal);
            break;
        case 0x1d: // 29
            FUN_0043b210();
            strVal = FUN_0043ab90();
            FUN_00408980(thisPtr + 0x27c, strVal);
            break;
        case 0x1e: // 30
            FUN_0043b210();
            strVal = FUN_0043ab90();
            FUN_00408980(thisPtr + 0x284, strVal);
            break;
        case 0x1f: // 31
            FUN_0043b210();
            strVal = FUN_0043ab90();
            FUN_004089b0(thisPtr + 0x28c, strVal);
            break;
        case 0x20: // 32
            FUN_0043b210();
            strVal = FUN_0043ab90();
            FUN_004089b0(thisPtr + 0x294, strVal);
            break;
        case 0x21: // 33
            FUN_0043b210();
            strVal = FUN_0043ab90();
            FUN_00408980(thisPtr + 0x29c, strVal);
            break;
        case 0x22: // 34
            FUN_0043b210();
            strVal = FUN_0043ab90();
            FUN_00408980(thisPtr + 0x2a4, strVal);
            break;
        case 0x23: // 35
            intVal = FUN_0043b210();
            *(int*)(thisPtr + 0x264) = *(int*)(intVal + 8);
            break;
        case 0x24: // 36
            intVal = FUN_0043b210();
            *(int*)(thisPtr + 0x268) = *(int*)(intVal + 8);
            break;
        case 0x25: // 37
            intVal = FUN_0043b210();
            *(int*)(thisPtr + 0x1d8) = *(int*)(intVal + 8);
            break;
        case 0x26: // 38
            FUN_0043b210();
            strVal = FUN_0043ab90();
            FUN_00408980(thisPtr + 0x1dc, strVal);
            break;
        }
        FUN_0043b1a0(); // advance to next entry
        isEnd = FUN_0043b120();
    }
    return;
}