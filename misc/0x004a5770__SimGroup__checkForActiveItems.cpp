// FUNC_NAME: SimGroup::checkForActiveItems
// Function at 0x004a5770 – iterates three lists (flag arrays and object list) checking for active status (flag 0x100 or virtual method). Returns 1 if any active, else 0.
// __fastcall: param_1 in ECX (this pointer)
// Offsets documented in comments.

using namespace std;

typedef unsigned int uint;
typedef unsigned short ushort;

class SimGroup {
public:
    // +0x5c: pointer to array of SimObject* (size at +0x60)
    // +0x60: count of SimObject pointers
    // +0x68: pointer to array of 8-byte items (first ushort flags? stride 8)
    // +0x6c: count of 8-byte items
    // +0x74: pointer to array of 4-byte items (first ushort? stride 4)
    // +0x78: count of 4-byte items

    bool __fastcall checkForActiveItems() {
        uint i;
        ushort* pFlag;

        // Check first list: 4-byte stride items (flags at offset 4 from base)
        i = 0;
        if (*(uint*)(this + 0x78) != 0) {
            pFlag = (ushort*)(*(int*)(this + 0x74) + 4); // skip first ushort? Actually each item is 4 bytes, we read second ushort
            do {
                if ((*pFlag & 0x100) != 0) {
                    return true;
                }
                i++;
                pFlag += 4; // next item: stride 4 bytes
            } while (i < *(uint*)(this + 0x78));
        }

        // Check second list: 8-byte stride items (flags at offset 4 from base)
        i = 0;
        if (*(uint*)(this + 0x6c) != 0) {
            pFlag = (ushort*)(*(int*)(this + 0x68) + 4); // offset 4 into each item
            do {
                if ((*pFlag & 0x100) != 0) {
                    return true;
                }
                i++;
                pFlag += 8; // stride 8 bytes
            } while (i < *(uint*)(this + 0x6c));
        }

        // Check third list: array of pointers to objects with virtual check method
        i = 0;
        if (*(int*)(this + 0x60) != 0) {
            do {
                int* objPtr = *(int**)(*(int*)(this + 0x5c) + i * 4);
                // Vtable at objPtr, function at vtable+0x10 (offset 16 bytes) – likely a bool method
                bool (*checkFunc)() = (bool (*)())(*(int**)(objPtr)[4]); // vtable[4] = 0x10 bytes offset
                if (checkFunc()) {
                    return true;
                }
                i++;
            } while (i < *(uint*)(this + 0x60));
        }

        return false;
    }
};