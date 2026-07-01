// FUNC_NAME: ObjectManager::findAndProcessIndex
// Address: 0x008557f0
// Role: Finds an object in an internal array by pointer/ID and processes its index.
// The array is at +0x0C, count at +0x48. If found, calls processFoundIndex with the index;
// otherwise calls with -1 (0xFFFFFFFF).

void __thiscall ObjectManager::findAndProcessIndex(int thisPtr, int targetObject)
{
    uint count = *(uint *)(thisPtr + 0x48); // number of objects
    uint index = 0;
    uint foundIndex = 0xFFFFFFFF; // sentinel for not found

    if (count != 0) {
        while (true) {
            foundIndex = index; // current index to try
            if (*(int *)(thisPtr + 0x0C + index * 4) == targetObject) {
                break; // found match
            }
            index++;
            if (index >= count) {
                foundIndex = 0xFFFFFFFF; // not found, fallback
                break;
            }
        }
    }

    // Process the found index (or -1 if not found)
    processFoundIndex(foundIndex);
}