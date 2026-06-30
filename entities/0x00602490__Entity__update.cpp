// FUNC_NAME: Entity::update
// Address: 0x00602490
// Role: Dispatches between two update implementations based on a flag at offset +0x48 (likely indicates active component or state)
void __thiscall Entity::update(int thisPtr, int arg1, int arg2, int arg3)
{
    // Check flag at offset 0x48 (e.g., mpActiveComponent, mStateFlags, etc.)
    if (*(int *)(thisPtr + 0x48) != 0)
    {
        // If flag is set, use simplified update (ignores arg2)
        // FUN_005fce40 - likely updateSimple or componentUpdate
        updateSimple(thisPtr, arg1, arg3);
    }
    else
    {
        // Otherwise use full update with all arguments
        // FUN_00602090 - likely updateFull or defaultUpdate
        updateFull(thisPtr, arg1, arg2, arg3);
    }
}