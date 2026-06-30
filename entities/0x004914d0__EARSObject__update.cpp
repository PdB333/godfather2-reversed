// FUNC_NAME: EARSObject::update
// Address: 0x004914d0
// Role: Tick/update method for EARSObject, handles behavior processing between pre and post update steps.

void EARSObject::update() {
    // Pre-update logic
    preTick();  // FUN_00490b20

    // If a behavior is active, process it
    if (m_pBehavior != nullptr) {  // +0x1c0
        // Call behavior processing function with slot ID, behavior pointer, and behavior buffer
        processBehavior(m_someId, m_pBehavior, &m_behaviorBuffer);  // args: +0x14, +0x1c0, +0x1d0
    }

    // Post-update logic
    postTick();  // FUN_00492190
}