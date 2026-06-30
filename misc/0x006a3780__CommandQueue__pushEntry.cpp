// FUNC_NAME: CommandQueue::pushEntry
// Address: 0x006a3780
// Role: Adds a 4-byte value to a fixed-size array queue, incrementing the count.
// Structure offsets:
//   +0x44: int count (number of entries currently stored)
//   +0x4c: int entries[] (array of 4-byte values, capacity unknown but at least count)

void __thiscall CommandQueue::pushEntry(int param_2)
{
    // Store the new entry at the current count index
    *(int *)(this + 0x4c + *(int *)(this + 0x44) * 4) = param_2;
    // Increment the count
    *(int *)(this + 0x44) = *(int *)(this + 0x44) + 1;
}