// FUNC_NAME: GhostManager::onGhostDeleted
// Address: 0x007890a0
// This function processes the deletion of a ghost object (param_2) from the manager.
// It checks if the object is already tracked in the internal list (at this+0x58).
// If not, it queries the object's virtual interface to determine its type (magic 0x637b907)
// and performs cleanup: notifies global systems, releases object ID, etc.

void __thiscall GhostManager::onGhostDeleted(GhostManager* this, int* pGhost) {
    // pGhost is a ghost object (e.g., NetObject*)
    // Each ghost object has a link node at offset +0x48 (in bytes, since param_2+0x12 where param_2 is int*)
    // That node is a member of a doubly linked list (likely mGhostLink)
    // local_18 = pointer to the link node inside the ghost
    int* pGhostLink = pGhost ? pGhost + 0x12 : nullptr;  // +0x48 bytes (int* arithmetic)

    // Save the next pointer of the link node and then set its next to itself? (removal marker)
    int* savedNext = pGhostLink ? pGhostLink[1] : 0;
    if (pGhostLink) {
        pGhostLink[1] = (int*)&pGhostLink;  // Point to itself (maybe means "orphaned" state)
    }

    // Search if pGhostLink is already in the manager's array of tracked ghost links (at +0x58)
    int* arrayBase = *(int**)(this + 0x58);
    uint count = *(uint*)(this + 0x5C);
    uint foundIndex = 0;
    if (count != 0) {
        for (; foundIndex < count; ++foundIndex) {
            if ((int*)arrayBase[foundIndex * 2] == pGhostLink) {
                // Already tracked - skip further processing
                goto cleanup;
            }
        }
    }

    // Not yet tracked: add pGhostLink to some list (via FUN_007834e0)
    GhostManager::addGhostToList(&pGhostLink);  // Possibly inserts into a pending deletion list

    // If bit 1 of flags (this+0x2C) is not set, process the deletion fully
    if (((*(uint*)(this + 0x2C) >> 1) & 1) == 0) {
        int* pRttiObject = nullptr;
        // Call virtual function at vtable offset 0x10 (4th function) of pGhost
        // This function appears to query an interface or type info with a GUID (0x55859efa)
        bool hasType = (**(code**)(*pGhost + 0x10))(0x55859efa, &pRttiObject);
        if (hasType && pRttiObject != nullptr && *(int*)(pRttiObject + 0x1ED4) == 0x637B907) {
            // Object matches specific type (e.g., Player or Crew)
            // Set bit 1 of flags to indicate this type was processed
            *(uint*)(this + 0x2C) |= 2;

            // Notify a global singleton (DAT_0112aa1c + 0x2C88) if it exists
            if (*(int*)(*(int*)0x0112AA1C + 0x2C88) != 0) {
                GhostManager::notifyDeletion(this);  // e.g., FUN_007857b0
            }

            // Release any associated object ID (this+0x30)
            if (*(int*)(this + 0x30) != -1) {
                if (*(int*)0x0112AF90 != 0) {
                    IdManager::releaseID(*(int*)(this + 0x30));  // e.g., FUN_009450b0
                }
                *(int*)(this + 0x30) = -1;
            }

            // Set a global flag
            GhostManager::setGlobalFlag(1);  // e.g., FUN_00788130

            // Play a sound or log event: check global state, then play sound with ID 0x29
            int* globalPtr = *(int**)0x012233A0;
            if (globalPtr[1] != 0 && globalPtr[1] != 0x1F30) {
                SoundSystem::playSound(0x29, 0);  // e.g., FUN_0079f100
            }
        }
    }

cleanup:
    // Remove pGhostLink from the linked list (restore previous state)
    if (pGhostLink != nullptr) {
        GhostManager::removeGhostFromList(&pGhostLink);  // e.g., FUN_004daf90
    }
    return;
}