// FUNC_NAME: getHandleIfActive
// Function address: 0x006b1a40
// Returns the value at offset 0xCC if the flag at 0x16C is zero, otherwise returns 0.
// This is likely a getter for a component handle that is only valid when the object is active/alive.

int __thiscall getHandleIfActive(void* this)
{
    int handle = *(int*)((char*)this + 0xCC);
    if (*(int*)((char*)this + 0x16C) != 0) {
        handle = 0;
    }
    return handle; // returns handle or 0
}