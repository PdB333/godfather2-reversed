// FUNC_NAME: SomeStatefulObject::clearStateFlags
// Address: 0x00766440
// Clears specified state flags (at offset +0xc88) and triggers a callback 
// via a sub-object at +0x58 if the state actually changed.

void __thiscall SomeStatefulObject::clearStateFlags(uint32 flagsToClear)
{
    // +0xc88: flags bitfield (state)
    uint32* stateFlags = reinterpret_cast<uint32*>(reinterpret_cast<uint8*>(this) + 0xc88);
    uint32 oldFlags = *stateFlags;
    uint32 newFlags = oldFlags & ~flagsToClear;

    // Only perform side-effects if the cleared bits were actually set
    if (newFlags != oldFlags)
    {
        // +0x58: pointer to a sub-object (e.g., state manager, event dispatcher)
        void* subObject = *reinterpret_cast<void**>(reinterpret_cast<uint8*>(this) + 0x58);
        // +0x28: virtual function slot (slot 10 if 4-byte vtable entries)
        // This callback is called with argument 0x10 (e.g., notification code)
        typedef void (__thiscall *CallbackFunc)(void*, int);
        CallbackFunc callback = *reinterpret_cast<CallbackFunc*>(
            reinterpret_cast<uint8*>(subObject) + 0x28);
        callback(subObject, 0x10);

        // Finally clear the requested flags
        *stateFlags = newFlags;
    }
}