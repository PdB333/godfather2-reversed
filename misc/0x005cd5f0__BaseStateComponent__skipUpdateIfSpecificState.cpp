// FUNC_NAME: BaseStateComponent::skipUpdateIfSpecificState
void __thiscall BaseStateComponent::skipUpdateIfSpecificState()
{
    // Read state field at +0x24, mask for bits 16-18 (0x70000)
    uint32 stateBits = *(uint32 *)(this + 0x24) & 0x70000;

    // If state is exactly one of three fixed values, return without doing anything
    if (stateBits == 0x10000)      // e.g., kStateA
        return;
    if (stateBits == 0x20000)      // e.g., kStateB
        return;
    if (stateBits == 0x40000)      // e.g., kStateC
        return;
    // For all other bit combinations, also return (trivial early-out)
    return;
}