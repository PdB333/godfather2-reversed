// FUNC_NAME: Animated::updateActionTimers
// Function address: 0x005f2490
// Role: Update per-action frame counters and timers for all animation layers/groups.
// Iterates over a 2D array of action data structures and processes each based on type.

class Animated {
public:
    // Offsets relative to this:
    // +0x00: unknown (probably vtable pointer)
    // +0x02: byte - number of action groups/layers
    // +0x03: byte - number of actions per group
    // +0x28: ushort* - pointer to the maximum frame count (used for clamping)
    // +0x2c: byte* - pointer to 2D array of ActionData (8 bytes each, indexed as [group][action])

    // Action data structure (8 bytes)
    struct ActionData {
        short m_duration;          // +0x00: Duration in frames? (set to 1000 if zero in type1)
        short m_typeAndFrame;      // +0x02: [7:0] = type (1-4), [15:8] = current frame index
        int   m_counter;           // +0x04: Counter/timer (clamped to 0..127 for type2)
    };

    // Offsets into the struct
    enum {
        OFF_NUM_GROUPS = 0x02,      // byte
        OFF_ACTIONS_PER_GROUP = 0x03, // byte
        OFF_MAX_FRAME_PTR = 0x28,   // ushort*
        OFF_ACTION_ARRAY = 0x2c     // byte*
    };

    // Member access helpers (inline for reconstruction)
    inline unsigned char getNumGroups() { return *(unsigned char*)((char*)this + OFF_NUM_GROUPS); }
    inline unsigned char getActionsPerGroup() { return *(unsigned char*)((char*)this + OFF_ACTIONS_PER_GROUP); }
    inline ushort* getMaxFramePtr() { return *(ushort**)((char*)this + OFF_MAX_FRAME_PTR); }
    inline ActionData* getActionArray() { return (ActionData*)(*(int*)((char*)this + OFF_ACTION_ARRAY)); }

    void __thiscall updateActionTimers();
};

void __thiscall Animated::updateActionTimers()
{
    unsigned char numGroups = getNumGroups();
    unsigned char actionsPerGroup = getActionsPerGroup();

    if (numGroups == 0) {
        return;
    }

    ushort* pMaxFramePtr = getMaxFramePtr();
    ushort maxFrame = *pMaxFramePtr; // the maximum allowed frame index

    ActionData* pActionArray = getActionArray();

    for (int groupIdx = 0; groupIdx < numGroups; groupIdx++) {
        // Base pointer to the current group (row) in the 2D array
        ActionData* pGroup = (ActionData*)((char*)pActionArray + actionsPerGroup * groupIdx * sizeof(ActionData));

        for (int actionIdx = 0; actionIdx < actionsPerGroup; actionIdx++) {
            ActionData& action = pGroup[actionIdx];
            unsigned char type = (unsigned char)(action.m_typeAndFrame & 0xFF); // low byte = type
            unsigned char currentFrame = (unsigned char)((action.m_typeAndFrame >> 8) & 0xFF); // high byte = frame index

            switch (type) {
                case 1: // Type 1: Set default duration if zero
                    if (action.m_duration == 0) {
                        action.m_duration = 1000; // default 1000 frames
                    }
                    break;

                case 2: // Type 2: Clamp frame index and counter
                    // Clamp frame index to valid range
                    if (maxFrame <= currentFrame) {
                        if (maxFrame == 0) {
                            action.m_typeAndFrame = (action.m_typeAndFrame & 0x00FF); // set high byte to 0
                        } else {
                            action.m_typeAndFrame = (action.m_typeAndFrame & 0x00FF) | ((unsigned short)(maxFrame - 1) << 8);
                        }
                    }
                    // Clamp counter to 0..127 (0x7F)
                    if (action.m_counter > 0x7F) {
                        action.m_counter = 0x7F;
                    }
                    // Note: also possible to set m_counter's high word? But here we set both shorts? Actually the code sets psVar4[2] and psVar4[3] separately,
                    // but since they are halves of the int, setting the int directly is equivalent.
                    break;

                case 3: // Type 3: Clamp frame index only
                    if (maxFrame <= currentFrame) {
                        if (maxFrame == 0) {
                            action.m_typeAndFrame = (action.m_typeAndFrame & 0x00FF);
                        } else {
                            action.m_typeAndFrame = (action.m_typeAndFrame & 0x00FF) | ((unsigned short)(maxFrame - 1) << 8);
                        }
                    }
                    break;

                case 4: // Type 4: Clamp counter to non-negative
                    if (action.m_counter < 0) {
                        action.m_counter = 0;
                    }
                    break;
            }
        }
    }
}