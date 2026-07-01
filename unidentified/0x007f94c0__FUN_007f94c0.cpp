// FUNC_NAME: SomeClass::accumulateTimedSample
void __thiscall accumulateTimedSample(int thisPtr, float sampleValue, int timestamp)
{
  int currentIndex = *(int *)(thisPtr + 0x890); // current sample index in ring buffer
  int *timestampArray = (int *)(thisPtr + 0x868); // array of timestamps, 8 bytes per entry (timestamp + value)
  float *valueArray = (float *)(thisPtr + 0x86c); // array of values, interleaved with timestamps

  // Check if the new timestamp is more than 0x9c3 (2500?) units away from the stored timestamp at current index
  if (0x9c3 < (uint)(timestamp - timestampArray[currentIndex * 8 / 4])) { // note: 8 bytes per entry, so index*2 for ints
    // Too far apart: advance to next slot (ring buffer of 5 entries)
    currentIndex++;
    *(int *)(thisPtr + 0x890) = currentIndex;
    if (4 < currentIndex) {
      *(int *)(thisPtr + 0x890) = 0; // wrap around
    }
    // Store new sample at the new index
    valueArray[*(int *)(thisPtr + 0x890) * 2] = sampleValue; // +0x86c + index*8
    timestampArray[*(int *)(thisPtr + 0x890) * 2] = timestamp; // +0x868 + index*8
    return;
  }
  // Within time window: accumulate (add) the sample value to the existing entry
  valueArray[currentIndex * 2] = valueArray[currentIndex * 2] + sampleValue;
  return;
}