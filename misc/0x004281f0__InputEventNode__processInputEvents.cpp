// FUNC_NAME: InputEventNode::processInputEvents
// Address: 0x004281f0
// This function processes pending input events for an input node and its children.
// It checks global input state arrays for events (state == 2) and distributes values.
// Counters track small (< 0x10) vs large events for statistics/feedback.
// The node structure has: +0x24 bool flag, +0x28 uint inputId, +0x2c uint timestamp, +0x30 int value,
// +0x48 InputEventNode* children array, +0x4c uint childCount, +0x40 some handle (used in feedback)

// Global arrays indexed by inputId (0..0x1FF)
extern int gInputEventState[0x200];     // 0x012083e8  0=idle, 2=active
extern int gInputEventValue[0x200];     // 0x012083f0  raw value (<0x10 = small, else large)
extern int gSmallEventCounter;          // _DAT_01163cc0
extern int gLargeEventCounter;          // _DAT_01163cc4
extern uint gCurrentTimestamp;          // DAT_0110ac50
extern char gProcessingEnabled;         // DAT_0120537e (byte, allows child processing)

class InputEventNode {
public:
    bool m_flag;                    // +0x24
    uint m_inputId;                 // +0x28
    uint m_timestamp;               // +0x2c
    int m_value;                    // +0x30
    void* m_feedbackHandle;         // +0x40 (used by triggerFeedback)
    InputEventNode* m_children;     // +0x48 (pointer to array of child nodes, stride 0x50)
    uint m_childCount;              // +0x4c
    // total size likely 0x50

    bool processInputEvents();
};

// Forward declarations of called functions
void updateFlagState(InputEventNode* node, bool newFlag);  // FUN_00427e80
void triggerFeedback(void* handle, bool isSmall);          // FUN_0049fad0

bool InputEventNode::processInputEvents()
{
    uint id = m_inputId;

    // Process own pending input event
    if (id < 0x200) {
        if (gInputEventState[id] == 2) {
            bool isSmall = (gInputEventValue[id] < 0x10);
            if (isSmall) {
                gSmallEventCounter++;
            } else {
                gLargeEventCounter++;
            }
            m_value = gInputEventValue[id];

            // If the stored flag differs from this event's size classification, update it
            if (m_flag != isSmall) {
                updateFlagState(this, isSmall);
            }

            m_timestamp = gCurrentTimestamp;
            gInputEventState[id] = 0;       // consume event
            m_inputId = 0xFFFFFFFF;
        }
    }

    // If global processing is enabled, process children's pending events
    if (gProcessingEnabled) {
        uint count = m_childCount;
        if (count != 0) {
            uint i = 0;
            int offset = 0;  // actual offset = i * 0x50
            do {
                InputEventNode* child = reinterpret_cast<InputEventNode*>(
                    reinterpret_cast<intptr_t>(m_children) + offset);
                uint childId = child->m_inputId;

                if (childId < 0x200) {
                    if (gInputEventState[childId] == 2) {
                        bool isSmall = (gInputEventValue[childId] < 0x10);
                        if (isSmall) {
                            gSmallEventCounter++;
                        } else {
                            gLargeEventCounter++;
                        }

                        gInputEventState[childId] = 0;      // consume event
                        child->m_inputId = 0xFFFFFFFF;
                        child->m_timestamp = gCurrentTimestamp;
                        child->m_value = gInputEventValue[childId];

                        // If the stored flag differs, update child's flag and trigger feedback
                        if (child->m_flag != isSmall) {
                            child->m_flag = isSmall;
                            triggerFeedback(child->m_feedbackHandle, isSmall);
                        }
                    }
                }

                i++;
                offset += 0x50;  // stride of child node
            } while (i < count);
            return true;
        }
        // no children -> done
        return true;
    }
    return true;  // always returns 1
}