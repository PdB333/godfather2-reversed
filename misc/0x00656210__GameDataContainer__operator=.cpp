// FUNC_NAME: GameDataContainer::operator=

// Structure with 20-byte elements stored in a dynamic array.
// Object size is at least 0x69 bytes (105 bytes).
// Offsets based on analysis of copy assignment.
struct GameDataContainer
{
    // Offsets 0x00-0x01F: first 32 bytes of raw data, copied as-is.
    // Contains 3 bytes + 7*4 bytes = 31 bytes? Actually:
    // byte[0], byte[1], byte[2]; then uint at 0x03,0x07,0x0b,0x0f,0x14,0x18,0x1c
    uint8_t rawHeader[0x20];

    // +0x20: pointer to refcounted object A
    int* refPtrA;
    // +0x24: pointer to refcounted object B
    int* refPtrB;
    // +0x28: pointer to refcounted object C
    int* refPtrC;
    // +0x2C: pointer to refcounted object D
    int* refPtrD;

    // +0x30: byte flag1
    uint8_t flag1;
    // +0x31: byte flag2
    uint8_t flag2;

    // +0x32: first 16-byte GUID
    uint8_t guid1[16];
    // +0x42: second 16-byte GUID
    uint8_t guid2[16];

    // +0x54: number of elements in the dynamic array
    int elementCount;
    // +0x58: capacity of element array (rounded up to multiple of 16)
    int elementCapacity;
    // +0x5C: pointer to array of Element20 structures
    int* elementData; // actually pointer to Element20

    // +0x60: byte flag3
    uint8_t flag3;
    // +0x61: byte flag4
    uint8_t flag4;

    // +0x64 (100 decimal): pointer to refcounted object E
    int* refPtrE;

    // +0x68: byte flag5
    uint8_t flag5;
};

// A 20-byte (0x14) element in the array
struct Element20
{
    uint8_t data[0x14];
};

// External globals (from decompilation)
extern int _DAT_01205a30; // tracks total allocated element count
extern int* PTR__malloc_00f0cd88;
extern int* PTR__free_00f0cd8c;

// Copy assignment operator for GameDataContainer
void __thiscall GameDataContainer::operator=(const GameDataContainer& src)
{
    // 1. Copy the raw header block (offsets 0x00-0x1F)
    rawHeader[0] = src.rawHeader[0];
    rawHeader[1] = src.rawHeader[1];
    rawHeader[2] = src.rawHeader[2];
    *(uint32_t*)(rawHeader + 0x03) = *(uint32_t*)(src.rawHeader + 0x03);
    *(uint32_t*)(rawHeader + 0x07) = *(uint32_t*)(src.rawHeader + 0x07);
    *(uint32_t*)(rawHeader + 0x0B) = *(uint32_t*)(src.rawHeader + 0x0B);
    *(uint32_t*)(rawHeader + 0x0F) = *(uint32_t*)(src.rawHeader + 0x0F);
    *(uint32_t*)(rawHeader + 0x14) = *(uint32_t*)(src.rawHeader + 0x14);
    *(uint32_t*)(rawHeader + 0x18) = *(uint32_t*)(src.rawHeader + 0x18);
    *(uint32_t*)(rawHeader + 0x1C) = *(uint32_t*)(src.rawHeader + 0x1C);

    // 2. Handle refcounted pointer at +0x20
    if (refPtrA)
    {
        int* refcount = refPtrA + 2; // refcount at offset 8? Actually +8 bytes from pointer base
        (*refcount)--;
        if (*refcount == 0)
        {
            // Call destructor via vtable at offset 8
            (*(void (**)(void))(*refPtrA + 8))();
        }
    }
    refPtrA = src.refPtrA;
    if (refPtrA)
        *(int*)(refPtrA + 2) += 1; // increment refcount

    // 3. Handle refcounted pointer at +0x24
    if (refPtrB)
    {
        int* refcount = refPtrB + 2;
        (*refcount)--;
        if (*refcount == 0)
            (*(void (**)(void))(*refPtrB + 8))();
    }
    refPtrB = src.refPtrB;
    if (refPtrB)
        *(int*)(refPtrB + 2) += 1;

    // 4. Handle refcounted pointer at +0x28
    if (refPtrC)
    {
        int* refcount = refPtrC + 2;
        (*refcount)--;
        if (*refcount == 0)
            (*(void (**)(void))(*refPtrC + 8))();
    }
    refPtrC = src.refPtrC;
    if (refPtrC)
        *(int*)(refPtrC + 2) += 1;

    // 5. Handle refcounted pointer at +0x2C
    if (refPtrD)
    {
        int* refcount = refPtrD + 2;
        (*refcount)--;
        if (*refcount == 0)
            (*(void (**)(void))(*refPtrD + 8))();
    }
    refPtrD = src.refPtrD;
    if (refPtrD)
        *(int*)(refPtrD + 2) += 1;

    // 6. Copy byte flags at +0x30 and +0x31
    flag1 = src.flag1;
    flag2 = src.flag2;

    // 7. Copy first GUID (16 bytes at +0x32)
    for (int i = 0; i < 16; ++i)
        guid1[i] = src.guid1[i];

    // 8. Copy second GUID (16 bytes at +0x42)
    for (int i = 0; i < 16; ++i)
        guid2[i] = src.guid2[i];

    // 9. Handle dynamic element array (offsets +0x54, +0x58, +0x5C)
    // Release old element data if any, before copying
    if (elementData)
    {
        _DAT_01205a30 -= elementCount; // global tracking
    }

    int newCount = src.elementCount;
    if (elementCapacity < (uint32_t)newCount)
    {
        // Need to reallocate: round capacity up to multiple of 16
        int newCapacity = newCount + (0x10 - (newCount & 0xF));
        int* newData = (int*)malloc(newCapacity * sizeof(Element20));

        // Copy old elements to new buffer (if any)
        int oldCount = elementCount;
        int* oldData = elementData;
        elementData = newData; // temporarily set new pointer

        if (oldCount != 0)
        {
            int offset = 0;
            do {
                Element20* dest = (Element20*)((uint8_t*)elementData + offset);
                Element20* src = (Element20*)((uint8_t*)oldData + offset);
                *dest = *src;
                offset += sizeof(Element20);
                oldCount--;
            } while (oldCount != 0);
        }

        elementData = oldData; // restore old for freeing
        if (elementCount != 0)
            _DAT_01205a30 -= elementCount;
        free(oldData);
        elementData = newData;
        elementCapacity = newCapacity;
    }

    // Copy elements from source
    int* srcData = src.elementData;
    if (newCount != 0)
    {
        int offset = 0;
        do {
            Element20* dest = (Element20*)((uint8_t*)elementData + offset);
            Element20* srcElem = (Element20*)((uint8_t*)srcData + offset);
            *dest = *srcElem;
            offset += sizeof(Element20);
            newCount--;
        } while (newCount != 0);
    }
    elementCount = src.elementCount;

    // 10. Copy byte flags at +0x60 and +0x61
    flag3 = src.flag3;
    flag4 = src.flag4;

    // 11. Handle refcounted pointer at +0x64 (100 decimal)
    if (refPtrE)
    {
        int* refcount = refPtrE + 2;
        (*refcount)--;
        if (*refcount == 0)
            (*(void (**)(void))(*refPtrE + 8))();
    }
    refPtrE = src.refPtrE;
    if (refPtrE)
        *(int*)(refPtrE + 2) += 1;

    // 12. Copy byte flag at +0x68
    flag5 = src.flag5;
}