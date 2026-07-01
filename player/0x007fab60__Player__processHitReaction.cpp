// FUNC_NAME: Player::processHitReaction
void __thiscall Player::processHitReaction(void* thisPtr, void* hitData, bool isHeadShot) {
    // +0x3d4: likely a flag like mIsDead or mIsInvincible
    if (*(int*)((char*)thisPtr + 0x3d4) != 0 && !isHeadShot) {
        // Play a special reaction (e.g. voice line for non-headshot while dead/invincible)
        // Read 12-byte transform from hitData+0x30-0x38
        __int128 hitTransform = *(__int128*)((char*)hitData + 0x30);
        FUN_00551260(&hitTransform); // likely handleSpecialReactionSound
        return;
    }

    // Default hit reaction path
    // +0x4a4: state flags (OR with 0x600 = combination of two flags)
    // +0x828: weapon animation slot info
    // +0x1c8c, 0x1ca4, 0x1c90, 0x1ca8: animation bone indices/parameters
    // +0x3b4: pointer to a hit reaction behavior object (initially null)
    // +0x3c0: pointer to some other data (e.g. current animation node)

    // Copy hit data transform (12 bytes) into local buffer
    char bodyTransform[12]; // probably a 3-float position or quaternion
    FUN_0043a2a0(bodyTransform, hitData); // extract character-relative transform

    // Get current weapon animation slot (returns an ID)
    int weaponSlot = FUN_00540cc0((char*)thisPtr + 0x828, 0);
    // Play hit reaction animation using extracted transform and bone data
    FUN_0054e530(
        thisPtr,
        *(int*)((char*)thisPtr + 0x1c8c),
        *(int*)((char*)thisPtr + 0x1ca4),
        *(int*)((char*)thisPtr + 0x1c90),
        *(int*)((char*)thisPtr + 0x1ca8),
        bodyTransform,
        weaponSlot,
        0
    );

    // Mark that a hit reaction is active
    *(unsigned int*)((char*)thisPtr + 0x4a4) |= 0x600;

    // If not a headshot and no hit reaction behavior exists yet, allocate one
    if (!isHeadShot && *(int*)((char*)thisPtr + 0x3b4) == 0) {
        // Allocate 8 bytes for a small behavior object
        int* behavior = (int*)FUN_009c8e50(8);
        if (behavior) {
            // Set vtable pointer (class VtableHitReactionBehavior)
            *behavior = (int)&PTR_FUN_00d71bfc;
        }
        // Store behavior pointer (even if null? — likely always succeeds in release)
        *(int**)((char*)thisPtr + 0x3b4) = behavior;
        if (behavior) {
            // Initialize the behavior object
            FUN_0054e310(behavior);
            // Store a reference to this+0x3c0 in behavior+4
            *(int*)(behavior + 1) = (int)((char*)thisPtr + 0x3c0);
        }
    }
}