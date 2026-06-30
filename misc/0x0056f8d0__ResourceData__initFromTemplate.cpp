// FUNC_NAME: ResourceData::initFromTemplate
bool __thiscall ResourceData::initFromTemplate(uint destSize, const ResourceTemplate* pTemplate) {
    void* pDest = this;
    uint uVar1 = g_nullResourceId; // DAT_00e2b1a4, likely a default/reserved value

    // Check if destination buffer is large enough for the header
    if (destSize < pTemplate->headerSize) {
        return false;
    }

    // Initialize header fields
    *(uint8*)((int)pDest + 2) = 1;          // flag byte
    *(uint*)pDest = 0;                       // type/flags?
    *(uint*)((int)pDest + 4) = 0;            // padding?
    *(uint8*)((int)pDest + 9) = 0;           // another flag
    *(uint16*)((int)pDest + 10) = pTemplate->headerSize;
    *(uint*)((int)pDest + 12) = *(uint*)((int)pTemplate + 12); // copy some 4-byte field
    // Zero out array fields
    *(uint*)((int)pDest + 24) = 0;            // field at offset +0x18? Actually in_EAX[6] is offset 0x18? Wait: int offset: in_EAX[6] = offset 0x18 (since each uint is 4 bytes). But earlier they set in_EAX[3] at offset 12, so in_EAX[4] at 16, in_EAX[5] at 20, in_EAX[6] at 24. Yes.
    *(uint*)((int)pDest + 20) = 0;            // field at +0x14
    *(uint*)((int)pDest + 16) = 0;            // field at +0x10
    *(uint*)((int)pDest + 28) = uVar1;        // field at +0x1C
    *(uint*)((int)pDest + 40) = 0;            // field at +0x28
    *(uint*)((int)pDest + 36) = 0;            // field at +0x24
    *(uint*)((int)pDest + 32) = 0;            // field at +0x20
    *(uint*)((int)pDest + 44) = uVar1;        // field at +0x2C
    // More flags/initializations
    *(uint8*)((int)pDest + 48) = 0;           // at +0x30 (in_EAX+0xc as byte)
    *(uint8*)((int)pDest + 49) = 0;           // at +0x31
    *(uint8*)((int)pDest + 50) = 0;           // at +0x32
    *(uint8*)((int)pDest + 51) = 0;           // at +0x33
    // Clear component pointers
    *(uint*)((int)pDest + 52) = 0;            // +0x34 (component1 pointer)
    *(uint*)((int)pDest + 56) = 0;            // +0x38
    *(uint*)((int)pDest + 60) = 0;            // +0x3C
    *(uint*)((int)pDest + 64) = 0;            // +0x40
    *(uint*)((int)pDest + 68) = 0;            // +0x44

    // Start of variable-length data area after header
    int writeOffset = (int)pDest + pTemplate->headerSize;
    int remaining = destSize - pTemplate->headerSize;

    // Copy optional component 1 (if present in template)
    if (pTemplate->component1 != nullptr) {
        bool (*copyComponent1)(int remaining) = (bool(*)(int))0x0056f080;
        if (!copyComponent1(remaining)) {
            return false;
        }
        *(uint*)((int)pDest + 52) = writeOffset; // store pointer to component data
        writeOffset += pTemplate->component1->size;
        remaining -= pTemplate->component1->size;
    }

    // Copy optional component 2
    if (pTemplate->component2 != nullptr) {
        bool (*copyComponent2)(int remaining) = (bool(*)(int))0x0056ed10;
        if (!copyComponent2(remaining)) {
            return false;
        }
        *(uint*)((int)pDest + 56) = writeOffset;
        writeOffset += pTemplate->component2->size;
        remaining -= pTemplate->component2->size;
    }

    // Copy optional component 3
    if (pTemplate->component3 != nullptr) {
        bool (*copyComponent3)(int remaining) = (bool(*)(int))0x005805f0;
        if (!copyComponent3(remaining)) {
            return false;
        }
        *(uint*)((int)pDest + 60) = writeOffset;
        writeOffset += pTemplate->component3->size;
        remaining -= pTemplate->component3->size;
    }

    // Copy optional component 4
    if (pTemplate->component4 != nullptr) {
        bool (*copyComponent4)(int remaining) = (bool(*)(int))0x00580960;
        if (!copyComponent4(remaining)) {
            return false;
        }
        *(uint*)((int)pDest + 64) = writeOffset;
        writeOffset += pTemplate->component4->size;
        remaining -= pTemplate->component4->size;
    }

    // Copy optional component 5
    if (pTemplate->component5 != nullptr) {
        bool (*copyComponent5)(int remaining) = (bool(*)(int))0x0056e900;
        if (!copyComponent5(remaining)) {
            return false;
        }
        *(uint*)((int)pDest + 68) = writeOffset;
        // Note: no update of writeOffset/remaining here because it's the last component
    }

    return true;
}