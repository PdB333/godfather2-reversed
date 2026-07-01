// FUNC_NAME: ObjectWithLists::cleanupList
// Address: 0x0097cd60
// Role: Removes all elements from an internal list (offset 0x30 count, offset 0xc array of pointers).
//       After each removal, checks if all reference counts (offsets 0x54, 0x78, 0x9c, 0x30) are zero.
//       If so, clears a flag (offset 0xa0) and invokes a list of callbacks (offset 0xd8 array of pointers to structs with function pointer at +0x04, count at 0xdc).

class ObjectWithLists {
public:
    // Offsets relative to this pointer (0x00)
    // +0x0c: int* m_array1; // array of pointers (size unknown, count at +0x30)
    // +0x30: int m_count1;
    // +0x54: int m_count2;
    // +0x78: int m_count3;
    // +0x9c: int m_count4;
    // +0xa0: int m_flag; // set to 0 when all counts are zero
    // +0xd8: CallbackEntry** m_callbackArray; // array of pointers to CallbackEntry
    // +0xdc: int m_callbackCount;

    struct CallbackEntry {
        int unknown;      // +0x00
        void (*func)();   // +0x04
    };

    void __fastcall cleanupList() {
        int count = this->m_count1;
        if (count != 0) {
            // Point to one past the last element of m_array1
            int* arrayEnd = &this->m_array1[count];
            int idx = count;
            do {
                idx--;
                this->m_count1--;
                // If the removed element is not the last, copy the last element into its place
                if (idx != this->m_count1) {
                    *arrayEnd = this->m_array1[this->m_count1];
                }
                // Check if all reference counts are zero
                if (this->m_count1 + this->m_count2 + this->m_count3 + this->m_count4 == 0) {
                    this->m_flag = 0;
                    // Invoke all registered callbacks
                    for (uint i = 0; i < this->m_callbackCount; i++) {
                        this->m_callbackArray[i]->func();
                    }
                }
                arrayEnd--;
                count--;
            } while (count != 0);
        }
    }
};