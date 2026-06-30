// FUNC_NAME: UISaveDataReader::readProperties
void __thiscall UISaveDataReader::readProperties(int this, void* stream)
{
    char flag; // +0x3c8 flag (loading state)
    int entry;

    UISaveDataReader::beginRead(stream); // FUN_0046c710
    flag = *(char*)(this + 0x3c8);
    if (flag != '\0') {
        *(char*)(this + 0x3c8) = 0;
        SubObject::reset(this + 100); // FUN_006aab90, sub-object at +100
    }
    UISaveDataReader::setChunkIdentifier(stream, 0x47e72b38); // FUN_0043aff0

    while (UISaveDataReader::hasMoreEntries(stream) == 0) { // FUN_0043b120
        UISaveDataReader::readNextEntry(stream); // FUN_0043b210
        int type = UISaveDataReader::getEntryType(stream); // FUN_0043ab70
        switch(type) {
        case 0: // integer property at +0x50
            entry = UISaveDataReader::readNextEntry(stream);
            *(int*)(this + 0x50) = *(int*)(entry + 8);
            break;
        case 1: // string property at +0x54
            UISaveDataReader::readNextEntry(stream);
            *(int*)(this + 0x54) = UISaveDataReader::getEntryString(stream); // FUN_004089b0 sets string
            break;
        case 2: // string property at +0x5c
            UISaveDataReader::readNextEntry(stream);
            *(int*)(this + 0x5c) = UISaveDataReader::getEntryString(stream);
            break;
        // Many cases from 3 to 0x29 call a generic string setter
        case 3:
        case 4:
        case 5:
        case 6:
        case 8:
        case 9:
        case 10:
        case 0xb:
        case 0xd:
        case 0xe:
        case 0xf:
        case 0x10:
        case 0x12:
        case 0x13:
        case 0x14:
        case 0x15:
        case 0x17:
        case 0x18:
        case 0x19:
        case 0x1a:
        case 0x1c:
        case 0x1d:
        case 0x1e:
        case 0x1f:
        case 0x21:
        case 0x22:
        case 0x23:
        case 0x24:
        case 0x26:
        case 0x27:
        case 0x28:
        case 0x29:
            UISaveDataReader::readNextEntry(stream);
            UISaveDataReader::setPropertyString(this, UISaveDataReader::getEntryString(stream)); // FUN_004d3d90
            break;
        case 7: // integer property at +0xc8 (200)
            entry = UISaveDataReader::readNextEntry(stream);
            *(int*)(this + 200) = *(int*)(entry + 8);
            break;
        case 0xc: // integer property at +0x134
            entry = UISaveDataReader::readNextEntry(stream);
            *(int*)(this + 0x134) = *(int*)(entry + 8);
            break;
        case 0x11: // integer property at +0x1a0
            entry = UISaveDataReader::readNextEntry(stream);
            *(int*)(this + 0x1a0) = *(int*)(entry + 8);
            break;
        case 0x16: // integer property at +0x20c
            entry = UISaveDataReader::readNextEntry(stream);
            *(int*)(this + 0x20c) = *(int*)(entry + 8);
            break;
        case 0x1b: // integer property at +0x278
            entry = UISaveDataReader::readNextEntry(stream);
            *(int*)(this + 0x278) = *(int*)(entry + 8);
            break;
        case 0x20: // integer property at +0x2e4
            entry = UISaveDataReader::readNextEntry(stream);
            *(int*)(this + 0x2e4) = *(int*)(entry + 8);
            break;
        case 0x25: // integer property at +0x350
            entry = UISaveDataReader::readNextEntry(stream);
            *(int*)(this + 0x350) = *(int*)(entry + 8);
            break;
        case 0x2a: // integer property at +0x3bc
            entry = UISaveDataReader::readNextEntry(stream);
            *(int*)(this + 0x3bc) = *(int*)(entry + 8);
            break;
        }
        UISaveDataReader::nextEntry(stream); // FUN_0043b1a0
    }

    if (flag == '\0') {
        // If not currently loading, and flag bit0 is set, copy global sprite data
        if ((*(byte*)(this + 0x50) & 1) != 0 && gSpriteData != 0) {
            UISaveDataReader::copyData((void*)(this + 0x3c), &gSpriteData, 0x8000); // FUN_00408900
        }
    } else {
        if (*(char*)(this + 0x3c8) == '\0') {
            *(char*)(this + 0x3c8) = 1;
            SubObject::restart(this + 100); // FUN_006aac90
        }
    }
}