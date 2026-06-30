// FUN_NAME: SomeManager::addEntry

#include <cstdint>

// Forward declarations of helper functions
void* allocateNode(int32_t size);                           // FUN_009c8e50 - memory allocator
void* findObject(void* base, int32_t index);                // FUN_00446130 - find child object at offset
void handleAllocationFailure();                             // FUN_00449e90 - failure handler

// Reconstructed code for function at 0x004e9720
// __thiscall: 'this' passed in EAX
// param_1: some argument forwarded to the child object's virtual method
int32_t** SomeManager::addEntry(int32_t param_1) {
    int32_t* thisPtr = reinterpret_cast<int32_t*>(this);
    
    // Check if 'this' is valid (common safety check)
    if (thisPtr == nullptr) {
        return nullptr;
    }
    
    // Access child object at offset +0x50 from 'this'
    int32_t* childObj = static_cast<int32_t*>(findObject(thisPtr + 0x50, 0));
    if (childObj == nullptr) {
        return nullptr;
    }
    
    // Call virtual method at vtable offset +0x28 on childObj
    // vtable is at *childObj, then call [vtable+0x28] with param_1
    typedef void (*VirtualMethod)(int32_t*);
    VirtualMethod method = *reinterpret_cast<VirtualMethod*>(
        *reinterpret_cast<uint8_t**>(childObj) + 0x28
    );
    method(reinterpret_cast<int32_t*>(param_1));
    
    // Allocate 8 bytes for a new linked list node
    int32_t** newNode = static_cast<int32_t**>(allocateNode(8));
    if (newNode == nullptr) {
        handleAllocationFailure();
        return nullptr;
    }
    
    // Initialize node:
    // newNode[0] = pointer to childObj + 0x12 (offset 0x48) 
    // newNode[1] = next pointer (initially 0, then updated)
    newNode[0] = reinterpret_cast<int32_t*>(&childObj[0x12]); // +0x12
    newNode[1] = nullptr;
    
    // Check if the head pointer (childObj + 0x13) is null
    int32_t** headPtr = reinterpret_cast<int32_t**>(&childObj[0x13]); // offset 0x4C
    if (*headPtr == nullptr) {
        return newNode;
    }
    
    // Insert at head: newNode->next = current head
    newNode[1] = *headPtr;
    // Update head to newNode
    *headPtr = newNode;
    
    return newNode;
}