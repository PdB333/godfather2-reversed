// FUNC_NAME: TNLConnection::removeReliablePacket

void __thiscall TNLConnection::removeReliablePacket(int thisPtr, int packetId)
{
    // Array of pointers to reliable packets (objects) at +0x30
    int** packetArray = *(int***)(thisPtr + 0x30);   // +0x30: array head
    int packetCount = *(int*)(thisPtr + 0x34);       // +0x34: array count
    uint index = 0;

    if (packetCount != 0) {
        // Search for the packet with the given ID (stored at +0xc of the pointed object)
        while (*(int*)(*packetArray + 0xc) != packetId) {
            index++;
            packetArray++;
            if (index >= (uint)packetCount) {
                return; // Not found
            }
        }

        if ((int)index >= 0) {
            // Save the packet pointer to remove
            int* removedPacket = packetArray[index]; // Actually *(int**)(*(thisPtr+0x30) + index*4) but we already have it

            // Shift remaining entries left to fill the gap
            if (index < (uint)(packetCount - 1)) {
                int* shiftSrc = (int*)(*(int*)(thisPtr + 0x30) + (uint)(index + 1) * 4);
                for (uint i = index; i < (uint)(packetCount - 1); i++) {
                    *(int**)(*(int*)(thisPtr + 0x30) + i * 4) = shiftSrc;
                    shiftSrc++;
                }
            }

            // Decrement count
            *(int*)(thisPtr + 0x34) = packetCount - 1;

            if (removedPacket != nullptr) {
                // Call virtual release/destroy function at vtable offset +0xc (index 3)
                (*(void (**)())(**(int**)removedPacket + 0xc))();
                // Free the packet memory
                FUN_009c8eb0(removedPacket);
            }

            // If no packets left, reset all status flags
            if (*(int*)(thisPtr + 0x34) == 0) {
                *(bool*)(thisPtr + 0x54) = false;    // +0x54: m_bFlag1
                *(bool*)(thisPtr + 0x64) = false;    // +0x64: m_bFlag2
                *(bool*)(thisPtr + 0x74) = false;    // +0x74: m_bFlag3
                *(uint*)(thisPtr + 0x4c) &= 0xfffffffd; // clear bit 1 (0x2) – m_flags
                *(bool*)(thisPtr + 0x84) = false;    // +0x84: m_bFlag4
                *(bool*)(thisPtr + 0x94) = false;    // +0x94: m_bFlag5
                *(uint*)(thisPtr + 0x4c) &= 0xfffffffb; // clear bit 2 (0x4)
                *(bool*)(thisPtr + 0xa4) = false;    // +0xa4: m_bFlag6
                *(bool*)(thisPtr + 0xb4) = false;    // +0xb4: m_bFlag7
                *(bool*)(thisPtr + 0xc4) = false;    // +0xc4: m_bFlag8
                *(bool*)(thisPtr + 0xd4) = false;    // +0xd4: m_bFlag9
                *(bool*)(thisPtr + 0xe4) = false;    // +0xe4: m_bFlag10
                *(uint*)(thisPtr + 0x4c) &= 0xfffffff7; // clear bit 3 (0x8)
            }

            // Log removal (global string DAT_01222230 likely "removed")
            undefined4 localStack[3]; // Actually 8 bytes + 1 byte = 12? But just a placeholder
            localStack[0] = DAT_01222230; // Global string reference
            localStack[1] = 0;
            localStack[2] = 0;
            FUN_00408a00(localStack, 0); // Debug output
        }
    }
}