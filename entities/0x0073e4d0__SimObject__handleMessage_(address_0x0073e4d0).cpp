// FUNC_NAME: SimObject::handleMessage (address 0x0073e4d0)
void __thiscall SimObject::handleMessage(Message* message)
{
    // message->getHashID() returns a 32-bit hash identifying the message type
    uint32_t msgHash = message->getHashID();

    // Dispatch based on message hash
    if (msgHash < 0xD4D01408)
    {
        // --- Hash 0xD4D01407: "someEventA" ---
        if (msgHash == 0xD4D01407)
        {
            // Retrieve pointer at this+0x5c -> object +0x24cc, then adjust by -0x48 to get owner
            int* ownerPtr = *(int**)(*(int*)(this + 0x5C) + 0x24CC);
            if (ownerPtr != nullptr)
                ownerPtr = (int*)((uint8_t*)ownerPtr - 0x48);
            // Call utility function with the adjusted pointer (or null)
            FUN_0076b220(ownerPtr);

            // Update message field [30] with result from another function
            message[0x1E] = FUN_00716440();
            return;
        }

        // --- Hash 0x1B2D5C51: "someEventB" ---
        if (msgHash == 0x1B2D5C51)
        {
            int* ptr = *(int**)(this + 0x68);
            if (ptr != nullptr)
                ptr = (int*)((uint8_t*)ptr - 0x48);
            FUN_0073d590(ptr);
            return;
        }

        // --- Hash 0xBD0065C8: "someEventC" ---
        if (msgHash == 0xBD0065C8)
        {
            int* ptr = *(int**)(this + 0x68);
            if (ptr != nullptr)
                ptr = (int*)((uint8_t*)ptr - 0x48);
            FUN_0073e120(ptr);
            return;
        }
    }
    else
    {
        // --- Hash 0xE8B1C0E8: "someEventD" ---
        if (msgHash == 0xE8B1C0E8)
        {
            // Retrieve pointer from this+0x5c -> object +0x898, adjust by -0x48
            int* ownerPtr = *(int**)(*(int*)(this + 0x5C) + 0x898);
            if (ownerPtr != nullptr)
                ownerPtr = (int*)((uint8_t*)ownerPtr - 0x48);

            // Set flag at (this+0x5c) offset 0x894 bit 0
            uint32_t* flagField = (uint32_t*)(*(int*)(this + 0x5C) + 0x894);
            *flagField |= 1;

            FUN_00774e60(ownerPtr);

            // If bit 0 of byte at this+0x58 is set, set bit 0 of message[0x19]
            if ((*(uint8_t*)(this + 0x58) & 1) != 0)
                message[0x19] |= 1;
        }
        // --- Hash 0xFF45BBCA: "someEventE" ---
        else if (msgHash == 0xFF45BBCA)
        {
            uint32_t id = FUN_007ff880();
            // Call virtual function at vtable offset 0x30 on the message object
            // Pass the ID, the pointer from this+0x5c, and 0
            (*(void(__thiscall**)(uint32_t, int, int))(*message + 0x30))(id, *(int*)(this + 0x5C), 0);
            return;
        }
    }
}