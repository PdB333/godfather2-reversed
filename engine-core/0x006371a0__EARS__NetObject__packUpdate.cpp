// FUNC_NAME: EARS::NetObject::packUpdate

void EARS::NetObject::packUpdate(NetObject* thisObj, PackCb* packCb) {
    // packCb is a structure with three fields:
    // [0] = pointer to stream context (e.g., BitStream*)
    // [1] = write function pointer (void (*)(void* stream, void* data, int size, int extra))
    // [2] = extra parameter (e.g., updateMask or flags)

    int count;
    void* arrayData;
    int bytes;

    // Write base class data (e.g., GhostObject header)
    FUN_00636e20(thisObj);

    // Write field at offset +0x3c (likely object class ID or some integer)
    int field3c = *(int*)((char*)thisObj + 0x3c);
    ((void (*)(void*, void*, int, int))packCb[1])(packCb[0], &field3c, 4, packCb[2]);

    // Write four consecutive bytes at offsets 0x44-0x47 (e.g., a bitmask or flags integer)
    char byte44 = *(char*)((char*)thisObj + 0x44);
    ((void (*)(void*, void*, int, int))packCb[1])(packCb[0], &byte44, 1, packCb[2]);

    char byte45 = *(char*)((char*)thisObj + 0x45);
    ((void (*)(void*, void*, int, int))packCb[1])(packCb[0], &byte45, 1, packCb[2]);

    char byte46 = *(char*)((char*)thisObj + 0x46);
    ((void (*)(void*, void*, int, int))packCb[1])(packCb[0], &byte46, 1, packCb[2]);

    char byte47 = *(char*)((char*)thisObj + 0x47);
    ((void (*)(void*, void*, int, int))packCb[1])(packCb[0], &byte47, 1, packCb[2]);

    // Write count at offset +0x30 (number of data elements in array at +0x14)
    count = *(int*)((char*)thisObj + 0x30);
    ((void (*)(void*, void*, int, int))packCb[1])(packCb[0], &count, 4, packCb[2]);

    // Write array of count*4 bytes pointed to by +0x14 (likely an array of ints/floats)
    arrayData = *(void**)((char*)thisObj + 0x14);
    bytes = count * 4;
    ((void (*)(void*, void*, int, int))packCb[1])(packCb[0], arrayData, bytes, packCb[2]);

    // Pack additional derived fields via helper functions
    FUN_00636ed0(thisObj);
    FUN_00637000(thisObj);
    FUN_006370b0(thisObj);   // This likely calls a derived class's pack or another base method

    // Write count at offset +0x2c (number of data elements in array at +0xc)
    count = *(int*)((char*)thisObj + 0x2c);
    ((void (*)(void*, void*, int, int))packCb[1])(packCb[0], &count, 4, packCb[2]);

    // Write array of count*4 bytes pointed to by +0xc (second dynamic array)
    arrayData = *(void**)((char*)thisObj + 0xc);
    bytes = count * 4;
    ((void (*)(void*, void*, int, int))packCb[1])(packCb[0], arrayData, bytes, packCb[2]);
}