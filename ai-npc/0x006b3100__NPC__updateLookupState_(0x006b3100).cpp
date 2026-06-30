// FUNC_NAME: NPC::updateLookupState (0x006b3100)
// Role: Checks an internal state (at +0xC4) and based on its value (0 or 1), looks up a component/object by ID (at +0x38) then calls an action function on a field (+0x18 or +0x1c) from the retrieved object.

void __fastcall NPC::updateLookupState(int thisPtr)
{
    int* pComponent;
    
    // State at offset 0xC4: 0 = mode A, 1 = mode B
    if (*(int*)(thisPtr + 0xC4) == 0) {
        // Lookup using id at +0x38 for mode A
        pComponent = (int*)getEntityByID_0(*(int*)(thisPtr + 0x38));
        if (pComponent != 0) {
            // Call action on retrieved object's offset +0x18
            performAction(*(int*)(pComponent + 0x18));
            return;
        }
    }
    else if (*(int*)(thisPtr + 0xC4) == 1) {
        // Lookup using id at +0x38 for mode B
        pComponent = (int*)getEntityByID_1(*(int*)(thisPtr + 0x38));
        if (pComponent != 0) {
            // Call action on retrieved object's offset +0x1C
            performAction(*(int*)(pComponent + 0x1C));
        }
    }
    return;
}