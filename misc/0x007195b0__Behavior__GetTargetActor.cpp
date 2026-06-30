// FUNC_NAME: Behavior::GetTargetActor
int __thiscall Behavior::GetTargetActor(void)
{
    // this is the behavior object, offset 0x330 holds a pointer to an internal node or slot
    int* pSlot = *(int**)(this + 0x330);
    if (pSlot == (int*)0) {
        return 0;
    }
    // Subtract 0x48 to get the base of the containing structure (e.g., a behavior controller)
    int* pBase = pSlot - 0x48; // equivalent to (int*)((char*)pSlot - 0x48)
    if (pBase == (int*)0) {
        return 0;
    }
    // Call a helper to retrieve a component from that base
    int* pComponent = FUN_0071ce70(pBase);
    if (pComponent != (int*)0) {
        // Offset 0x10 in the component is likely the actor pointer
        return (int)(pComponent + 0x10);
    }
    return 0;
}