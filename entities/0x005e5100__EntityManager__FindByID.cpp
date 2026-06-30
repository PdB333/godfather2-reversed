// FUNC_NAME: EntityManager::FindByID

// Function at 0x005e5100: Linear search for an object by its ID (offset +0x04) in an array stored in a container.
// __fastcall calling convention: ECX = unused (likely this pointer), EDX = pointer to container structure,
// third parameter (stack) = target ID to match.
// Container structure has:
//   +0x6014: pointer to array of pointers to objects (array of int*)
//   +0x6018: uint count of elements in the array
// Each object has an ID field at offset +0x04.

int __fastcall EntityManager::FindByID(int unusedThis, int* pContainer, int targetID)
{
    uint index = 0;
    int* pFound = 0;

    if (*(uint*)((char*)pContainer + 0x6018) != 0) {
        int** pArray = *(int***)((char*)pContainer + 0x6014);
        while (true) {
            pFound = *pArray;
            if (pFound != 0 && *(int*)((char*)pFound + 4) == targetID) {
                break;
            }
            ++index;
            ++pArray;
            if (*(uint*)((char*)pContainer + 0x6018) <= index) {
                return 0;
            }
        }
    }
    return pFound;
}