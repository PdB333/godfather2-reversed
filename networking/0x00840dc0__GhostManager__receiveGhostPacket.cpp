// FUNC_NAME: GhostManager::receiveGhostPacket
void __thiscall GhostManager::receiveGhostPacket(int thisPtr, int* packetData, int connectionId)
{
    int guid[4]; // 128-bit GUID from packet header
    guid[0] = packetData[0];
    guid[1] = packetData[1];
    guid[2] = packetData[2];
    guid[3] = packetData[3];

    // Check if ghost registry exists (offset +0x170 likely mGhostRegistry)
    if (*(int*)(thisPtr + 0x170) != 0)
    {
        // Adjust pointer to get the ghost container base (offset -0x48 from registry start)
        int* ghostContainer = (int*)(*(int*)(thisPtr + 0x170) - 0x48);
        if (ghostContainer != 0)
        {
            // Begin iteration over ghosts matching this GUID
            int* iterator = (int*)FUN_00446100(guid);
            if (iterator != 0)
            {
                int* foundGhost = 0;
                do
                {
                    int* currentGhost = 0;
                    // Check if current iterator entry matches the given hash (virtual at vtable+0x10)
                    char isValid = (**(code**)(*iterator + 0x10))(0xae986323, &currentGhost);
                    if (isValid == 0)
                    {
                        currentGhost = 0;
                    }
                    else if (currentGhost != 0 && (isValid = FUN_00402080(&DAT_012067c4), isValid == 0))
                    {
                        // Debug condition break? Possibly failed assertion
                        break;
                    }
                    foundGhost = currentGhost;
                    // Move to next iterator
                    iterator = (int*)FUN_00446100(guid, iterator);
                } while (iterator != 0);

                if (foundGhost != 0)
                {
                    int refCounter = 0;
                    // Convert connection ID to internal reference (e.g., network handle)
                    int handle = FUN_004dafd0(connectionId);
                    // AddRef on ghost container? (virtual at vtable+0x98)
                    char result = (**(code**)(*ghostContainer + 0x98))(&refCounter, handle);
                    if (result != 0)
                    {
                        // AddRef on found ghost as well
                        handle = FUN_004dafd0(foundGhost);
                        result = (**(code**)(*foundGhost + 0x98))(&refCounter, handle);
                        if (result != 0)
                        {
                            // Process the ghost update (virtual at vtable+0x80)
                            // Arguments: foundGhost, packet data offset, refCounter, flags, unused
                            (**(code**)(*ghostContainer + 0x80))(foundGhost, &guid[2], &refCounter, 0, 0);
                        }
                    }
                }
            }
        }
    }
}