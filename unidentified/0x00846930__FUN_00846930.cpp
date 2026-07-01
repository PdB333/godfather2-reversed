// FUNC_NAME: SomeManager::traverseAndCleanup
void __fastcall SomeManager::traverseAndCleanup(SomeManager* this)
{
    int* handle;
    int* end;
    int object;

    while (true) {
        // Process the dynamic array of handles at +0x10c (base) and +0x110 (count)
        // Each element is 8 bytes (two ints). Only the first int is used as a handle.
        handle = *(int**)((int)this + 0x10c); // base pointer to array of pairs
        if (handle != handle + *(int*)((int)this + 0x110) * 2) { // count > 0?
            end = (int*)(*(int*)((int)this + 0x10c) + *(int*)((int)this + 0x110) * 8);
            do {
                object = *handle;
                if ((object != 0) && (object != 0x48)) {
                    // object is a handle (likely offset from actual object by +0xC)
                    FUN_004088c0(object - 0xc); // cleanup/release the object
                }
                handle += 2; // move to next pair
            } while (handle != end);
        }
        // Call another traversal function (maybe recursively or for sibling list)
        FUN_00846830();
        // Check linked list via next pointer at +0x120
        int nextPtr = *(int*)((int)this + 0x120);
        if ((nextPtr == 0) || (nextPtr == 0x48))
            break;
        int nextObj = (nextPtr == 0) ? 0 : (nextPtr - 0x48);
        if (nextObj == (int)this)
            return; // cycle detection
        // Move to next node in the linked list
        this = (nextPtr == 0) ? 0 : (SomeManager*)(nextPtr - 0x48);
    }
}