// FUNC_NAME: WeightedDistribution::distributeTiming

void __thiscall WeightedDistribution::distributeTiming(void) {
  // Structure layout:
  // +0x00: (vtable or other)
  // +0x04: m_entries (pointer to array of Entry, stride 0x10)
  // +0x08: (unused)
  // +0x0c: m_entryCount (uint32)
  // +0x10: m_totalWeight (uint32) — number of slots/units
  // +0x14: m_totalValue (uint32) — total time/amount to distribute
  //
  // Entry layout (0x10 bytes each):
  // +0x00: unknown (4 bytes)
  // +0x04: unknown (4 bytes)
  // +0x08: m_flags (uint32): bit1 (0x2) = "active" or "needs timing"
  // +0x0c: m_assignedValue (int32) — result stored here

  uint32_t totalWeight = *(uint32_t*)(this + 0x10);
  float average;

  if (totalWeight == 0) {
    average = 0.0f;
  } else {
    // Convert unsigned ints to float, handling potential sign-bit issues
    // (original code adds 2^31 when negative to get correct unsigned value)
    uint32_t val = *(uint32_t*)(this + 0x14);
    int signedVal = *(int*)(this + 0x14);
    float fVal = (float)signedVal;
    if (signedVal < 0) {
      fVal += 2147483648.0f; // 0x4F000000
    }

    int signedWeight = *(int*)&totalWeight;
    float fWeight = (float)signedWeight;
    if (signedWeight < 0) {
      fWeight += 2147483648.0f;
    }

    average = fVal / fWeight;
  }

  uint32_t assignedCount = 0; // number of entries processed so far that had the flag set
  uint32_t count = *(uint32_t*)(this + 0x0c);
  uint8_t* entries = *(uint8_t**)(this + 0x04);

  for (uint32_t i = 0; i < count; i++) {
    Entry* entry = (Entry*)(entries + i * 0x10);

    // Compute proportional value based on the order of flagged entries
    float fAssigned = (float)assignedCount;
    if ((int)assignedCount < 0) { // safeguard (never happens for uint)
      fAssigned += 2147483648.0f;
    }
    entry->m_assignedValue = (int)(fAssigned * average + 0.5f); // ROUND to nearest

    // If bit1 is set in flags, count this entry for the next distribution
    if ((entry->m_flags >> 1) & 1) {
      assignedCount++;
    }
  }
}