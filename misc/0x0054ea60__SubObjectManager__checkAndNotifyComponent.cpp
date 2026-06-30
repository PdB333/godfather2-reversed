// FUNC_NAME: SubObjectManager::checkAndNotifyComponent
// Address: 0x0054ea60
// Role: Searches a sub-object's component array for a specific ID (0x1300).
//       If found, attempts to retrieve a singleton object and invokes a
//       virtual method on it with a hash. Returns success based on global state.

#include <cstdint>

// Forward declarations
struct SomeSubObject; // At offset from this

// Global functions (from external binary)
void lookupSingleton(uintptr_t** outPtr, uint32_t type); // FUN_004af8c0

// It seems unaff_ESI is a global condition flag (set by caller or global)
extern bool g_globalCondition; // unaff_ESI

class SubObjectManager {
public:
    // +0x10: byte offset to a sub-object within the manager's memory
    //        (relative to this)
    uint8_t subObjectOffset; // at offset 0x10

    // +0x78: start of a data block containing counts or parameters for
    //        sub-objects. The int at (this+0x78 + subObjectOffset) is
    //        the number of components in the sub-object's array.
    uint8_t _padding0[0x78 - 0x10 - 1]; // adjust as needed

    // The sub-object at this+subObjectOffset has its own structure.
    // For this function, we care about its +0x74 field:
    //   at +0x74: pointer to an array of uint32_t (component IDs),
    //   terminated by 0x1300.

    // Note: The exact layout is reconstructed from the decompiled logic.
    // Offsets are relative to this.

    // This method is __thiscall
    bool checkAndNotifyComponent();
};

// Static assert for offset sanity (optional)
// static_assert(offsetof(SubObjectManager, subObjectOffset) == 0x10, "Offset mismatch");

bool SubObjectManager::checkAndNotifyComponent()
{
    uint8_t subOff = this->subObjectOffset; // +0x10
    // Base pointer to the sub-object
    SomeSubObject* subObj = reinterpret_cast<SomeSubObject*>(
        reinterpret_cast<uint8_t*>(this) + subOff); // +0x00 relative

    // Read the component count from the data block at this+0x78
    // The count is at offset subOff within that block (i.e., this+0x78+subOff)
    int componentCount = *reinterpret_cast<int*>(
        reinterpret_cast<uint8_t*>(this) + 0x78 + subOff);

    // Pointer to the component ID array in the sub-object (+0x74)
    uint32_t* componentArray = *reinterpret_cast<uint32_t**>(
        reinterpret_cast<uint8_t*>(subObj) + 0x74);

    int index = 0;
    if (componentCount > 0) {
        // Search the array for the sentinel value 0x1300
        while (*componentArray != 0x1300) {
            ++index;
            ++componentArray; // advance by 4 bytes (uint32_t)
            if (componentCount <= index) {
                // Not found within the allowed count
                return false;
            }
        }

        // Found component ID 0x1300 at index
        // Now attempt to get a singleton/manager object for type 0x2001
        uintptr_t* outputPtr = nullptr;
        lookupSingleton(&outputPtr, 0x2001);
        // Ensure outputPtr is valid
        if (outputPtr != nullptr) {
            // Call virtual function at vtable offset 0x10
            // First argument: hash 0xd80c71d2
            // Second argument: pointer to the output pointer (or something)
            // The vtable pointer is at *outputPtr (base of the object)
            void* vtable = *reinterpret_cast<void**>(outputPtr);
            bool (__fastcall *virtualFunc)(uint32_t, uintptr_t**) = 
                reinterpret_cast<decltype(virtualFunc)>(
                    *reinterpret_cast<void**>(static_cast<uint8_t*>(vtable) + 0x10));
            bool result = virtualFunc(0xd80c71d2, &outputPtr);

            // Success also depends on a global condition (unaff_ESI)
            if (result && g_globalCondition) {
                return true;
            }
        }
    }

    return false;
}