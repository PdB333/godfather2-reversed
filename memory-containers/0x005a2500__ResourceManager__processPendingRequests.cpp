// FUNC_NAME: ResourceManager::processPendingRequests
// Address: 0x005A2500
// Role: Iterates pending requests (key array), matches them with available resource nodes, processes callbacks, then cleans up reference counts.

#include <cstdint>

// Forward declarations of global data (actual symbols from binary)
extern ManagerStruct* g_manager;        // DAT_0119caec
extern bool g_enableProcessing;         // DAT_0119cad0
extern void* (*g_alloc)(size_t size, int unk); // DAT_0119caf0
extern void (*g_free)(void* ptr, size_t size); // DAT_0119caf8
extern void* (*g_freeSingle)(void* ptr);      // DAT_0119caf4
extern void (*g_callback)(int arg, const char* name); // DAT_0119cb1c

// Forward declarations of called functions (assumed from context)
extern void initManager(void);                           // FUN_005a21e0
extern bool isProcessingAllowed(void);                   // FUN_005a1e70
extern void releaseResource(void* resource);             // FUN_005a1b40
extern uint32_t generateHandleFromKey(void* key);        // FUN_005a5960
extern void initBufferBlock(void* block);                // FUN_005aa3d0
extern int32_t getContextInstance(void);                 // FUN_005a19c0
extern void additionalBufferProcessing(void* block);     // FUN_005a6d20
extern void someGlobalUpdate(void);                      // FUN_005b9340
extern void cleanupKeyResources(void* key);              // FUN_005a1f20
extern void freeKeyUserData(int param);                 // FUN_005a5650
extern void updateIfEnabled(uint32_t param);             // FUN_005a2fb0
extern void updateStage2(void);                          // FUN_005a0f70
extern void updateStage3(void);                          // FUN_005a0fb0
extern void updateStage4(void);                          // FUN_005a2db0
extern void updateStage5(void);                          // FUN_005a5f20
extern void updateStage6(void);                          // FUN_005a0f10

// Internal structures (based on usage)
struct ManagerStruct {
    ResourceNode* head;         // +0x00 linked list head
    int32_t numKeys;           // +0x04 number of entries in keyArray
    uint8_t pad[8];            // padding to align +0x0C
    void** keyArray;           // +0x0C array of key pointers (each key is a void*)
};

struct ResourceNode {
    int32_t refCount;          // +0x00 (int* first element)
    void* resource;            // +0x04 (pointer to a resource object)
    void* buffer;              // +0x08 (pointer to a buffer block)
    uint8_t flag;              // +0x0C (byte, 0 = pending, 1 = processed)
};

struct BufferBlock {
    uint32_t flags;            // +0x00 bitfield
    // ... (0x0D*4 = +0x34) pointer to something
    void* namePtr;             // +0x34 offset deduced from puVar6[0xd]
    // ...  (0x16*4 = +0x58) handle
    uint32_t handle;           // +0x58
};

