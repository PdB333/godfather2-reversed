// FUNC_NAME: ComponentManager::processPendingRemovals
// Function address: 0x007043a0
// Role: Iterates over a list of component pointers, removes inactive components and frees memory.
//       Special handling when the component belongs to the player entity (notifies the GameManager).

void __thiscall ComponentManager::processPendingRemovals(void)
{
    // m_pComponentArray points to an array of 8‑byte entries; first DWORD is the component pointer
    int** componentArray = this->m_pComponentArray;          // param_1[0]
    int componentCount = this->m_nComponentCount;            // param_1[1]

    for (int i = 0; i < componentCount; i++)
    {
        int* pComponent = componentArray[i * 2];             // each entry is 8 bytes, extract the pointer
        if (pComponent == nullptr)
            continue;

        // The component is embedded at offset 0x48 inside an owner entity.
        // Subtract 0x48 to get the owner.
        Entity* pOwner = reinterpret_cast<Entity*>((char*)pComponent - 0x48);
        if (pOwner == nullptr)
            continue;

        // Check if the owner entity is still valid (e.g., not destroyed)
        if (!pOwner->IsValid())  // FUN_00481620
            continue;

        // Retrieve the game manager singleton
        GameManager* pGameManager = GameManager::GetInstance();  // FUN_007079a0
        if (pGameManager != nullptr)
        {
            // +0x74C: pointer to the player’s component (if any)
            int* pPlayerComponent = pGameManager->m_pPlayerComponent;  // offset 0x1d3*4 = 0x74C
            Entity* pPlayerOwner = nullptr;
            if (pPlayerComponent != nullptr)
            {
                // Player component is also embedded 0x48 bytes into the player entity
                pPlayerOwner = reinterpret_cast<Entity*>((char*)pPlayerComponent - 0x48);
            }

            // If the current owner is the player, notify the game manager
            if (pPlayerOwner == pOwner)
            {
                // Virtual function at vtable index 150 (byte offset 600)
                pGameManager->OnPlayerComponentRemoved(0);  // (**(code **)(*piVar4 + 600))(0);
            }
        }

        // End of update / release lock
        pOwner->EndUpdate();  // FUN_00481570

        // Remove the component from the owner (virtual at vtable index 88, byte offset 0x160)
        pOwner->RemoveComponent(pComponent);  // (**(code **)(*piVar1 + 0x160))(0);

        // Free the component’s allocation – memory block header is at pComponent - 0xc
        MemoryManager::Free(reinterpret_cast<void*>((char*)pComponent - 0xc));  // FUN_004088c0
    }

    // Compact the array after removals
    this->CompactArray();  // FUN_007042d0
}