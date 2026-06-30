// Reconstructed from Ghidra export: 0x0040eef0
// Original behavior:
//   - compare the tracker's 16-entry input history against a zero-terminated
//     16-bit sequence stored in reverse order
//   - return a truthy value only when the most recent history words match the
//     sequence tail, up to a maximum of 16 entries

#include <cstdint>

// The original code reads the candidate sequence from an object field at +0x10.
// The exact type is not known, but the layout below matches the observed access.
struct ComboSequenceDefinition
{
    std::uint8_t padding_00[0x10];
    const std::uint16_t* sequenceWords; // +0x10
};

// The original object carries a rolling input history at +0x90.
// Only the fields relevant to this helper are modeled here.
class ComboInputTracker
{
public:
    bool MatchesReversedSequence(const ComboSequenceDefinition* sequenceDefinition) const;

private:
    std::uint8_t padding_00[0x90];
    std::uint16_t recentInputWords[16]; // +0x90
};

// Ghidra: FUN_0040eef0
bool ComboInputTracker::MatchesReversedSequence(const ComboSequenceDefinition* sequenceDefinition) const
{
    const std::uint16_t* sequenceBegin = sequenceDefinition->sequenceWords;
    const std::uint16_t* sequenceEnd = sequenceBegin;

    // Walk to the zero terminator, then step back to the last real element.
    while (*sequenceEnd != 0) {
        ++sequenceEnd;
    }
    --sequenceEnd;

    int comparedWords = 0;
    if (sequenceBegin <= sequenceEnd) {
        do {
            // The tracker only retains 16 samples, so longer sequences are
            // effectively truncated to their most recent 16 words.
            if (comparedWords > 0x0F) {
                break;
            }

            if (recentInputWords[comparedWords] != *sequenceEnd) {
                return false;
            }

            --sequenceEnd;
            ++comparedWords;
        } while (sequenceBegin <= sequenceEnd);
    }

    return true;
}
