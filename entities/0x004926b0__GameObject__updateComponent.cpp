// FUNC_NAME: GameObject::updateComponent
void __fastcall GameObject::updateComponent(int thisPtr)
{
    // Call base class update (likely performs generic object upkeep)
    FUN_00490b20();

    // Check if a child/sub-component pointer exists at offset +0x1c0
    if (*(int *)(thisPtr + 0x1c0) != 0)
    {
        // Process the component:
        // - arg1: value at +0x14 (could be a flag, ID, or size)
        // - arg2: the component pointer itself (+0x1c0)
        // - arg3: buffer/state at +0x1d0 (16 bytes? possibly a transform or data block)
        FUN_0060ad20(
            *(int *)(thisPtr + 0x14),      // +0x14: parameter field
            *(int *)(thisPtr + 0x1c0),     // +0x1c0: component pointer
            thisPtr + 0x1d0                 // +0x1d0: component data/work buffer
        );
    }
}