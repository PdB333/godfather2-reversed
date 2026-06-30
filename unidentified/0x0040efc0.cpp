// 0x0040efc0
// Reconstructed from Ghidra export for The Godfather II (EA / EARS engine).
//
// Main update path for a compact input-combo tracker:
//   - track a 16-bit button mask
//   - record only newly-pressed bits into the recent history buffer
//   - clear the history when the active context changes
//   - scan a small rule table for a context-specific sequence match
//   - notify an optional completion callback when a rule succeeds
//
// The exact gameplay meaning of "contextId" is not fully identified here.
// Based on the surrounding code, it behaves like a mode / player / controller
// discriminator that keeps combo state from leaking across contexts.

#include <cstdint>

struct ComboRuleEntry
{
    std::uint32_t unknown_00;                 // Present in the original layout; unused here.
    int contextId;                            // +0x04
    bool (*predicate)(void* predicateContext); // +0x08
    void* predicateContext;                   // +0x0C
};

class ComboInputTracker
{
public:
    void __thiscall processInput(int contextId, std::uint16_t currentMask);

private:
    ComboRuleEntry* m_rules[32];                  // +0x00
    std::uint32_t m_ruleCount;                    // +0x80
    int m_activeContextId;                        // +0x84
    std::uint16_t m_previousMask;                 // +0x88
    void (*m_onRuleMatched)(ComboRuleEntry* rule); // +0x8C
    std::uint16_t m_recentMaskHistory[16];        // +0x90

    void pushRecentMask(std::uint16_t mask);      // See 0x0040ef80.cpp
    bool matchesRecentHistory() const;            // See 0x0040eef0.cpp
};

void __thiscall ComboInputTracker::processInput(int contextId, std::uint16_t currentMask)
{
    const std::uint16_t newlyPressed = static_cast<std::uint16_t>(~m_previousMask & currentMask);

    // A context change invalidates the rolling sample window. This prevents
    // a combo started under one game state from being reused in another.
    if (contextId != m_activeContextId)
    {
        for (std::uint16_t& sample : m_recentMaskHistory)
        {
            sample = 0;
        }

        m_activeContextId = contextId;
    }

    // Only rising edges matter for the combo history. Releases are ignored.
    if (newlyPressed != 0)
    {
        pushRecentMask(newlyPressed);

        if (m_ruleCount != 0)
        {
            for (std::uint32_t ruleIndex = 0; ruleIndex < m_ruleCount; ++ruleIndex)
            {
                ComboRuleEntry* rule = m_rules[ruleIndex];
                if (rule == nullptr)
                {
                    continue;
                }

                if (rule->contextId != contextId)
                {
                    continue;
                }

                // The global recent-history matcher is consulted first.
                // Only if the active input pattern fits do we ask the rule
                // object itself whether it should fire.
                if (!matchesRecentHistory())
                {
                    continue;
                }

                if (!rule->predicate(rule->predicateContext))
                {
                    continue;
                }

                // Successful match: notify the owner, then reset the tracker
                // so the next combo must start from a fresh history window.
                if (m_onRuleMatched != nullptr)
                {
                    m_onRuleMatched(rule);
                }

                m_activeContextId = 0;
                for (std::uint16_t& sample : m_recentMaskHistory)
                {
                    sample = 0;
                }

                m_previousMask = currentMask;
                return;
            }
        }
    }

    m_previousMask = currentMask;
}
