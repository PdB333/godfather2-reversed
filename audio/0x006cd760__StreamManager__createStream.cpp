// FUNC_NAME: StreamManager::createStream
int __fastcall StreamManager::createStream(int thisPtr)
{
    undefined4 *allocator;
    int newStream;
    undefined4 localStruct[3]; // {2, 0x10, 0} for allocation alignment/type
    undefined4 *local_10; // unused, but pushed on stack

    allocator = (undefined4 *)MemoryManager::getAllocator(); // FUN_009c8f80()
    localStruct[0] = 2;
    localStruct[1] = 0x10;
    localStruct[2] = 0;

    // Allocate 0x170 bytes with alignment spec from localStruct
    newStream = (**(code **)*allocator)(0x170, &localStruct);
    if (newStream == 0) {
        return 0;
    }

    // Initialize the new stream object with this as parent
    newStream = StreamManager::initStream(thisPtr, newStream); // FUN_006cd2b0(thisPtr)

    // If this->field_0x78 is 0 or 0x48, set stream parameter
    if (*(int *)(thisPtr + 0x78) == 0 || *(int *)(thisPtr + 0x78) == 0x48) {
        // First get some sub-object from this+0x68, then set a parameter
        uVar3 = getStreamParamObject(thisPtr + 0x68, 0); // FUN_00445ff0
        setStreamParameter(uVar3, 0x55859efa, &localStruct); // FUN_004480d0
    }

    // Same check for field_0x80
    if (*(int *)(thisPtr + 0x80) == 0 || *(int *)(thisPtr + 0x80) == 0x48) {
        uVar3 = getStreamParamObject(thisPtr + 0x58, 0);
        setStreamParameter(uVar3, 0x55859efa, &localStruct);
    }

    // Process the field_0x78 sub-object
    startStreamPreload(thisPtr + 0x78); // FUN_006cd230

    // Mark the new stream as "loaded" or "active"
    *(uint *)(newStream + 0xdc) |= 0x80000;

    return newStream;
}