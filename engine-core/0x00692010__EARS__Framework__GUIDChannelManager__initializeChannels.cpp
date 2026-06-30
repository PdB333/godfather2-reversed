// FUNC_NAME: EARS::Framework::GUIDChannelManager::initializeChannels
// Address: 0x00692010
// This function initializes two objects (param_1 and param_2) with GUID-based interface channels.
// It handles two code paths based on a flag (likely platform or debug mode). 
// The global _DAT_00d5c968 is a system manager used to retrieve final channel values.

void GUIDChannelManager::initializeChannels(void* param_1, void* param_2, int flag)
{
    // Stage 1: Base initialization
    baseInit();
    getSomeSingleton(); // result ignored

    // Create a temporary object with vtable at 0x00691a50
    void* tempObj = createObject(&vtbl_0x00691a50);

    // Call virtual method at offset 4 on param_1 with argument 0
    callVtableMethod(param_1, 4, 0);

    // Register a GUID pair with param_2
    setGUIDInterface(0xebc77d43, param_2);
    // Wait: the order in decompiled: store param_2 then guid, then FUN_00690530()
    // Reorder to match: guid first, then pointer
    registerInterface(0xebc77d43, param_2);

    // Call another virtual on param_1 with arg 0xc
    void* result = getSomeHandle();
    callVtableMethod(param_1, 4, 0xc);

    // Register interface with GUID 0x0c1e9c75 and arg 0xc
    registerInterface(0x0c1e9c75, 0xc, param_1);

    // Reset and repeat for arg 0xd
    result = getSomeHandle();
    callVtableMethod(param_1, 4, 0xd);
    registerInterface(0x1d8e854d, 0xd, param_1);

    // Branch based on flag (EDI)
    if (flag == 4)
    {
        // Special debug/release path
        setGUIDInterface(0x62b07722, param_2);
        configureInterface(0xd177df7c, param_2);
        configureInterface(0x54a314df, param_2);
    }
    else
    {
        // Normal path
        setGUIDInterface(0x3ddc7637, param_2);
        configureInterface(0x2938c6cc, param_2);

        // Release two GUID interfaces (common pair)
        releaseInterfacePair(0xebc77d43, 0xed41087b, param_1);
        if (param_2 != nullptr)
        {
            releaseInterfacePair(0xebc77d43, 0xed41087b, param_2);
        }

        // Create another object with vtable at 0x00690ce0
        void* obj = createObject(&vtbl_0x00690ce0);
        callVtableMethod(param_1, 4, 0x20);
        registerInterface(0xed41087b, 0x20, param_1);
        finalizeInterface(0xed41087b);
    }

    // Common finalization: set up channel 0x16 on param_1 and 0x11 on param_2
    void* channelObj = createObject(&vtbl_0x00690d60);
    callVtableMethod(param_1, 4, 0x16);
    registerInterface(0x6ef11ea8, 0x16, param_1);

    if (param_2 != nullptr)
    {
        uint64_t streamData = createStreamData();
        pushStreamData(&streamData, &vtbl_0x00690e00, 1);
        callVtableMethod(param_2, 4, 0x11);
        registerInterface(0x6ef11ea8, 0x11, param_2);
    }

    // Create another object for channel 0x17 on param_1 and 0x12 on param_2
    channelObj = createObject(&vtbl_0x00690d60, 2, 3);
    callVtableMethod(param_1, 4, 0x17);
    registerInterface(0xbe16155b, 0x17, param_1);

    if (param_2 != nullptr)
    {
        streamData = createStreamData();
        pushStreamData(&streamData, &vtbl_0x00690e00, 2);
        callVtableMethod(param_2, 4, 0x12);
        registerInterface(0xbe16155b, 0x12, param_2);
    }

    // Finalize: set two channel properties from global system manager on param_2
    int vtable = *(int*)param_2; // vtable pointer
    int prop1 = getGlobalProperty(g_systemManager, 0);
    (*(void (__thiscall**)(void*, int, int))(vtable + 0x18))(param_2, 2, prop1);

    int prop2 = getGlobalProperty2(g_systemManager, 0);
    (*(void (__thiscall**)(void*, int, int))(vtable + 0x18))(param_2, 3, prop2);
}