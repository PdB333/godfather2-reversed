// FUNC_NAME: StreamManager::StreamManager

void __fastcall StreamManager::StreamManager(void *this, int maxStreams)
{
    // vtable pointer
    *(void**)this = &g_StreamManager_vtable;  // PTR_LAB_00e42f38

    // offset +0x0C: pointer to an internal buffer region (this + 0x138)
    *(void**)((char*)this + 0x0C) = (char*)this + 0x138;

    // offset +0x10: max number of streams (parameter)
    *(int*)((char*)this + 0x10) = maxStreams;

    // offset +0x04: clear
    *(int*)((char*)this + 0x04) = 0;

    // offset +0x08: clear
    *(int*)((char*)this + 0x08) = 0;

    // offset +0x14: byte clear
    *(char*)((char*)this + 0x14) = 0;

    // offset +0x2C: total stream data size (maxStreams * 8)
    *(int*)((char*)this + 0x2C) = maxStreams * 8;

    // offset +0x30: default buffer capacity (0x2000)
    *(int*)((char*)this + 0x30) = 0x2000;

    // offset +0x18: clear
    *(int*)((char*)this + 0x18) = 0;

    // offset +0x1C: byte clear
    *(char*)((char*)this + 0x1C) = 0;

    // offset +0x1D: byte clear
    *(char*)((char*)this + 0x1D) = 0;

    // offset +0x38: byte clear
    *(char*)((char*)this + 0x38) = 0;

    // offset +0x34: clear
    *(int*)((char*)this + 0x34) = 0;
}