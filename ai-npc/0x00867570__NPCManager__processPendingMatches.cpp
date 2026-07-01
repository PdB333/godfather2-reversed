// FUNC_NAME: NPCManager::processPendingMatches
// Address: 0x00867570
// Role: Updates entity matching/swapping for NPCs that are not in special states (combat/mission/etc.)
// Checks bit flags at this+0xf28 (likely m_flags or m_stateMask)
// Uses command-query function (0x005fd860) with codes 1,2,3 to retrieve/swap entity pairs
// Uses a compare-and-swap function (0x00865c50) to attempt assignment

void __thiscall NPCManager::processPendingMatches(int this)
{
    uint flags = *(uint *)(this + 0xf28); // +0xf28: state/behavior flags (bits 25-27: combat, mission, etc.)

    // Only proceed if none of the high flags are set (e.g., not in combat, not in mission)
    if (!(flags & 0x02000000) && !(flags & 0x04000000) && !(flags & 0x08000000)) {
        int firstIndex = 0;    // e.g., index of first entity
        int secondIndex = 0;   // index of second entity
        int firstType = 0;     // type/category of first
        int secondType = 0;    // type/category of second

        // Command codes used: 2, 3, 1
        int cmdBuffer[2];      // buffer used for command and output
        cmdBuffer[1] = 2;      // command 2: query some pending pair
        queryCommand(cmdBuffer + 1, &firstIndex, &firstType); // 0x005fd860

        if (firstType != 0) {
            cmdBuffer[1] = 3;  // command 3: query related secondary
            queryCommand(cmdBuffer + 1, cmdBuffer, &secondType);

            if ((secondType != 0) && !compareAndSwap(firstIndex, firstType, cmdBuffer[0], secondType)) {
                // Swap failed; try opposite assignment
                secondType = 0;
                cmdBuffer[0] = 0;
                cmdBuffer[1] = 1;              // command 1: query alternative
                queryCommand(cmdBuffer + 1, &secondType, cmdBuffer);
                if (cmdBuffer[0] != 0) {
                    compareAndSwap(secondType, cmdBuffer[0], firstIndex, firstType);
                }
            }
        }
    }
}