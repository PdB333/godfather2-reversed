// FUNC_NAME: Entity::updatePendingDeletion
// Address: 0x007fbe50
// Role: Checks flag at +0x25c bit 5. If set, calls virtual timer function (vtable+0xc0). If timer > 0, clears flag and performs deletion.
void Entity::updatePendingDeletion() {
    // Offset +0x25c: m_flags (DWORD)
    const uint32_t kDeletionPendingBit = 5;
    const uint32_t kDeletionPendingMask = 1 << kDeletionPendingBit;

    if ((m_flags & kDeletionPendingMask) != 0) {
        // Virtual function at vtable offset 0xc0 returns remaining timer as long double
        float timer = getDeletionTimer(); // Virtual function index 48 (0xc0 / 4)
        if (timer > 0.0f) {
            // Clear deletion pending bit
            m_flags &= ~kDeletionPendingMask;
            // Perform actual removal/cleanup
            performDeletion(); // Corresponds to FUN_007f7050
        }
    }
}