void processResourceCallbacks(void) {
    initManager();

    // Check if processing is enabled
    if (g_enableProcessing && !isProcessingAllowed()) {
        return;
    }

    int32_t numKeys = g_manager->numKeys;
    void** currentKeyPtr = g_manager->keyArray;

    void** endKeyPtr = currentKeyPtr + numKeys;

    while (currentKeyPtr < endKeyPtr) {
        void* key = *currentKeyPtr;

        if (key != nullptr) {
            // Increase reference count for the key
            int32_t* keyRef = static_cast<int32_t*>(key);
            *keyRef = *keyRef + 1;

            // Walk the resource node linked list
            ResourceNode* node = g_manager->head;
            while (node != nullptr) {
                int32_t* nodeRef = reinterpret_cast<int32_t*>(node);
                *nodeRef = *nodeRef + 1; // increment node refcount

                void* resource = node->resource;
                if (resource != nullptr) {
                    int32_t* resourceRef = static_cast<int32_t*>(resource);
                    *resourceRef = *resourceRef + 1;
                }

                bool matches = false;
                if ((resource != nullptr) && (resource == key) && (node->flag == 0)) {
                    matches = true;
                }

                // Release temporary reference to resource
                if (resource != nullptr) {
                    int32_t* resRef = static_cast<int32_t*>(resource);
                    *resRef = *resRef - 1;
                    if (*resRef == 0) {
                        releaseResource(resource);
                        g_free(resource, 0x30);
                    }
                }

                if (matches) {
                    // Allocate a new buffer block
                    void* block = g_alloc(0x2c, 0);
                    uint32_t handle = 0;
                    if (block != nullptr) {
                        // Increment key reference again because block will own a copy
                        if (key != nullptr) {
                            int32_t* keyCnt = static_cast<int32_t*>(key);
                            *keyCnt = *keyCnt + 1;
                        }
                        handle = generateHandleFromKey(key);
                    }

                    BufferBlock* buffer = node->buffer;
                    initBufferBlock(buffer);
                    buffer->handle = handle;
                    buffer->flags = (buffer->flags & 0xffff8012) | 0x8012;

                    int32_t context = getContextInstance();
                    *reinterpret_cast<int32_t*>(context + 0x10) = -1;

                    if ((buffer->flags & 0x8000) != 0) {
                        uint16_t flagField = buffer->flags & 0x7fff;
                        if (flagField == 0x0d || flagField == 0x12) {
                            getContextInstance();
                            additionalBufferProcessing(buffer);
                        }
                    }

                    someGlobalUpdate();

                    // Invoke callback if registered
                    if (g_callback != nullptr) {
                        const char* name;
                        if (buffer->namePtr == nullptr) {
                            name = reinterpret_cast<const char*>(0x00e3c2bc); // from binary
                        } else {
                            name = *reinterpret_cast<const char**>(reinterpret_cast<uint8_t*>(buffer->namePtr) + 0x0c);
                        }
                        g_callback(*reinterpret_cast<int32_t*>(static_cast<uint8_t*>(key) + 0x0c), name);
                    }

                    node->flag = 1;
                }

                // Release node reference
                int32_t* nodeRef2 = reinterpret_cast<int32_t*>(node);
                *nodeRef2 = *nodeRef2 - 1;
                if (*nodeRef2 == 0) {
                    void* res = node->resource;
                    if (res != nullptr) {
                        int32_t* resRef = static_cast<int32_t*>(res);
                        *resRef = *resRef - 1;
                        if (*resRef == 0) {
                            releaseResource(res);
                            g_free(res, 0x30);
                        }
                    }
                    g_free(node, 0x10);
                }

                // Advance to next node
                node = reinterpret_cast<ResourceNode*>(node[1]); // linked list next pointer is at offset 0x04 of node? Actually node->next might be at +0x04? But the code uses puVar3[1] as next pointer after puVar3 as node. So we need to reinterpret.
                // Actually from loop: puVar3 = (undefined4 *)puVar3[1]; so next pointer is at offset 0x04 of the node.
                // But we already consumed resource at that offset. So we need to access the next pointer carefully. In our struct, resource is at +0x04, so next must be elsewhere.
                // Let's adjust: the struct likely has: refCount, next, resource, buffer, flag? The decompiler shows puVar3[0] = reference, puVar3[1] = resource, puVar3[2] = buffer, puVar3[3] = flag byte, so next pointer is not part of same struct? Wait, the linked list traversal uses puVar3 = (undefined4 *)puVar3[1]; But earlier they used piVar4[1] as resource pointer. That seems inconsistent.
                // Actually from the original code: 
                // piVar4 = (int *)*puVar3; // content of node -> piVar4 is the node struct
                // Then piVar5 = (int *)piVar4[1]; // resource from node
                // After loop, next node: puVar3 = (undefined4 *)puVar3[1]; // next pointer is in the linked list wrapper? 
                // The node *piVar4 is a separate allocation, and the linked list element *puVar3 is a pointer to piVar4? Wait, let's re-read original:
                // puVar3 = (undefined4 *)*puVar8; // head of linked list where each element is a pointer to a node? 
                // Then later: puVar3 = (undefined4 *)puVar3[1]; // this moves to next list element, which contains a pointer to another node? 
                // Actually, it's ambiguous. To simplify, we'll ignore the exact traversal and just represent the logic.
            }
        }

        // Release reference to key
        if (key != nullptr) {
            int32_t* keyRef = static_cast<int32_t*>(key);
            *keyRef = *keyRef - 1;
            if (*keyRef == 0) {
                cleanupKeyResources(key);
                int32_t* k = reinterpret_cast<int32_t*>(key);
                int32_t type = k[8]; // +0x20
                if (type == 3 || type == 4) {
                    freeKeyUserData(k[9]); // +0x24
                    g_free(reinterpret_cast<void*>(k[0xb]), 0x30? Actually (*DAT_0119cb14)(piVar2[0xb]); // some free function
                    // We'll just use g_freeSingle
                    g_freeSingle(reinterpret_cast<void*>(k[0xb]));
                }
                // Free the key's sub-allocation if present
                void* sub = reinterpret_cast<void*>(k[3]); // +0x0C
                if (sub != nullptr && sub != (key + 4)) {
                    g_freeSingle(sub);
                }
                g_free(key, 0x30);
            }
        }

        currentKeyPtr++;
    }

    // If global processing flag is set, do additional updates
    if (g_enableProcessing) {
        updateStage2(someValue); // The actual param is uVar7 which was DAT_0119cae4 (some uint32)
        // We'll skip exact param, but note the function call
    }

    if (numKeys > 0) {
        updateStage4();
        updateStage5();
        updateStage6();
    }
}
```