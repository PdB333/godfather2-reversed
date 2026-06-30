// FUNC_NAME: handleEntityState
void __thiscall handleEntityState(int thisPtr, int entity) {
    int component = *(int*)(thisPtr + 0x218); // +0x218: pointer to owning component (e.g., CharacterComponent)
    if ((*(int*)(entity + 0x38) != 0) &&      // +0x38: flag indicating entity has a pending state
        (*(int*)(component + 0xb4) != 0)) {   // +0xb4: flag indicating component is active/valid
        if (*(int*)(entity + 0x3c) == 0) {    // +0x3c: flag for secondary state condition
            FUN_005764e0(component, entity);  // apply transition/effect to entity
            return;
        }
        FUN_00574bd0(component);              // revert/clear state on component
    }
}