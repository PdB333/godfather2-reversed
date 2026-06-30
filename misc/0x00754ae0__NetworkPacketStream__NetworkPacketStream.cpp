// FUNC_NAME: NetworkPacketStream::NetworkPacketStream
undefined4* __thiscall NetworkPacketStream::NetworkPacketStream(NetworkPacketStream* thisObj, undefined4 param2, undefined4 param3) {
    char boolResult;
    int* vtablePtr;

    // Call base class constructor (likely NetStream or similar)
    NetStream::NetStream(param2, param3);

    // Set vtable pointer for this class
    thisObj->vtable = (VTable*)&networkPacketStream_VTable;

    // Initialize various fields to default values
    thisObj->flags0x14 = 0;                           // +0x14: byte, likely some state flag
    thisObj->field_0x58 = 0;                          // +0x58
    thisObj->someId = 0xFFFFFFFF;                     // +0x5C, default to -1
    thisObj->field_0x60 = 0;                          // +0x60
    thisObj->field_0x64 = 0;                          // +0x64
    thisObj->field_0x68 = 0;                          // +0x68
    thisObj->flags0x20 = 0;                           // +0x20: byte, another flag
    thisObj->field_0x84 = 0;                          // +0x84
    thisObj->field_0x88 = 0;                          // +0x88
    thisObj->field_0x8C = 0;                          // +0x8C
    thisObj->flags0x24 = 0;                           // +0x24: byte
    thisObj->field_0x94 = 0;                          // +0x94

    // Resolve the containing object from a subobject pointer stored at +0x48
    if (thisObj->baseSubobjectPtr != (void*)0) {
        vtablePtr = (int*)((char*)thisObj->baseSubobjectPtr - 0x48);
    } else {
        vtablePtr = (int*)0;
    }

    // Call a virtual method on the resolved object to register the packet type
    // 0x55859efa is likely a hash of the packet type identifier
    boolResult = ((bool (*)(unsigned int, unsigned int*))(*vtablePtr))[0x10])(0x55859efa, &param3);

    // Store the result (based on return address trick – treated as a flag)
    thisObj->registrationResult = (unsigned int)(boolResult != 0) & thisObj->unknownRetAddr;

    // Clear remaining fields
    thisObj->field_0x70 = 0;                          // +0x70
    thisObj->field_0x6C = 0;                          // +0x6C
    thisObj->field_0x68 = 0;                          // +0x68

    return thisObj;
}