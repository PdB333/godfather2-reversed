// FUNC_NAME: ProcessManager::processAll (offset 0x005ddc30)
// Reconstructed C++ for update loop iterating over two component lists
// Based on Ghidra decompilation of 0x005ddc30 (The Godfather 2, EARS engine)

// Pre-declare internal processing functions
bool processComponent1(uint32_t param);  // FUN_005dc6e0
void* getComponentData(uint32_t value);  // FUN_005dc670
bool updateComponent2(void* data, void* node); // FUN_005de000

// Node structures for the two linked lists
struct ComponentNode1 {
    // Size unknown; only next pointer offset is known
    char unknown[0x28];      // 0x00 - 0x27
    ComponentNode1* next;    // +0x28
};

struct ComponentNode2 {
    uint32_t value;          // +0x00  (first field, used as key/ID)
    char unknown[0x1C - 4];  // 0x04 - 0x1B
    ComponentNode2* next;    // +0x1C (offset 7 * sizeof(uint32_t))
};

// The manager class (this pointer in EDI)
class ProcessManager {
    char unknown_00[0x24];           // 0x00 - 0x23

public:
    bool enabled;                    // +0x24 (bit 0 checked)

private:
    uint32_t component1Count;        // +0x28
    ComponentNode1* component1Head;  // +0x2C
    uint32_t component2Count;        // +0x30
    ComponentNode2* component2Head;  // +0x34

public:
    // Main update function; param_1 is likely deltaTime or context
    bool processAll(uint32_t param_1) {
        char success = 1;

        // Check if the manager is enabled
        if (!(enabled & 1)) {
            return 0;
        }

        // Call pre-update or initialisation step
        preUpdate();

        // Process first component list
        ComponentNode1* node1 = component1Head;
        if (node1 != 0) {
            uint32_t count1 = component1Count;
            uint32_t idx = 0;
            do {
                if (node1 == 0) {
                    success = 0;
                } else {
                    if (!processComponent1(param_1)) {
                        success = 0;
                    }
                    node1 = node1->next;
                }
                idx++;
            } while (idx < count1);
        }

        // Process second component list
        ComponentNode2* node2 = component2Head;
        if (component2Count != 0) {
            uint32_t count2 = component2Count;
            uint32_t idx2 = 0;
            do {
                if (node2 == 0) {
                    success = 0;
                } else {
                    void* data = getComponentData(node2->value);
                    if (data == 0) {
                        success = 0;
                    } else {
                        if (!updateComponent2(data, node2)) {
                            success = 0;
                        }
                    }
                    node2 = node2->next;
                }
                idx2++;
            } while (idx2 < count2);
        }

        return success != 0;
    }

    void preUpdate(); // FUN_005ddd30 (stub)
};

// Stub implementations (not provided)
void ProcessManager::preUpdate() {
    // Actual logic at 0x005ddd30
}

bool processComponent1(uint32_t param) {
    // Actual logic at 0x005dc6e0
    return true;
}

void* getComponentData(uint32_t value) {
    // Actual logic at 0x005dc670
    return 0;
}

bool updateComponent2(void* data, void* node) {
    // Actual logic at 0x005de000
    return true;
}