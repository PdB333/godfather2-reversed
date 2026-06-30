// FUNC_NAME: EARS::Stream::StreamHandle::assign
// Address: 0x006fe6b0
// Reconstructed from Ghidra decompilation for The Godfather 2 (x86, EARS engine)
// Handles assignment of a stream handle: copies callback state, manages node list membership,
// and delegates to FUN_006fe4b0.

#include <cstdint>

// Forward declarations for external functions
void __fastcall FUN_004daf90(int* ptr);          // Releases a node reference (e.g., decrements count)
uint32_t FUN_006fe4b0(int streamId, uint32_t arg1, uint32_t arg2); // Core assignment logic

// Internal structure of a node in the list (located at container + 0x48)
// Offset 0x00: unknown data (not used here)
// Offset 0x04: previous node pointer (points to StreamHandle::nodePtr)
struct Node {
    char data[4];    // +0x00
    int* prev;       // +0x04 (int**) – points to the owning handle's nodePtr field
};

class StreamHandle {
public:
    // Field offsets (each 4 bytes):
    // +0x00: callback – function pointer to close/stop handler
    // +0x04: callbackArg – value passed as third argument to callback
    // +0x08: unused
    // +0x10: nodePtr – pointer to the Node this handle represents
    // +0x14: prevNode – saved previous value of node->prev (list head)
    // +0x18: context – first argument to callback
    // +0x1C: state – handle state (0=inactive, 3=error?, 4=closed)

    typedef void (__thiscall *Callback)(void* context, int reason, int value);

    Callback callback;      // +0x00
    int callbackArg;        // +0x04
    // padding at +0x08, +0x0C (unused)
    Node* nodePtr;          // +0x10
    Node* prevNode;         // +0x14
    void* context;          // +0x18
    int state;              // +0x1C
};

__declspec(naked) void __fastcall FUN_004daf90(int* ptr);
uint32_t __fastcall FUN_006fe4b0(int streamId, uint32_t arg1, uint32_t arg2);

uint32_t __thiscall StreamHandle::assign(
    int streamId,           // param_2: handle to the underlying stream/resource
    StreamHandle* other,    // param_3: source handle to copy from (if not same)
    void* container,        // param_4: pointer to container object; its internal node is at +0x48
    uint32_t arg1,          // param_5: passed to FUN_006fe4b0
    uint32_t arg2           // param_6: passed to FUN_006fe4b0
)
{
    uint32_t result = 0;

    if (streamId != 0) {
        // If callback exists and state is not closed(4), inactive(0) or error(3),
        // call the callback to close the previous stream (reason 4)
        if (callback != nullptr && state != 4 && state != 0 && state != 3) {
            callback(context, 4, callbackArg);
        }

        // Copy first two fields from other handle if different objects
        if (this != other) {
            callback = other->callback;
            callbackArg = other->callbackArg;
        }

        // Locate the node inside the container (offset 0x48)
        Node* newNode = (container != nullptr) ? (Node*)((uint8_t*)container + 0x48) : nullptr;

        // Update the node pointer and rewire the list
        if (nodePtr != newNode) {
            if (nodePtr != nullptr) {
                FUN_004daf90(reinterpret_cast<int*>(&nodePtr));
            }
            nodePtr = newNode;
            if (newNode != nullptr) {
                prevNode = reinterpret_cast<Node*>(newNode->prev);
                newNode->prev = reinterpret_cast<int*>(&nodePtr);
            }
        }

        // Delegate to underlying assignment function
        result = FUN_006fe4b0(streamId, arg1, arg2);
    }

    return result;
}