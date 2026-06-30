// FUNC_NAME: NPCComponent::updateBehavior
void NPCComponent::updateBehavior(AnotherComponent* target)
{
    // Check global active flag via external function
    char active = isActive(); // FUN_005795f0
    if (active) {
        // Perform update on target and pass local buffer
        int localBuffer; // stack0xffffffe4
        processInput(target, &localBuffer); // FUN_00579450
        return;
    }
    // Check component-specific flags: bit 0x20 at offset +0xB and counter > 1 at +0x0
    if (((*(byte*)(this + 0xB) & 0x20) != 0) && (*(int*)this > 1)) {
        // Call virtual function at index 1 (vtable+4) on target
        (*(void (__thiscall**)(AnotherComponent*))(*((int*)target) + 4))(target);
        return;
    }
    // Default: always call same virtual on target
    (*(void (__thiscall**)(AnotherComponent*))(*((int*)target) + 4))(target);
}