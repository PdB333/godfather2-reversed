// FUNC_NAME: Character::setAnimationOverlayFlag
// Address: 0x00782db0
// Sets an animation overlay flag on the character data and triggers the animation.
// Parameter: animationId - index of the animation to play
// Parameter: isUpperBody - if true, sets upper body overlay flag (bit 29), else full body (bit 28)

void __thiscall Character::setAnimationOverlayFlag(int this, int animationId, char isUpperBody) {
    // Character data block (large structure with flags)
    int* characterData = *(int**)(this + 0x28);
    // Flags field at offset 0x1f5c within character data
    uint* flags = (uint*)(characterData + 0x1f5c / 4); // raw offset, reinterpret as uint

    if (isUpperBody == 0) {
        *flags |= 0x10000000; // Set bit 28 (full body overlay)
    } else {
        *flags |= 0x20000000; // Set bit 29 (upper body overlay)
    }
    *flags &= 0xBFFFFFFF; // Clear bit 30 (some other flag)

    // Play the specified animation with no blend
    FUN_007195f0(animationId, 0);

    if (animationId != 0) {
        // Check if game manager is present
        int manager = FUN_0043b870(DAT_01130fb0);
        if (manager != 0) {
            // Update character data (e.g., trigger events)
            FUN_009ab770(*(int*)(this + 0x28));
        }
    }

    // Call the first virtual function (likely "update" or "advance") with argument 1
    ((void (__thiscall*)(int, int))(*((int*)this + 0x1c / sizeof(int))))(1);
}