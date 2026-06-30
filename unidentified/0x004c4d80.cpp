// FUN_NAME: GhostManager::updateGhostData

#include <cstdint>

// External global pointer to the GhostManager instance
extern GhostManager* g_pGhostManager;

// Helper functions (implemented elsewhere)
int32_t __cdecl GetCurrentSequence();
int32_t __cdecl MarkGhostDirty(GhostManager* manager, int32_t flags);
void    __cdecl FlushGhostUpdate(GhostManager* manager, int32_t handle);

// GhostManager member function (__thiscall, this in ECX/EAX)
void GhostManager::updateGhostData(int32_t newParam, const uint8_t newData[16])
{
    // Read the slot index from the GhostManager instance (this)
    // Offset 0x2a: short slotIndex
    int32_t slotIndex = *reinterpret_cast<int16_t*>(reinterpret_cast<uint8_t*>(this) + 0x2a);
    
    if (slotIndex < 0)
        return;   // Invalid slot

    // Pre‑compute offsets into arrays held by the global GhostManager
    int32_t slotOffset = slotIndex * 0x20;                     // stride 0x20
    int32_t* stateEntry = reinterpret_cast<int32_t*>(
        *reinterpret_cast<int32_t*>(reinterpret_cast<uint8_t*>(g_pGhostManager) + 0x10) + slotOffset );
    
    // 0x10 offsets inside each stateEntry: +0x0c = some stored parameter, +0x14 = timestamp/sequence
    int32_t currentSequence = GetCurrentSequence();
    bool bDirty = (stateEntry[0x0c/4] != newParam) || (stateEntry[0x14/4] != currentSequence);
    
    int32_t markResult = 0;
    if (bDirty)
    {
        // Check the dirty‑play flag at g_pGhostManager+0x3c
        if (*reinterpret_cast<uint8_t*>(reinterpret_cast<uint8_t*>(g_pGhostManager) + 0x3c) != 0)
        {
            markResult = MarkGhostDirty(g_pGhostManager, 1);
        }
        
        // Copy the 16‑byte data into the “previous” array (stride 0x10)
        // g_pGhostManager+0x04 points to the beginning of that array
        uint8_t* dataEntry = reinterpret_cast<uint8_t*>(
            *reinterpret_cast<int32_t*>(reinterpret_cast<uint8_t*>(g_pGhostManager) + 0x04) +
            slotIndex * 0x10 );
        *reinterpret_cast<uint64_t*>(dataEntry)       = *reinterpret_cast<const uint64_t*>(newData);
        *reinterpret_cast<uint64_t*>(dataEntry + 8)   = *reinterpret_cast<const uint64_t*>(newData + 8);
        
        // Update the state entry with the new values
        stateEntry[0x0c/4] = newParam;
        stateEntry[0x14/4] = currentSequence;
        
        // If the manager is still active and markDirty succeeded, flush the update
        if ((*reinterpret_cast<uint8_t*>(reinterpret_cast<uint8_t*>(g_pGhostManager) + 0x3c) != 0) &&
            (markResult != 0))
        {
            FlushGhostUpdate(g_pGhostManager, markResult);
            // Clear the pending flag at offset 0x18
            *reinterpret_cast<uint8_t*>(reinterpret_cast<uint8_t*>(g_pGhostManager) + 0x18) = 0;
        }
    }
    else
    {
        // Data didn't change, but still need to store the input? 
        // The original code copies data even when bDirty is false – see the unconditional copy before bDirty check.
        // Actually the copy is inside the if (bDirty) block (after the first condition). But decompilation shows copy outside? 
        // Let's re‑examine: Ghidra: "puVar6 = ... *puVar6 = *param_2; puVar6[1] = param_2[1];" then "if (bVar1) {...}"
        // That means copy happens EVEN when bVar1 is false, because the copy is before the if(bVar1) block.
        // So the copy is unconditional (after the if(iVar5>=0) and after the dirty check? Actually the order: 
        //   iVar3 = 0;
        //   if ((*(char...)) && (bVar1)) iVar3 = FUN...
        //   puVar6 = ... *puVar6 = ... 
        //   if (bVar1) { ... }
        // So copy is after the optional MarkGhostDirty call, but BEFORE the if(bVar1) block. 
        // So copy is always performed if slotIndex >= 0. 
        // But bVar1 may be false, then we skip the updates. However the copy still happens. 
        // So we need to move the copy outside the bDirty conditional. Let's restructure accordingly.
    }
    
    // Unconditional copy of new data into the previous data array
    uint8_t* dataEntry = reinterpret_cast<uint8_t*>(
        *reinterpret_cast<int32_t*>(reinterpret_cast<uint8_t*>(g_pGhostManager) + 0x04) +
        slotIndex * 0x10 );
    *reinterpret_cast<uint64_t*>(dataEntry)       = *reinterpret_cast<const uint64_t*>(newData);
    *reinterpret_cast<uint64_t*>(dataEntry + 8)   = *reinterpret_cast<const uint64_t*>(newData + 8);
    
    // Now if dirty, update the state entry and possibly flush
    if (bDirty)
    {
        stateEntry[0x0c/4] = newParam;
        stateEntry[0x14/4] = currentSequence;
        
        if ((*reinterpret_cast<uint8_t*>(reinterpret_cast<uint8_t*>(g_pGhostManager) + 0x3c) != 0) &&
            (markResult != 0))
        {
            FlushGhostUpdate(g_pGhostManager, markResult);
            *reinterpret_cast<uint8_t*>(reinterpret_cast<uint8_t*>(g_pGhostManager) + 0x18) = 0;
        }
    }
}