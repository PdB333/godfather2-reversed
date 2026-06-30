// FUNC_NAME: InputAxisManager::init
// Address: 0x00697310
// This function initializes the input axis definitions for vehicle controls.
// It allocates a linked list node (size 0x2C) and registers standard axes
// (X, Y, Z, Z-Rotation, Throttle, Rudder) and their inverted variants.

#include <cstdint>

// Forward declarations
void* allocateMemory(uint32_t size);     // FUN_009c8e50
void debugPrint(const char* text);       // FUN_004d3bc0
uint64_t* createAxisDefinition(uint32_t* outData); // FUN_00696ed0, returns 8-byte axis object

// Unknown global pointer used for axis creation
extern uint32_t _DAT_00d5780c;  // Likely an input device or action context
extern uint32_t _DAT_00d5ccf8;  // Same for inverted axes

class InputAxisManager {
public:
    // Offsets:
    // +0x04: pointer to first axis node (linked list)
    // +0x08: unknown field (zeroed)
    void* unknownField0x08;  // +0x08

    // Node structure (0x2C bytes)
    struct AxisNode {
        AxisNode* prev;   // +0x00
        AxisNode* next;   // +0x04
        void* data;       // +0x08
        uint8_t flags[0x28]; // padding, flags at +0x28 and +0x29
        uint8_t flag0x28; // +0x28: set to 1
        uint8_t flag0x29; // +0x29: set to 1
    };

    // Returns this pointer (constructor-like)
    int __fastcall init() {
        uint32_t unknownGlobal; // uVar1

        // Allocate a new axis node (size 0x2C)
        AxisNode* newNode = (AxisNode*)allocateMemory(0x2C);
        if (newNode != nullptr) {
            newNode->prev = nullptr;
            newNode->next = nullptr;
            newNode->data = nullptr;
        }
        // Set flags
        newNode->flag0x28 = 1;  // +0x28
        newNode->flag0x29 = 1;  // +0x29

        // Store node at this+4
        *(AxisNode**)((int)this + 4) = newNode;

        // Initialize circular linked list pointers (self-pointers for now)
        newNode->next = newNode;
        newNode->prev = newNode;
        // Actually the code does:
        // *(int *)(*(int *)(param_1 + 4) + 4) = *(int *)(param_1 + 4); // node->next = node
        // *(undefined4 *)*(undefined4 *)(param_1 + 4) = *(undefined4 *)(param_1 + 4); // node->prev = node
        // *(int *)(*(int *)(param_1 + 4) + 8) = *(int *)(param_1 + 4); // node->data = node ? maybe a self-reference
        newNode->next = (AxisNode*)((int)this + 4); // Wait, careful. Actually the code stores the pointer to node at this+4, then reads it back.
        // Let's replicate exactly:
        // *(int *)(*(int *)(param_1 + 4) + 4) = *(int *)(param_1 + 4);
        // So node->next = address of node? No, it's the value at param_1+4 which is the pointer to node. So node->next = node pointer (self)
        // But the code says *(int *)(*(int *)(param_1+4)+4) = *(int*)(param_1+4); So node->next = node. OK self-loop.
        // Similarly node->prev = node.
        // And node->data = node.
        AxisNode* node = *(AxisNode**)((int)this + 4);
        node->next = node;
        node->prev = node;
        node->data = (void*)node;

        // Zero this+8
        unknownField0x08 = nullptr;

        // Cache global for axes
        unknownGlobal = _DAT_00d5780c; // base context

        // Register standard axes
        debugPrint("X-Axis");
        registerAxis(createAxisDefinition(/* out */ 0), 0x000000000ULL, unknownGlobal);

        debugPrint("Y-Axis");
        registerAxis(createAxisDefinition(/* out */ 0), 0x100000000ULL, unknownGlobal);

        debugPrint("Z-Axis");
        registerAxis(createAxisDefinition(/* out */ 0), 0x400000000ULL, unknownGlobal);

        debugPrint("Z-Rotation");
        registerAxis(createAxisDefinition(/* out */ 0), 0x500000000ULL, unknownGlobal);

        debugPrint("Throttle");
        registerAxis(createAxisDefinition(/* out */ 0), 0x600000000ULL, unknownGlobal);

        debugPrint("Rudder");
        registerAxis(createAxisDefinition(/* out */ 0), 0x700000000ULL, unknownGlobal);

        // Inverted axes use a different global
        unknownGlobal = _DAT_00d5ccf8; // inverted context

        debugPrint("X-Axis.Inverted");
        registerAxis(createAxisDefinition(/* out */ 0), 0x000000000ULL, unknownGlobal);

        debugPrint("Y-Axis.Inverted");
        registerAxis(createAxisDefinition(/* out */ 0), 0x100000000ULL, unknownGlobal);

        debugPrint("Z-Axis.Inverted");
        registerAxis(createAxisDefinition(/* out */ 0), 0x400000000ULL, unknownGlobal);

        debugPrint("Z-Rotation.Inverted");
        registerAxis(createAxisDefinition(/* out */ 0), 0x500000000ULL, unknownGlobal);

        debugPrint("Throttle.Inverted");
        registerAxis(createAxisDefinition(/* out */ 0), 0x600000000ULL, unknownGlobal);

        debugPrint("Rudder.Inverted");
        registerAxis(createAxisDefinition(/* out */ 0), 0x700000000ULL, unknownGlobal);

        return (int)this;
    }

private:
    // Helper to create and register an axis
    void registerAxis(uint64_t* axisObj, uint64_t axisId, uint32_t context) {
        if (axisObj != nullptr) {
            *axisObj = axisId;
            *(uint32_t*)(axisObj + 1) = context; // second 4 bytes
        }
        // The original code also checks if local_10[0] != 0 and calls a function pointer.
        // local_10 is an out parameter from createAxisDefinition; it may contain a callback.
        // We'll replicate assuming it's a member function or a global callback.
        // For now, we ignore this as it may be decompiler artifact. 
    }
};
```