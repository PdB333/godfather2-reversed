// FUNC_NAME: NetSession::setHost
bool __thiscall NetSession::setHost(int *this, int *hostInfo)
{
    int someMemberId;
    int *tmpPtr;
    int hostHandle;
    long long hostIdentifier;
    bool hostInfoValid;
    int *localThisCopy;

    localThisCopy = this;
    // Virtual function call at vtable+8 (probably reset/clear routine)
    (**(code **)(*this + 8))();
    // Unknown memory or state initialization
    FUN_00983120(0, 0, 0);
    tmpPtr = hostInfo;
    hostInfoValid = hostInfo != (int *)0x0;
    if (hostInfoValid) {
        // Get host handle from hostInfo (vtable+0x10)
        hostHandle = (int)(**(code **)(*hostInfo + 0x10))();
        // Possibly swap or reassign internal pointers
        FUN_00968ea0(&localThisCopy, &hostInfo);
        // Clear offset +0x04 of the object (likely a member pointer)
        localThisCopy[1] = 0;
        // Log/event: clearing hosts list
        FUN_005a04a0("ClearHostsList", 0, &DAT_00d8cdec, 0);
        // Call member function at (this[0xbb] + 0x6c) with arg 0
        // 0xbb*4 = 0x2EC offset – probably a pointer to another object
        (**(code **)(this[0xbb] + 0x6c))(0);
        someMemberId = this[0x19]; // offset 0x64 – some identifier
        // Get host identifier from hostInfo (vtable+0x3c)
        hostIdentifier = (**(code **)(*hostInfo + 0x3c))(hostHandle);
        // Register or use the host identifier
        FUN_0096e500(someMemberId, hostIdentifier, hostHandle);
    }
    // Clear bit 14 (0x4000) of flags at offset 0x1bd*4 = 0x6F4
    this[0x1bd] = this[0x1bd] & 0xffffbfff;
    return hostInfoValid;
}