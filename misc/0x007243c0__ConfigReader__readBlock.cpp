// FUNC_NAME: ConfigReader::readBlock
void ConfigReader::readBlock(ConfigReader* this) {
    char hasMore;
    uint32_t typeTag;
    int32_t ptr;
    int32_t ptr2;
    float floatVal;
    int32_t basePtr;
    uint32_t index;
    undefined4 local_78;
    undefined4 local_74;

    local_74 = DAT_00e445ac; // global initial value
    local_78 = DAT_00d5779c; // global initial value

    // Initialize stream reading
    beginRead(this); // FUN_0046f160
    readChunkHeader(this, 0x4e98dfba); // FUN_0043aff0 - likely a fourCC or ID

    hasMore = hasMoreData(this); // FUN_0043b120
    while (hasMore == 0) {
        advanceRead(this); // FUN_0043b210 - read length/pointer?
        typeTag = readTypeTag(this); // FUN_0043ab70

        switch(typeTag) {
            // Even types 0..0x18: store into DAT_0112acac array
            case 0:
            case 2:
            case 4:
            case 6:
            case 8:
            case 10:
            case 0xc:
            case 0xe:
            case 0x10:
            case 0x12:
            case 0x14:
            case 0x16:
            case 0x18:
                ptr = readPointerValue(this); // FUN_0043b210 - read some structure pointer? Then dereference offset 8
                typeTag = *(undefined4*)(ptr + 8); // value from struct
                advanceRead(this); // FUN_0043b210
                index = readTypeTag(this); // FUN_0043ab70
                g_ArrayA[index & 0xfffffffe] = typeTag; // DAT_0112acac
                break;

            // Odd types 1..0x19: store into DAT_0112aca8 array
            case 1:
            case 3:
            case 5:
            case 7:
            case 9:
            case 0xb:
            case 0xd:
            case 0xf:
            case 0x11:
            case 0x13:
            case 0x15:
            case 0x17:
            case 0x19:
                ptr = readPointerValue(this); // FUN_0043b210
                typeTag = *(undefined4*)(ptr + 8);
                advanceRead(this);
                index = readTypeTag(this);
                g_ArrayB[index & 0xfffffffe] = typeTag; // DAT_0112aca8
                break;

            // Types 0x1a..0x26: store into array relative to g_BasePtr
            case 0x1a:
            case 0x1b:
            case 0x1c:
            case 0x1d:
            case 0x1e:
            case 0x1f:
            case 0x20:
            case 0x21:
            case 0x22:
            case 0x23:
            case 0x24:
            case 0x25:
            case 0x26:
                ptr = readPointerValue(this); // FUN_0043b210
                basePtr = DAT_0112ad5c; // global base pointer
                typeTag = *(undefined4*)(ptr + 8);
                advanceRead(this);
                index = readTypeTag(this);
                *(undefined4*)(basePtr - 0x44 + index * 4) = typeTag; // array of ints offset from base
                break;

            case 0x27:
                ptr = readPointerValue(this);
                _DAT_00e51764 = *(float*)(ptr + 8);
                if (_DAT_00e51764 < DAT_00d5ef84) {
                    _DAT_00e51764 = DAT_00d5ef84;
                }
                break;

            case 0x28:
                ptr = readPointerValue(this);
                local_74 = *(undefined4*)(ptr + 8);
                break;

            case 0x29:
                ptr = readPointerValue(this);
                local_78 = *(undefined4*)(ptr + 8);
                break;
        }

        advanceNext(this); // FUN_0043b1a0
        hasMore = hasMoreData(this);
    }

    finalizeConfig(local_74, local_78); // FUN_00768f80
    return;
}