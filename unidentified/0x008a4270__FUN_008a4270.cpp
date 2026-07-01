// FUNC_NAME: SomeManager::update
void __fastcall SomeManager::update(int thisPtr)
{
    // Call base engine update? (0x004bf5b0)
    engineUpdate();

    // If global singleton pointer is valid
    if (gSomeGlobalVTablePtr != nullptr)
    {
        // Check some flag at offset 0x36c
        if (*(int *)(thisPtr + 0x36c) != 0)
        {
            // Reset or initialize something (arg 0)
            resetSomething(0);
        }

        // Call a function from the global vtable (offset 0) with argument 1
        if (gSomeGlobalVTablePtr != nullptr)
        {
            (**(code **)(gSomeGlobalVTablePtr))(1);
        }
    }
}