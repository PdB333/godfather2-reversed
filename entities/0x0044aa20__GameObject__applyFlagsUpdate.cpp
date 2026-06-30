// FUNC_NAME: GameObject::applyFlagsUpdate
// Address: 0x0044AA20
// Role: Processes a message (type 0x20E5862) to update an object's flags bitfield.
// Uses a set-and-clear pattern: newFlags = (currentFlags | bitsToSet) & ~bitsToClear.
// The state at +0x0C determines whether to call applyFlagsGlobal() or onFlagsChanged().

enum class ObjectState : int32_t {
    kStateInvalid = 0,
    kStateActive  = 0x48
};

class GameObject {
public:
    // +0x0C: Object state
    int32_t m_state;
    // +0x14: Bitfield of flags
    uint32_t m_flags;

    // Message type constant for flag updates (likely a hash)
    static const uint32_t kMessageTypeFlagsUpdate = 0x20E5862;

    void __thiscall applyFlagsUpdate(uint32_t messageType, uint64_t* pData) {
        // Only process if this is the expected message type
        if (messageType != kMessageTypeFlagsUpdate || pData == nullptr)
            return;

        uint32_t bitsToSet   = static_cast<uint32_t>(*pData);          // low 32 bits
        uint32_t bitsToClear = static_cast<uint32_t>((*pData) >> 32); // high 32 bits

        uint32_t oldFlags = m_flags;
        uint32_t newFlags = (oldFlags | bitsToSet) & ~bitsToClear;
        m_flags = newFlags;

        // Only act if the flags actually changed
        if (oldFlags == newFlags)
            return;

        // State-dependent handling
        if (m_state == ObjectState::kStateInvalid || m_state == ObjectState::kStateActive) {
            // Default path: call a global flag application function
            applyFlagsGlobal(bitsToSet, bitsToClear);
        } else {
            // Custom handler for other states (e.g., networked object)
            onFlagsChanged();
        }
    }

private:
    // FUN_0046F990: Applies the flag delta to the game state
    void applyFlagsGlobal(uint32_t bitsToSet, uint32_t bitsToClear);
    // FUN_0044A8E0: Called when flags change for objects not in default states
    void onFlagsChanged();
};