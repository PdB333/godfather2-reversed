// FUNC_NAME: findAndActivateFirstObject
// Address: 0x00822850
// Iterates a pool of up to count objects (stored at this+0x3c) and calls a helper to retrieve
// an object matching the provided ID. If found, calls its first virtual method with argument 1.
// Returns 1 on success, 0 if no match is found within the pool limit.

int __thiscall findAndActivateFirstObject(int thisPtr, int objectId)
{
    int idx = 0;
    if (*(int *)(thisPtr + 0x3c) != 0) {
        do {
            // Retrieves an object pointer associated with the given ID
            void *obj = (void *)FUN_00822410(objectId);
            if (obj != (void *)0x0) {
                // Call the first virtual function (vtable[0]) with argument 1 (likely activate/start)
                (*(void (__thiscall **)(void *, int))(**(int **)obj))(obj, 1);
                return 1;
            }
            idx++;
        } while (idx < *(unsigned int *)(thisPtr + 0x3c));
    }
    return 0;
}