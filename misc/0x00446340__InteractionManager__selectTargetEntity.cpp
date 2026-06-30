// FUNC_NAME: InteractionManager::selectTargetEntity

int __thiscall InteractionManager::selectTargetEntity(InteractionManager *this, Entity *entity, int playerIndex, bool skipConditional) {
    bool bVar1;
    char cVar2;
    undefined4 *transformData;
    undefined4 uVar4;
    code *customCallback;
    int interactionObj;
    int local_1c;
    Transform4x4 localTransform;
    Transform4x4 local_18;
    Transform4x4 local_14;
    Transform4x4 local_10;
    Transform4x4 local_c;

    if (entity == nullptr) {
        return 0;
    }

    // Get the current camera or world transform (e.g., player view matrix)
    transformData = (undefined4 *)getPlayerTransform(); // FUN_0043ab10 -> likely returns pointer to 16 floats
    local_18 = *transformData;
    local_14 = transformData[1];
    local_10 = transformData[2];
    local_c = transformData[3];
    interactionObj = 0;

    // Validate entity (e.g., check if it's alive, in range, etc.)
    cVar2 = validateEntity(this, entity, 0, 0, 0); // FUN_00446bf0
    if (cVar2 != '\0') {
        // Get the entity's primary component (e.g., physics or render object)
        if ((entity->flags & 1) == 0) { // flags at +0x1c, bit 0
            uVar4 = getComponentViaOffset(entity, 0x28); // FUN_004dafd0 -> deref pointer at +0x28
        } else {
            uVar4 = *(undefined4 *)(entity + 0x28); // direct component pointer
        }

        // Check for a custom interaction callback
        customCallback = (code *)getCustomInteractionCallback(); // FUN_00446bc0
        if (customCallback != nullptr) {
            // Custom callback: (component, transform, playerIndex, entity, 0)
            (*customCallback)(uVar4, &local_18, playerIndex, entity, 0);
            return 0;
        }

        // No custom callback – create a standard interaction proxy (e.g., GUI button, prompt)
        interactionObj = createInteractionProxy(uVar4, entity); // FUN_00483410
        if (interactionObj != 0) {
            // Check if the interaction is a special type (e.g., cinematic, locked)
            if ((*(uint *)(interactionObj + 0x14) & 0x8000000) == 0) {
                // Standard interaction – start it immediately
                startInteraction(this, interactionObj, playerIndex); // FUN_004467c0
            } else if (skipConditional == false) {
                // Special interaction – need to check conditions
                if ((this->currentInteractionState == 0) || // this+0x3c
                    (bVar1 = true, this->currentInteractionId != *(int *)(interactionObj + 0x1c))) { // this+0x40 vs interactionObj+0x1c
                    bVar1 = false;
                }
                int actionType = getActionType(playerIndex); // FUN_00402610 – e.g., 1=use, 2=talk, 3=attack
                if ((actionType == 3) || (bVar1)) {
                    finishInteraction(interactionObj, 0); // FUN_00446470 – finalize and return it
                    return interactionObj;
                }
            }
        }
    }
    return interactionObj;
}