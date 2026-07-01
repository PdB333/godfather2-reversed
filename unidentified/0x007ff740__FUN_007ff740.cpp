// FUNC_NAME: UnknownClass::checkAndUpdateResolvedHandle
// Function at 0x007ff740: Updates a tracked handle/resolved ID, calls virtual callback on change.
// Accesses offsets 0x108 (264th int) and 0x7B9 (1977th int) from this.
// Uses constant -0x1E98FD1 (~ -32083921) as sentinel for uninitialized handle.
// Calls helper FUN_00405af0 to resolve the handle to an int (new ID).
// Calls virtual method at vtable+0x2F0 if the resolved ID changes and is non-zero.
void __thiscall checkAndUpdateResolvedHandle(void *thisObj)
{
    int *this = (int *)thisObj;
    int newId = 0;
    int handle = this[0x108 / 4]; // +0x420: current handle (e.g., object ID or identifier)
    if (handle != -0x1E98FD1) {
        newId = FUN_00405af0(handle); // resolve handle to an internal ID (e.g., entity pointer index)
    }
    if (newId != this[0x7B9 / 4] && newId != 0) { // compare to stored resolved ID at +0x1EE4
        (**(void (__thiscall **)(int))(*(int *)this + 0x2F0))(newId); // call virtual function (e.g., onTargetChanged)
        this[0x7B9 / 4] = newId; // update stored resolved ID
    }
}