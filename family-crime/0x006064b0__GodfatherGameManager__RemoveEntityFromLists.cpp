// FUNC_NAME: GodfatherGameManager::RemoveEntityFromLists
// Address: 0x006064b0
// Role: Removes an entity from various global tracking lists (active entity array and player slot arrays).
// Called on entity destruction or cleanup.
// param_1: entityPtr - pointer to the entity object
// param_2: bRemoveFromActiveList - if non-zero, also remove from the 20-entry active entity list

static GodfatherGameManager* gGameManager = (GodfatherGameManager*)0x01205750; // global singleton
static Entity* gActiveEntityList[20] = (Entity**)0x011d912c; // array of 20 entity pointers
static struct {
    Entity* entity;   // +0x00
    int slotId;       // +0x04
} gPlayerSlotList[5] = (struct*)0x011f38f0; // 5 player slot entries, each 8 bytes

static int gPlayerSlotFlag = *(int*)0x01223538; // flag set when player slot 0 is processed

void RemoveEntityFromLists(Entity* entityPtr, int bRemoveFromActiveList)
{
    Entity* currentEntity;
    Entity* entityFromSlot;
    int slotId;
    GodfatherGameManager* gm;

    if (entityPtr == 0) {
        return;
    }

    // First loop: check the global active entity list (20 entries)
    if (bRemoveFromActiveList != 0) {
        for (int i = 0; i < 20; i++) {
            if (entityPtr == gActiveEntityList[i]) {
                // call some removal notification (e.g., OnEntityRemovedFromList)
                // likely sends an event or triggers cleanup
                NotifyEntityRemoval();
                gActiveEntityList[i] = 0;
                break; // assume only one match? Actually loop continues but table cleared; break might be implied but code continues to end of loop
            }
        }
    }

    // Second loop: check the 5 player slot pairs (entity + slot ID)
    for (int i = 0; i < 5; i++) {
        entityFromSlot = gPlayerSlotList[i].entity; // [i*2] offset
        if (entityPtr == entityFromSlot) {
            slotId = gPlayerSlotList[i].slotId; // [i*2+4] offset
            gPlayerSlotList[i].entity = 0;
            gPlayerSlotList[i].slotId = 0;

            gm = gGameManager;
            if (entityFromSlot != 0 || slotId != 0) {
                // Different slot indices have special handling
                if (i == 4) {
                    // Slot 4: call method at vtable+0x9c (maybe removes enemy/extra slot)
                    (gm->vtable->UnregisterSlot4)(gm, 0);
                }
                else if (i == 0) {
                    // Slot 0: player's own entity – call method at vtable+0x94 with a slot ID from GetDefaultSlot()
                    int defaultSlot = GetDefaultSlotId(); // FUN_00609260
                    (gm->vtable->UnregisterSlot)(gm, 0, defaultSlot);
                    gPlayerSlotFlag = 1; // mark that player slot was handled
                }
                else {
                    // Other slots (1-3): call method at vtable+0x94 with slot index and zero
                    (gm->vtable->UnregisterSlot)(gm, i, 0);
                }
            }
        }
    }
    return;
}