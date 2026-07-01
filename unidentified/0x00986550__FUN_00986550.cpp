// FUNC_NAME: SomeManager::setMaxCountAndNotify
// Function address: 0x00986550
// Role: Sets a maximum count (at +0x50) and optionally calls a notification callback.
// The function retains the object (via FUN_004d3e20) before potentially storing it.

void __thiscall SomeManager::setMaxCountAndNotify(int newMaxCount, void* object, void (*callback)(void*))
{
    // Retain the object (increment reference count or similar)
    retainObject(&object); // FUN_004d3e20

    // Update the maximum count if the new value is larger
    // +0x50: m_maxCount (uint)
    if (m_maxCount < (uint)(newMaxCount + 1)) {
        m_maxCount = newMaxCount;
    }

    // If the object is valid, invoke the callback
    if (object != nullptr) {
        callback(object);
    }
}