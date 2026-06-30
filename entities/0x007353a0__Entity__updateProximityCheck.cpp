// FUNC_NAME: Entity::updateProximityCheck
void __fastcall Entity::updateProximityCheck(Entity* thisPtr)
{
    int iVar1;
    char cVar2;
    unsigned int uVar3;
    int* piVar4;
    int local_local = (int)thisPtr; // local copy for comparison

    // Timer at offset 0x2678 (likely a cooldown counter, decrements each frame)
    int* timer = (int*)((int)thisPtr + 0x2678);
    *timer = *timer - 1;

    if (*timer < 0) {
        // Reset timer to 30 frames
        *timer = 0x1e;

        // Clear bit 5 in flags at offset 0x1f5c (mask 0xffffffdf = clear bit 5)
        *(unsigned int*)((int)thisPtr + 0x1f5c) &= 0xffffffdf;

        // Get the object manager singleton
        uVar3 = getObjectManager(); // FUN_00806460
        // Get the linked list of all sim objects
        piVar4 = (int*)getObjectList(uVar3); // FUN_0043c2c0
        // The list starts with a header pointer; dereference to get first node
        piVar4 = (int*)*piVar4;

        if (piVar4 != (int*)0x0) {
            do {
                if ((int*)*piVar4 != (int*)0x0) { // node has data
                    local_local = 0;
                    // vtable+0x10: likely a virtual method that checks if object matches a type/hash
                    // parameter 0x369ac561 is a magic constant (type ID or interface)
                    cVar2 = (**(code**)(**(int**)*piVar4 + 0x10))(0x369ac561, &local_local);
                    iVar1 = local_local; // potential object pointer returned

                    // Conditions: the virtual call succeeded, the returned object exists,
                    // it is not this entity, and two spatial/overlap checks pass
                    if ((((cVar2 != '\0') && (local_local != 0)) && (local_local != (int)thisPtr)) &&
                       ((cVar2 = checkSpatialCondition1(), cVar2 != '\0' &&
                        (cVar2 = checkSpatialCondition2(thisPtr), cVar2 != '\0')))) {
                        // Trigger interaction on both objects
                        triggerInteraction(iVar1); // FUN_00732190
                        triggerInteraction((int)thisPtr);
                        return;
                    }
                }
                // Move to next node (offset 4 is next pointer)
                piVar4 = (int*)piVar4[1];
                if (piVar4 == (int*)0x0) {
                    return;
                }
            } while (true);
        }
    }
    return;
}