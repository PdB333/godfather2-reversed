// FUNC_NAME: InstanceManager::requestInstance
// Address: 0x005f1790
// Role: Counts existing instances of a given template ID, and if threshold reached, spawns a new instance based on priority flags.

#include <cstdint>

// Forward declarations
struct RegistrationInfo;
struct ManagerNode;
struct InstanceInfo;

// Global variables (from decompiled offsets)
extern ManagerNode* g_pNodeListHead;          // DAT_011a0ef0
extern float g_additivePriorityThreshold;     // DAT_00e2cd48

// Callee function (address 0x005f1ef0) - spawns a new instance
extern uint32_t spawnInstance(ManagerNode* node);

// Registration info structure (based on decompiled offsets)
struct RegistrationInfo {
    int32_t templateId;        // +0x00
    // Padding? +0x04 unused? Actually +0x05 is maxCount, so likely packed
    uint8_t maxCount;          // +0x05
    uint8_t currentCount;      // +0x06
    // Padding up to +0x28
    uint8_t flags;             // +0x28
};

// Node structure in the global linked list
struct ManagerNode {
    ManagerNode* next;          // +0x04
    InstanceInfo* instanceInfo; // +0x2c
    float someFloat;            // +0x50
};

// Instance info (first field is the template ID)
struct InstanceInfo {
    int32_t templateId; // +0x00
};

// Function implementation
uint32_t InstanceManager::requestInstance(RegistrationInfo* info, float priority)
{
    uint8_t count = 0;
    ManagerNode* node = g_pNodeListHead;
    // Set current count to 1 initially (will be updated in loop)
    info->currentCount = 1;

    if (node == nullptr) {
        // No nodes at all; return failure (low byte zero, high bytes from previous eax - assume 0)
        return 0x0;
    }

    do {
        // Check if this node has instance info and matches the desired template
        if (node->instanceInfo != nullptr && node->instanceInfo->templateId == info->templateId) {
            count++;
            info->currentCount = count;

            // When count reaches or exceeds maxCount, consider spawning
            if (count >= info->maxCount) {
                if ((info->flags & 0x10) == 0) {
                    // Without flag: spawn if node's float <= priority
                    if (node->someFloat <= priority) {
                        goto spawn;
                    }
                } else {
                    // With flag: spawn if node's float + global additive < priority
                    if (node->someFloat + g_additivePriorityThreshold < priority) {
spawn:
                        uint32_t result = spawnInstance(node);
                        // Return the high 24 bits of result (masking low byte)
                        return result & 0xFFFFFF00;
                    }
                }
                // Conditions not met for spawning; return packed success indicator
                // Low byte = 1 (success), high 24 bits = templateId >> 8
                return (static_cast<uint32_t>(info->templateId) >> 8) | 0x1;
            }
        }
        node = node->next;
    } while (node != nullptr);

    // No matching node found with enough count; return failure
    return 0x0;
}