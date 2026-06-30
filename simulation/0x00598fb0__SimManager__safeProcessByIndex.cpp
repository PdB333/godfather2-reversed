// FUNC_NAME: SimManager::safeProcessByIndex
// Function address: 0x00598fb0
// Role: Validates object index and calls debug processing. Part of SimManager (EARS engine).
//   This function checks if the given index is within bounds (m_objectCount at +0x10C),
//   adjusts it to the last valid index if out of range, asserts that the object pointer
//   at that index (from m_objects array at +0x110) is not null, then calls a debug
//   processing function and a common end routine.

void __thiscall SimManager::safeProcessByIndex(SimManager* this, uint index)
{
    // Check if index is out of bounds (>= m_objectCount)
    if (this->m_objectCount <= index)
    {
        // Call error handler (assert/break) via global debug system
        (*(code**)(*DAT_01205590 + 4))();
        // Clamp index to last valid element
        index = this->m_objectCount - 1;
    }

    // Check if the object pointer at index is null
    if (this->m_objects[index] == 0)
    {
        // Call error handler again
        (*(code**)(*DAT_01205590 + 4))();
    }

    // Call debug processing (e.g., draw bounding box, log) via another global
    (*(code**)(*DAT_012055a8 + 0x40))();

    // Common end-of-frame/bookend routine
    SimManager::commonEndRoutine(); // FUN_00597370
}

// Assumed structure offsets:
// +0x10C uint m_objectCount
// +0x110 int* m_objects (array of handles/pointers)