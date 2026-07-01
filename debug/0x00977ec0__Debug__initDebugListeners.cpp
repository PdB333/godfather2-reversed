// FUNC_NAME: Debug::initDebugListeners
// Function at 0x00977ec0: Registers two debug event listeners, then immediately removes the first one.
// Presumably part of setting up debug callbacks during initialization.
void __thiscall Debug::initDebugListeners()
{
    int listenerList;

    // Offset +0x14 into this object likely contains a pointer to a listener list (e.g., CallbackRegistry).
    if (this == 0)
        listenerList = 0;
    else
        listenerList = reinterpret_cast<int>(this) + 0x14;

    // Register first debug callback (address 0x009767b0)
    registerListener(listenerList, 0x009767b0);
    // Register second debug callback (address 0x00976800)
    registerListener(listenerList, 0x00976800);

    // Immediately remove the first callback; possibly to replace with a different handler later
    // or a bug/unintended code path.
    if (this != 0)
        removeListener(reinterpret_cast<int>(this) + 0x14, 0x009767b0, 0);
    else
        removeListener(0, 0x009767b0, 0);
}