// FUNC_NAME: SomeComponent::isExpired
// Address: 0x006abda0
// Role: Checks whether a timer has expired and a secondary condition is met.
// Structure offsets:
//   +0x10: m_pOwner (int*) - pointer to an owning object
//   +0x18: m_timer (float) - countdown timer
//   +0x2c: m_threshold (float) - some comparison value
// External global: DAT_01205228 (float constant)

class SomeComponent {
public:
    bool isExpired() const;
};

// Global constant referenced in the function
extern const float DAT_01205228; // e.g. 0.0f or some maximum threshold

bool SomeComponent::isExpired() const {
    // All three conditions must be true:
    // - owner pointer is valid
    // - timer has expired (<= 0)
    // - threshold is within the allowed range
    return (m_pOwner != nullptr && 
            m_timer <= 0.0f && 
            m_threshold <= DAT_01205228);
}