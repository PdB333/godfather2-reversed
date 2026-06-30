// FUNC_NAME: getStatusFlag
unsigned char __fastcall getStatusFlag(void* unusedThis, int handle)
{
    int entityPtr;
    unsigned char localByte;
    int localInt[1]; // actually 4 bytes

    entityPtr = (int)findEntityByHandle(handle, &localByte, localInt);
    if (entityPtr != 0) {
        return *(unsigned char*)(entityPtr + 0x22); // Status flag at offset +0x22
    }
    return 0;
}