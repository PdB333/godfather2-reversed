// FUNC_NAME: EntitySubComponent::initializeTwoComponents
void __thiscall EntitySubComponent::initializeTwoComponents(
    int this,
    undefined4 param1,
    undefined4 param2,
    undefined4 param3,
    undefined4 param4
)
{
    // First sub-component initialization (likely a transform or physics object)
    FUN_006042a0(param1, param2, param4);

    // Initialize component at offset 0xB4 (e.g., a local transform or bounding box)
    FUN_004d4300(this + 0xB4);

    // Set up component with global constant DAT_00e4086c and param3
    // This might be a reference to a shared resource or animation state
    FUN_004d4b00(param4, &DAT_00e4086c, param3);

    // Initialize component at offset 0xC4 (e.g., another sub-object or attachment point)
    FUN_004d4300(this + 0xC4);

    return;
}