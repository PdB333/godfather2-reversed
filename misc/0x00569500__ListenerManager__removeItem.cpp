// FUNC_NAME: ListenerManager::removeItem
// Address: 0x00569500
// This function removes an item from a dependency-managed list (m_itemList).
// When the last item is removed, it optionally triggers cleanup and notifies dependent objects (m_dependentList).

class ListenerManager {
public:
    // Virtual table offsets (relative to vtable pointer at offset 0):
    // +0: destructor (implicit)
    // +8: shouldCleanup() – returns false to indicate cleanup should proceed
    // +0x10: performCleanup()
    // +0x40: notifyDependent(void* dependent)

    // Field offsets (relative to this pointer):
    // +0x00: vtable pointer
    // +0x04: ... (unused in this function)
    // +0x08: m_itemList (array of int* or handles) (index 2)
    // +0x1C: m_itemCount (index 7)
    // +0x228: m_dependentList (array of int* or handles) (index 0x8a)
    // +0x328: m_dependentCount (index 0xca)

    void __thiscall removeItem(int item) {
        int count = this->m_itemCount;
        int index = 0;
        if (count != 0) {
            int* list = this->m_itemList;
            // Search for the item in m_itemList
            while (list[index] != item) {
                index++;
                if (count <= (unsigned int)index) {
                    return; // Item not found
                }
            }

            // If this is the last item and shouldCleanup() returns false (meaning we should cleanup)
            if ((count == 1) && ((*(char* (__thiscall**)(ListenerManager*))((int*)(this->vtable) + 2))(this) == 0)) {
                // Perform cleanup: call virtual and global functions
                (*(void (__thiscall**)(ListenerManager*))((int*)(this->vtable) + 4))(this);
                // Global shutdown handler (address 0x00ab4db0 with DAT_00e2cbe8)
                someGlobalShutdownFunc(&DAT_00e2cbe8);
                // Notify all dependent objects
                int depCount = this->m_dependentCount;
                if (depCount != 0) {
                    int* depList = this->m_dependentList;
                    for (int i = 0; i < depCount; i++) {
                        (*(void (__thiscall**)(ListenerManager*, void*))((int*)(this->vtable) + 0x10))(this, (void*)depList[i]);
                    }
                }
                // Finalize global state (address 0x00ab4e70)
                someOtherGlobalFunc();
            }

            // Remove the element from m_itemList by shifting remaining items
            count = this->m_itemCount;
            if (index < count) {
                if (index < count - 1) {
                    this->m_itemList[index] = this->m_itemList[count - 1];
                }
                this->m_itemCount = count - 1;
            }
        }
    }

private:
    // Fields assumed based on code
    void* vtable;                // +0x00
    // padding/other fields
    int m_itemList[];            // +0x08 (array of ints)
    int m_itemCount;             // +0x1C
    int m_dependentList[];       // +0x228
    int m_dependentCount;        // +0x328
};

// External functions (addresses known from decompilation)
void someGlobalShutdownFunc(void* param);  // 0x00ab4db0
void someOtherGlobalFunc(void);            // 0x00ab4e70

// Global data address
extern int DAT_00e2cbe8;