// FUNC_NAME: TriggerHandler::processTrigger
void __thiscall TriggerHandler::processTrigger()
{
    // +0xC4: pointer to a trigger object (may be inside a container at offset +0x48)
    char* triggerObj = reinterpret_cast<char*>(*(uint*)((char*)this + 0xC4));
    char* containerObj = nullptr;

    // Validate the trigger object and compute its container base
    if (triggerObj != nullptr)
    {
        containerObj = triggerObj - 0x48; // +0x48 is the offset of the trigger within the container
    }

    // If the trigger is invalid, perform cleanup and reinitialization
    if (triggerObj == nullptr || containerObj == nullptr)
    {
        // +0x10: pointer to an owner object (e.g., a scene node)
        uint* ownerFlags = &((uint*)(*(int*)((char*)this + 0x10)))[0x14 / 4]; // +0x14 offset inside owner

        if ((*ownerFlags & 0x1000) != 0) // bit 12: e.g., "streaming active"
        {
            uint* thisFlags = reinterpret_cast<uint*>((char*)this + 0xC);
            if ((*thisFlags & 0x20000) == 0) // bit 17: not yet set
            {
                *thisFlags |= 0x20000;
                signalStreamingActivation(); // FUN_0051b120
            }
            *thisFlags &= 0xFFFBFFFF; // clear bit 18 (0x40000)
        }

        // Clear container pointer and reset trigger
        *(int*)((char*)this + 0xB4) = 0;
        resetTrigger(0); // FUN_0051d230
        return;
    }

    // Store the container pointer at +0xB4
    *(char**)((char*)this + 0xB4) = containerObj;

    // Call virtual function at vtable offset 0x58 (index 22) – returns a value stored at +0x84
    typedef uint (__thiscall* GetValueFunc)(void*);
    GetValueFunc getValue = (GetValueFunc)(*(void***)containerObj)[0x58 / 4];
    *(uint*)((char*)this + 0x84) = getValue(containerObj);

    // Local buffers used for message processing
    uint messageBuffer[15] = { 0 }; // 60 bytes, first element cleared
    char outputBuffer[84] = { 0 };

    // Call virtual function at vtable offset 0x10 (index 4) – message handler
    // Signature: bool __thiscall handleMessage(uint magicId, void* buffer)
    typedef bool (__thiscall* MessageFunc)(void*, uint, void*);
    MessageFunc handleMsg = (MessageFunc)(*(void***)containerObj)[0x10 / 4];
    bool handled = handleMsg(containerObj, 0xae986323, messageBuffer);

    // Note: unaff_ESI is a global/register variable from the original assembly; assume it's a global pointer
    extern void* g_pSomeGlobal; // declared elsewhere
    int* pGlobalStruct = reinterpret_cast<int*>(g_pSomeGlobal);

    if (handled && pGlobalStruct != nullptr && *(int*)((char*)pGlobalStruct + 0x218) != 0)
    {
        uint* flags = (uint*)(*(int*)((char*)pGlobalStruct + 0x218) + 0x10);
        if ((*flags & 0x4480000) == 0) // bit masks (streaming/lock state)
        {
            // Copy data from trigger object +0x88 into output buffer (size 84)
            copyData(outputBuffer, triggerObj + 0x88); // FUN_0044b4e0

            // Call function with this->+0xB8 and the message buffer
            processResult(*(int*)((char*)this + 0xB8), messageBuffer); // FUN_0051cfb0

            finalizeAction(); // FUN_00417560
            return;
        }
    }

    // Fallback: check owner streaming flag again
    uint* ownerFlags = &((uint*)(*(int*)((char*)this + 0x10)))[0x14 / 4];
    if ((*ownerFlags & 0x1000) != 0)
    {
        uint* thisFlags = reinterpret_cast<uint*>((char*)this + 0xC);
        if ((*thisFlags & 0x20000) == 0)
        {
            *thisFlags |= 0x20000;
            signalStreamingActivation(); // FUN_0051b120
        }
        *thisFlags &= 0xFFFBFFFF;
        return;
    }
}