// FUNC_NAME: SomeManager::isSlotActive
// Reconstructed C++ for function at 0x00625790
// This function checks if a slot (1-based index) is valid and active.
// The class has two pointers at offsets +0x8 (end) and +0xc (array base pointer?).
// Each slot is an 8-byte structure with a type ID (offset +0) and a data pointer (offset +4).
// Type ID 6 is checked, and a byte at data[6] must be non-zero.

class SomeManager {
public:
    // Returns true if the slot at the given index is active (type 6 and active flag set).
    // If index < 1, uses a default entry from external function.
    bool __thiscall isSlotActive(int index) {
        int* entryPtr;
        if (index < 1) {
            // Get default entry from external function (e.g., empty slot placeholder)
            entryPtr = (int*)FUN_00625430();
        } else {
            // Calculate pointer to slot entry: base pointer + (index-1)*8
            int* basePtr = *(int**)(this + 0xc);
            entryPtr = (int*)(basePtr - 2 + index * 2); // -2 because 8 bytes = 2 ints
            // Check if entry is beyond the end boundary
            if (*(int**)(this + 0x8) <= entryPtr) {
                return false;
            }
        }
        // Check entry validity: type ID must be 6, and byte at data[6] must be non-zero
        if (entryPtr != nullptr && *entryPtr == 6) {
            char* data = (char*)*(entryPtr + 1); // second int is a pointer to data
            if (data != nullptr && data[6] != '\0') {
                return true;
            }
        }
        return false;
    }
};

// Assume FUN_00625430 is a helper that returns a pointer to a default/empty slot structure.
int* __cdecl FUN_00625430();