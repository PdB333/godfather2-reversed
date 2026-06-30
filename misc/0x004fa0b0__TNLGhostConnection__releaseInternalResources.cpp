// FUNC_NAME: TNLGhostConnection::releaseInternalResources

void __fastcall TNLGhostConnection::releaseInternalResources(int* thisPtr)
{
    // Base class destructor calls (multiple inheritance)
    BaseClass1::destructor();
    BaseClass2::destructor();

    // Check ghosted object block at offset 0x16C
    void* ghostBlock = reinterpret_cast<void*>(thisPtr[0x5b]); // offset 0x16C
    if (ghostBlock != nullptr)
    {
        // Set flag (0x200000) at offset 0xC within ghost block
        *reinterpret_cast<uint32_t*>(static_cast<char*>(ghostBlock) + 0xC) |= 0x200000;
        
        // Call ghost cleanup routine
        GhostCleanupFunc(); // FUN_0051d6b0

        // If there's a next pointer at offset 0x8, clear it
        if (*reinterpret_cast<void**>(static_cast<char*>(ghostBlock) + 0x8) != nullptr)
        {
            *reinterpret_cast<void**>(static_cast<char*>(ghostBlock) + 0x8) = nullptr;
            // Also clear the pointer itself (redundant but intentional)
            *reinterpret_cast<void**>(static_cast<char*>(ghostBlock) + 0x8) = nullptr;
        }
    }

    // Check reliable packet buffer at offset 0x40
    void* packetBuffer = reinterpret_cast<void*>(thisPtr[0x10]); // offset 0x40
    if (packetBuffer != nullptr)
    {
        // Release packet buffer resources
        PacketBufferReleaseFunc(); // FUN_004fc520

        // Push packetBuffer onto global free list (stack of freed objects)
        int*& freeListCursor = *reinterpret_cast<int**>(DAT_01206880 + 0x14); // global free list pointer
        *freeListCursor = reinterpret_cast<int>(&PTR_LAB_01123be8); // vtable for freed object
        freeListCursor++;
        *freeListCursor = reinterpret_cast<int>(packetBuffer); // pointer to the buffer
        freeListCursor++;
        *reinterpret_cast<int**>(DAT_01206880 + 0x14) = freeListCursor;

        // Clear the two fields
        thisPtr[0x10] = 0;
        thisPtr[0x11] = 0;
    }

    // Switch vtable to final base class
    *reinterpret_cast<void**>(thisPtr) = &PTR_FUN_00e37110;

    // Check secondary resource at offset 0x10
    void* secondaryResource = reinterpret_cast<void*>(thisPtr[4]); // offset 0x10
    if (secondaryResource != nullptr)
    {
        // Push secondaryResource onto global free list
        int*& freeListCursor = *reinterpret_cast<int**>(DAT_01206880 + 0x14);
        *freeListCursor = reinterpret_cast<int>(&PTR_LAB_01123be8);
        freeListCursor++;
        *freeListCursor = reinterpret_cast<int>(secondaryResource);
        freeListCursor++;
        *reinterpret_cast<int**>(DAT_01206880 + 0x14) = freeListCursor;

        // Clear the two fields
        thisPtr[4] = 0;
        thisPtr[5] = 0;
    }
}