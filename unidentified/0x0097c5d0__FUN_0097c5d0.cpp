// FUNC_NAME: unknown::updateRegisteredObjects
void __thiscall SomeManager::updateRegisteredObjects(int thisPtr)
{
    uint i = 0;
    // +0xA0: some flag indicating pending update / dirty state, cleared here
    *(int*)(thisPtr + 0xA0) = 0;

    uint count = *(uint*)(thisPtr + 0xDC); // +0xDC: number of registered objects
    if (count != 0)
    {
        // +0xD8: pointer to array of object pointers
        int** arrayBase = *(int***)(thisPtr + 0xD8);
        do
        {
            int* obj = arrayBase[i];          // each object is a pointer to its vtable
            // Call the second virtual function (vtable slot +4) – typically update/tick
            (*(void (__thiscall**)(int))(*(int*)obj + 4))(obj);
            i++;
        } while (i < count);
    }
}