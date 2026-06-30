// FUNC_NAME: ObjectRegistry::lookupAndInvokeObject
// Address: 0x00652a50
// Role: Searches a global linked list of registered objects by name, and if found, invokes the second virtual method on the object, returning its result.

#include <cstdint>

// Forward declarations
struct RegistryNode;
struct RegisteredObject;

// Global head of the linked list of registered objects
extern RegistryNode* g_registryHead;

// Structure for a node in the registry list
struct RegistryNode {
    RegistryNode*    next;          // +0x00
    RegisteredObject* object;       // +0x04
    uint8_t          enabled;       // +0x08 (flag byte)
    // +0x09 padding
};

// Base class for objects that can be registered
struct RegisteredObject {
    virtual ~RegisteredObject() {}
    virtual uint32_t secondVirtual() = 0;  // vtable offset 0x04
    // Names are embedded directly at offset 0x20
    wchar_t name[32];  // +0x20 (actual size might differ, typical 32 wchars)
};

uint32_t ObjectRegistry::lookupAndInvokeObject(const wchar_t* searchName) {
    // unaff_EDI held the searchName parameter (passed by EDI or implicit)
    RegistryNode* node = g_registryHead;
    while (node != nullptr) {
        if (node->enabled != 0) {
            // Compare name at object+0x20 with searchName (wide string comparison)
            const wchar_t* objectName = node->object->name;
            const wchar_t* key = searchName;
            int cmpResult;
            do {
                wchar_t oc = *objectName;
                wchar_t kc = *key;
                if (oc != kc) {
                    cmpResult = (oc < kc) ? -1 : 1;
                    break;
                }
                if (oc == 0) {
                    cmpResult = 0;
                    break;
                }
                objectName++;
                key++;
            } while (true);
            if (cmpResult == 0) {
                // Match found: call the second virtual method on the object
                return node->object->secondVirtual();
            }
        }
        node = node->next;
    }
    return 0;
}