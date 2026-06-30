// FUNC_NAME: ReplicationStream::initialize
void ReplicationStream::initialize(int streamId)
{
    int *piVar1;
    int iVar5;
    undefined4 *puVar6;
    void *_Dst;
    // this = ESI

    this->field_4 = 0; // +0x04
    this->field_8 = 0; // +0x08
    this->vtable = &ReplicationStream_vtable; // +0x00
    this->dataBuffer2 = 0; // +0x18
    this->dataBuffer1 = 0; // +0x1C
    this->initialized = 0; // +0x20

    void* globalMgr = GetGlobalManager(); // FUN_006607b0
    int* alloc = (int*)_malloc(0x38); // size 56

    if (DAT_0120588f == '\0') {
        DAT_0120588f = 1;
        InitGlobalData(&DAT_01203740); // FUN_00662100
        SetupGlobalData(&DAT_01203740); // FUN_006622a0
    }

    iVar5 = AllocateFromGlobalPool(&DAT_01203740, alloc); // FUN_00663200
    if (iVar5 == 0) {
        this->streamId = streamId; // +0x10
        this->poolAlloc = alloc; // +0x0C
        DAT_01204978 = 0;

        // Write streamId in big-endian to global buffer
        DAT_01204979 = (uint8)(streamId >> 0x18);
        DAT_0120497a = (uint8)(streamId >> 0x10);
        DAT_0120497b = (uint8)(streamId >> 8);
        DAT_0120497c = (uint8)streamId;

        int someVal = 0x7fb;
        EncodeBuffer(&DAT_0120497d, &someVal, 0, alloc); // FUN_00663850 (write type/length?)

        int encodedSize = (int)someVal + 5;
        puVar6 = CreateBufferObject(0x18); // FUN_009c8e50
        if (puVar6 != 0) {
            puVar6[4] = encodedSize;
            puVar6[1] = 0;
            puVar6[2] = 0;
            *puVar6 = &DataBuffer_vtable; // PTR_LAB_00e42d64
            puVar6[3] = &DAT_01204978;
            *(uint8*)(puVar6 + 5) = 0;
        }

        // Release previous dataBuffer1 (if any)
        if (this->dataBuffer1 != 0) {
            piVar1 = this->dataBuffer1 + 2;
            *piVar1 = *piVar1 - 1;
            if (*piVar1 == 0) {
                (*(void (**)())*this->dataBuffer1)(); // destructor
            }
        }
        this->dataBuffer1 = puVar6;
        if (puVar6 != 0) {
            puVar6[2] = puVar6[2] + 1; // increase refcount
        }

        // Ensure dataBuffer1 owns its own copy
        iVar5 = this->dataBuffer1;
        if (*(uint8*)(iVar5 + 0x14) == 0) {
            _Dst = (void*)_malloc(*(size_t*)(iVar5 + 0x10));
            memcpy(_Dst, *(void**)(iVar5 + 0x0C), *(size_t*)(iVar5 + 0x10));
            *(void**)(iVar5 + 0x0C) = _Dst;
            *(uint8*)(iVar5 + 0x14) = 1;
        }

        // Now repeat same pattern for second buffer with flag=1
        DAT_01204978 = 1;
        DAT_01204979 = (uint8)(streamId >> 0x18);
        DAT_0120497a = (uint8)(streamId >> 0x10);
        DAT_0120497b = (uint8)(streamId >> 8);
        DAT_0120497c = (uint8)streamId;

        someVal = 0x7fb;
        EncodeBuffer(&DAT_0120497d, &someVal, 1, alloc);

        encodedSize = (int)someVal + 5;
        puVar6 = CreateBufferObject(0x18);
        if (puVar6 != 0) {
            puVar6[4] = encodedSize;
            puVar6[1] = 0;
            puVar6[2] = 0;
            *puVar6 = &DataBuffer_vtable;
            puVar6[3] = &DAT_01204978;
            *(uint8*)(puVar6 + 5) = 0;
        }

        // Release previous dataBuffer2
        if (this->dataBuffer2 != 0) {
            piVar1 = this->dataBuffer2 + 2;
            *piVar1 = *piVar1 - 1;
            if (*piVar1 == 0) {
                (*(void (**)())*this->dataBuffer2)();
            }
        }
        this->dataBuffer2 = puVar6;
        if (puVar6 != 0) {
            puVar6[2] = puVar6[2] + 1;
        }

        // Ensure dataBuffer2 owns its own copy
        iVar5 = this->dataBuffer2;
        if (*(uint8*)(iVar5 + 0x14) == 0) {
            _Dst = (void*)_malloc(*(size_t*)(iVar5 + 0x10));
            memcpy(_Dst, *(void**)(iVar5 + 0x0C), *(size_t*)(iVar5 + 0x10));
            *(void**)(iVar5 + 0x0C) = _Dst;
            *(uint8*)(iVar5 + 0x14) = 1;
        }

        this->field_14 = 1; // +0x14
        this->initialized = 1; // +0x20
    }
    return;
}