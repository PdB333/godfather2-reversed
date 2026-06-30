// 0x0040ef80
// Reconstructed helper for The Godfather II (EA / EARS engine).
//
// This routine maintains a fixed-size FIFO of 16-bit state values stored at
// offset 0x90 on the owning object. It shifts the existing 16-entry window one
// slot toward the end of the array and writes the new value into the first slot.
//
// The exact gameplay meaning of the stored values is not fully identified from
// this function alone, but the surrounding code treats them as a recent history
// buffer used by a state machine / filter-like subsystem.

#include <cstdint>

class RecentMaskHistoryOwner
{
public:
    std::uint8_t reserved_00[0x90];   // Unidentified fields before the history.
    std::uint16_t recentMaskHistory[16]; // 0x90 - 0xAF

    void __thiscall pushRecentMask(std::uint16_t mask);
};

void __thiscall RecentMaskHistoryOwner::pushRecentMask(std::uint16_t mask)
{
    // Copy from back to front so the newest value lands in slot 0 and the
    // older entries are preserved in order.
    for (int index = 15; index > 0; --index)
    {
        recentMaskHistory[index] = recentMaskHistory[index - 1];
    }

    recentMaskHistory[0] = mask;
}
