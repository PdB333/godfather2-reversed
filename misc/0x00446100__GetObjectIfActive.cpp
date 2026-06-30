// FUNC_NAME: GetObjectIfActive
// 0x00446100: Checks if an object resolved from a handle has the active flag (bit 27 at +0x14) set.
// Returns the object pointer if yes, otherwise null.
int GetObjectIfActive(int handle, int argUnknown)
{
    int objPtr = resolveObjectFromHandle(handle, argUnknown); // e.g., SimObject* from ID
    if ((objPtr != 0) && ((*(uint*)(objPtr + 0x14) & 0x8000000) != 0)) {
        return objPtr;
    }
    return 0;
}