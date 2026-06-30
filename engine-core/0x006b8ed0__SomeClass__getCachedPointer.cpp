// FUNC_NAME: SomeClass::getCachedPointer
#include <cstdint>

// Forward declarations of external functions
int __fastcall FUN_006b0ee0(void* ptr);  // Likely a getter/handler on the pointed object
void* __fastcall FUN_00446100(void* hashMap, int key); // Returns a node pointer from a hash map

int __fastcall SomeClass::getCachedPointer(void* thisPtr) {
    uint8_t* base = reinterpret_cast<uint8_t*>(thisPtr);
    
    // Check if we have a cached pointer at offset 0x60
    void* cachedPtr = *reinterpret_cast<void**>(base + 0x60);
    if (cachedPtr != nullptr) {
        // Use the cached pointer and call a helper function
        return FUN_006b0ee0(cachedPtr);
    }
    
    // Look up in the hash map at offset 0x64 with key 0
    void* mapNode = FUN_00446100(reinterpret_cast<void*>(base + 0x64), 0);
    if (mapNode != nullptr) {
        // Call virtual function at vtable offset 0x10 (index 4) on the node
        // This function likely checks if a given hash exists (0x6f1d0554)
        typedef bool (__thiscall* ContainsFunc)(void*, uint32_t);
        bool exists = reinterpret_cast<ContainsFunc>(
            *reinterpret_cast<uintptr_t**>(mapNode)[4]
        )(mapNode, 0x6f1d0554);
        
        if (exists) {
            // Return the value stored at byte offset 0x60 from the map node
            // This is interpreted as an int (may be a handle or pointer)
            return *reinterpret_cast<int*>((uint8_t*)mapNode + 0x60);
        }
    }
    return 0;
}