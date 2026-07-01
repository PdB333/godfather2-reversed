// FUNC_NAME: PlayerInteractionManager::processInteraction
void __thiscall PlayerInteractionManager::processInteraction(int thisPtr, int entityPtr)
{
    char cVar1;
    int *globalPtr;
    int *componentPtr;
    int *interactableComponent;
    int iVar4;
    uint slotIndex;
    int *local_8;
    int local_4;

    local_4 = thisPtr;
    globalPtr = (int *)GameManager::getSingleton(); // FUN_00791300
    if (*(char *)(thisPtr + 0x154) != '\0') {
        // Check if entity is destroyed or invalid (bit 28 of flags at +0x5c)
        if ((*(uint *)(entityPtr + 0x5c) >> 0x1c & 1) != 0) {
            InteractionManager::cancelInteraction(entityPtr + 0x20); // FUN_008e3280
            return;
        }
        // Increment global interaction counter
        globalPtr[0x9a4] = globalPtr[0x9a4] + 1;
        slotIndex = 0;
        // Set global update function pointer (likely a callback)
        globalPtr[0x56] = (int)&InteractionUpdateCallback; // LAB_008e2e70
        // Iterate over 3 interaction slots starting at this+0x38, each 0x5c bytes
        int slotPtr = thisPtr + 0x38;
        do {
            componentPtr = (int *)SlotManager::getComponent(slotPtr, 0); // FUN_00446100
            if (componentPtr != (int *)0x0) {
                local_8 = (int *)0x0;
                // Query for InteractableComponent (hash 0x254cce9)
                cVar1 = (**(code **)(*componentPtr + 0x10))(0x254cce9, &local_8);
                interactableComponent = local_8;
                if ((((cVar1 != '\0') && (local_8 != (int *)0x0)) &&
                    // Check if interactable component is active
                    (cVar1 = (**(code **)(*local_8 + 0x154))(), cVar1 != '\0')) &&
                    // Get the entity that owns this component
                    (iVar4 = (**(code **)(*interactableComponent + 0x160))(), entityPtr == iVar4)) {
                    // Check if slot is currently active (bit 1 of flags at slotPtr+0x38)
                    if ((*(uint *)(slotPtr + 0x38) >> 2 & 1) != 0) {
                        iVar4 = slotPtr + 0x50;
                        cVar1 = InteractionSlot::isReady(iVar4); // FUN_0083cf40
                        if (cVar1 != '\0') {
                            InteractionSlot::reset(iVar4); // FUN_00790c80
                            // Register interaction with global manager
                            (**(code **)(*globalPtr + 0x1c))(iVar4);
                            // Clear the active flag
                            *(uint *)(slotPtr + 0x38) = *(uint *)(slotPtr + 0x38) & 0xfffffffb;
                        }
                    }
                    // Start the interaction
                    InteractionManager::startInteraction(entityPtr, slotPtr); // FUN_008e2850
                    return;
                }
            }
            slotIndex = slotIndex + 1;
            slotPtr = slotPtr + 0x5c;
        } while (slotIndex < 3);
    }
    return;
}