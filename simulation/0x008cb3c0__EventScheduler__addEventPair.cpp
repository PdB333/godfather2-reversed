// FUNC_NAME: EventScheduler::addEventPair
// Address: 0x008cb3c0
// Role: Adds a pair of integer values to a pending events array.
// The array can hold up to 500 entries; count stored at offset +0xfac.
// Entries are 8 bytes each: two ints, stored at +0xc and +0x10 relative to entry start.

void __thiscall EventScheduler::addEventPair(EventScheduler *this, int value1, int value2)
{
  int count = *(int *)((uintptr_t)this + 0xfac); // pending event count
  if (count < 500) {
    // Store the pair in the next available slot
    *(int *)((uintptr_t)this + 0xc + count * 8) = value1;   // +0xc: first field
    *(int *)((uintptr_t)this + 0x10 + count * 8) = value2;  // +0x10: second field
    // Increment the count
    *(int *)((uintptr_t)this + 0xfac) = count + 1;
  }
}