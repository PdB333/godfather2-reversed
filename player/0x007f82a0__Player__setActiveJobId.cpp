// FUNC_NAME: Player::setActiveJobId

void __thiscall Player::setActiveJobId(int *this, int newJobId) {
    // this: Player object (presumed class from EARS engine)
    // Field at +0x58 (this[0x16]) pointer to a manager/notifier (e.g., JobManager or MissionManager)
    code *notifyCallback = *(code **)(this[0x16] + 0x28); // +0x28 = 40 byte offset into that manager
    int oldJobId = this[0x7b8]; // +0x1EE0 – current active job/mission identifier
    this[0x7b8] = newJobId;

    // Signal with message ID 0x80 (likely a notification code, e.g., JOB_CHANGED)
    (*notifyCallback)(0x80);

    // Virtual function call: vtable slot 0x1C8/4 = 114
    // Typical pattern: "onJobChanged" taking previous and new values
    (**(code **)(*this + 0x1C8))(oldJobId, newJobId);
}