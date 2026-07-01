// FUNC_NAME: InputDeviceManager::getActionBindingByIndex
// Address: 0x008d6ad0
// Returns a pointer to the action binding structure at the given index within the array stored at offset +0x44.
// Each binding entry is 0x14 bytes in size.

int __thiscall InputDeviceManager::getActionBindingByIndex(int this, int index)
{
    // Array base: this + 0x44; each element size: 0x14.
    return this + 0x44 + index * 0x14;
}