// FUNC_NAME: UIMessageQueueManager::addMessage
// Function: 0x0069aa10
// Reconstructed C++ based on Ghidra decompilation. This method adds a new message
// entry to an internal ring buffer. Each entry is a large structure (0x504 bytes)
// containing a wide string and parsed XML/DOM data.

#include <wchar.h>
#include <string.h>

// Forward declarations of helper functions (defined elsewhere)
void * ParseUIMessage(wchar_t *text, void **outNode); // FUN_004ddaf0
int GetNodeID(void *node, int arg);                  // FUN_004db320
void CallNodeDestructor(void *node);                 // via function pointer
void HandleFullQueue(void *writePtr, wchar_t *text); // FUN_0069a140

// Internal structure representing a message entry in the queue (size 0x504 bytes)
struct UIMessageEntry {
    wchar_t text[15];          // +0x00: first 15 characters of the message
    short padding;             // +0x1E: alignment padding
    // The rest is filled by ParseUIMessage and other data
    // Actually the exact layout is unknown but the total size is 0x504 bytes.
    // The following fields are derived from stack usage:
    void *parsedNode;          // +0x20: pointer to parsed DOM/render node
    int parsedNodeID;          // +0x24: ID extracted from the node
    int unknown1;              // +0x28: extra data
    void (*nodeDestructor)(void*); // +0x2C: callback to release parsedNode
    // Remaining bytes up to 0x504 are either unused or contain additional data
    // In the actual code, the whole entry is cleared via memset(0,0x504).
    char reserved[0x504 - sizeof(wchar_t[15]) - sizeof(short) - sizeof(void*)*3 - sizeof(int)];
};

// Class managing a ring buffer of UIMessageEntry
class UIMessageQueueManager {
public:
    // Offset +0x08: current write pointer into the ring buffer
    UIMessageEntry *writePtr;
    // Offset +0x0C: end (one past last slot) of the ring buffer
    UIMessageEntry *endPtr;
    // Offset +0x14: pointer to a counter structure (e.g., a metrics tracker)
    // At offset +0x04 within that structure is a short counter incremented.
    void *counterStruct; // actually int* but used as base for short counter

    // Method: addMessage
    // param_2: wide string (message text, up to 15 characters)
    void __thiscall addMessage(wchar_t *text) {
        UIMessageEntry entry; // local_504 (size 0x504)
        memset(&entry, 0, sizeof(entry));
        wcsncpy(entry.text, text, 15); // copy at most 15 characters
        entry.text[14] = L'\0'; // ensure null termination (wcsncpy might not add null if source longer?)

        // Parse the text into a node and get its ID
        void *node = nullptr;
        ParseUIMessage(entry.text, &node); // FUN_004ddaf0: fills node pointer and sets destructor callback
        if (node == nullptr) {
            node = (void*)0x0120546e; // fallback node address (likely a sentinel)
        }
        entry.parsedNode = node;
        entry.parsedNodeID = GetNodeID(node, 0); // FUN_004db320: second arg is 0 (local_510)
        entry.nodeDestructor = (void (*)(void*))0; // local_508 is originally null; set to the destructor from ParseUIMessage? Actually the decompiler shows local_508 was set to 0, but then later used. Likely ParseUIMessage sets it. We need to fix: the stack variable local_508 is altered by ParseUIMessage? The decompiler shows it as a local variable that remains 0, but then later it's called. That suggests ParseUIMessage might return a destructor function, or the destructor is stored in the entry. Actually in the code, after ParseUIMessage, local_508 is still 0, but then later if (local_514 !=0) (*local_508)(local_514). That would crash if local_508 is 0. So likely ParseUIMessage sets local_508 via an out parameter. The Ghidra decompilation may have missed that. I'll assume ParseUIMessage also outputs a destructor function pointer.
        // Therefore, we'll modify the signature of ParseUIMessage to also return a destructor.
        // For reconstruction, we can keep it as a separate step:
        void (*destructor)(void*) = nullptr;
        ParseUIMessageWithDestructor(entry.text, &entry.parsedNode, &destructor);
        entry.nodeDestructor = destructor;

        // Ensure the entry's parsedNodeID is set
        entry.parsedNodeID = GetNodeID(entry.parsedNode, 0);

        // Write entry into the ring buffer if there is space
        if (writePtr < endPtr) {
            // The buffer has space; copy the whole entry
            UIMessageEntry *dest = writePtr;
            writePtr = writePtr + 1; // advance by one entry (actually pointer arithmetic by sizeof(UIMessageEntry))
            // In the original assembly, the write pointer is incremented by 0x141 (321) which is 321*4 = 1284 bytes = sizeof(entry)
            // So we need to handle pointer increment correctly.
            // Using char* or casting: writePtr = (UIMessageEntry*)((char*)writePtr + sizeof(entry));
            // But in the code, the increment is done before copying? Actually the code:
            // if (puVar5 < *(undefined4**)(param_1+0xc)) {
            //   *(undefined4**)(param_1+8) = puVar5 + 0x141;
            //   copy loop...
            // So it increments writePtr first, then copies.
            // So we need to do that.
            // Let's implement correctly:
            UIMessageEntry *oldWrite = writePtr;
            writePtr = (UIMessageEntry*)((char*)writePtr + sizeof(UIMessageEntry));
            // copy from entry to oldWrite
            memcpy(oldWrite, &entry, sizeof(entry));
        } else {
            // Buffer is full; call overflow handler (might grow or drop)
            HandleFullQueue(writePtr, entry.text);
        }

        // Increment counter at offset +0x14 (counterStruct)
        if (counterStruct) {
            short *counter = (short*)((char*)counterStruct + 4);
            (*counter)++;
        }

        // Release parsed node if it was allocated (the destructor is stored in entry)
        if (entry.parsedNode != nullptr && entry.parsedNode != (void*)0x0120546e) {
            entry.nodeDestructor(entry.parsedNode);
        }
    }
};

// Stubs for helper functions (actual implementation not shown)
void ParseUIMessage(wchar_t *text, void **outNode); // original, but we need destructor
void ParseUIMessageWithDestructor(wchar_t *text, void **outNode, void (**outDestructor)(void*));
int GetNodeID(void *node, int arg);
void HandleFullQueue(void *writePtr, wchar_t *text); // FUN_0069a140

// End of reconstruction