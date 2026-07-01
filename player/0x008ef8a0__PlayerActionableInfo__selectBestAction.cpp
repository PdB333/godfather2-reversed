// FUNC_NAME: PlayerActionableInfo::selectBestAction

#include <cstdint>

// Forward declarations for called functions (assumed within same module)
uint32_t engineHash(uint32_t value); // FUN_004059b0
uint32_t getCurrentTime();           // FUN_008ec040
uint32_t getSomeTimeOffset();        // FUN_008ebfc0
void* lookupEntity(uint32_t id);     // FUN_008ecc20 / FUN_008ecc80
bool activateAction(void* action);   // FUN_008eb560
bool isActionActive(void* action);   // FUN_008ee8b0
void deleteAction(void* action);     // FUN_004061b0
void removeFromHashTable(uint32_t id); // FUN_008ef6b0
void removeFromAnotherTable(uint32_t id); // FUN_006f9af0
void sendCommand(int32_t cmd, void* data); // FUN_00408c70
void freeAction(void* action);       // FUN_004daf90
void fullyReleaseAction(void* action); // FUN_009c8eb0
void broadcastStateChange(void* param); // FUN_004088c0
void iterateNextNode(void* node);    // FUN_008ea280
void iterateNextNode2(void* node);   // FUN_008ea1d0
void panic();                        // FUN_00b97aea (assert / abort)

// Global data – possibly a singleton manager or entity hash table
extern int g_globalManager;          // DAT_0122337c

// Internal structure for an action node (likely linked list element)
struct ActionNode {
    ActionNode* next;               // +0x00 next pointer (used in iterating)
    void*        actionData;        // +0x04 (not used directly here)
    uint32_t     entityId;          // +0x08? Actually from code: iVar8+0xc is entity ID, stored in local_14
    // Actually the decompiled shows for puVar1: *(undefined4 **)(iVar8 + 0x10) – that's the first action node in a list
    // Then each puVar1 has fields at offsets: puVar1[7] is priority, puVar1[2] is some pointer, puVar1[6] is something, puVar1[8] is type?
    // Let's define based on usage:
    int32_t  priority;             // puVar1[7] (offset +0x1c) — *1000-50
    void*    somePointer;          // puVar1[2] (offset +0x08)
    int32_t  someId;               // puVar1[6] (offset +0x18)
    int32_t  actionType;           // puVar1[8] (offset +0x20)
};

// The class owning this method
class PlayerActionableInfo {
public:
    // Offsets: +0x10, +0x1c, +0x20, +0x2c, +0x3c (guessed)
    void*   list1;                 // +0x10 - main action list head
    int32_t totalCost;             // +0x1c - total cost / time
    void*   list2;                 // +0x20 - second action list (e.g. combat)
    void*   list3;                 // +0x2c - third action list (e.g. movement)
    void*   stateData;             // +0x3c - broadcast state parameter

    // Method: selects and runs the best action from available lists
    // param_2: time-based priority offset (or score adjustment)
    // param_3: pointer to int (maybe output or exclusion check)
    bool selectBestAction(int32_t priorityOffset, int32_t* excludedAction);
};

bool PlayerActionableInfo::selectBestAction(int32_t priorityOffset, int32_t* excludedAction) {
    int32_t currentTime = getCurrentTime();
    int32_t someOffset = getSomeTimeOffset();
    int32_t globalMgr = g_globalManager; // global manager pointer

    // If totalCost is already less than currentTime+someOffset, skip? Actually check opposite:
    if (totalCost > currentTime + someOffset) {
        // Not ready yet? Return 1? Actually the code returns 1 only after doing work.
        // Let's follow logic: if condition fails, it proceeds with selection.
        // The check is: if (*(int*)(this+0x1c) <= iVar4 + iVar5) { ... } else return 1 at end.
        // So if totalCost is too high, skip processing and return 1 (maybe success?).
        // But the decompiled shows return 1 after the big block if condition fails.
        // For clarity, we'll restructure.
    }

    // If totalCost <= currentTime + someOffset, perform selection
    // Initialize best priority to a large number
    int32_t bestPriority = 999999;
    void*   bestAction = nullptr;
    uint32_t bestEntityId = 0xfe16702f; // magic initial value
    ActionNode* bestNode = nullptr;

    // Loop over two sublists: list2 and list3 (indices 0 and 1)
    int32_t passIndex = 0;
    do {
        void* listCursor;
        if (passIndex == 0) {
            listCursor = *(void**)((uint8_t*)this + 0x24); // Wait, offset: +0x20+4? Decompiled: iVar4 = this+0x20, then iVar8 = **(int**)(iVar4+4). So list2 has a head pointer at +0x20, and the actual iteration starts from the node at *(int*)(+0x24).
            // Actually reinterpret: the list structure seems to be a linked list of "container nodes" (iVar8). Each container has a list of ActionNodes at +0x10.
        } else {
            listCursor = *(void**)((uint8_t*)this + 0x30); // +0x2c+4
        }

        // Iterate over container nodes in that sublist
        void* containerNode = *(void**)((uint8_t*)listCursor); // **(int**)(iVar4+4)
        while (containerNode != *(void**)((uint8_t*)listCursor)) {
            // Normal loop: iterate through container nodes.
            // For each container, get its action list (at containerNode + 0x10)
            ActionNode* actionNode = *(ActionNode**)((uint8_t*)containerNode + 0x10);
            while (actionNode != nullptr) {
                if (passIndex == 0) {
                    // First sublist (list2): check entity validity via hash table
                    uint32_t entityId = *(uint32_t*)((uint8_t*)containerNode + 0x0c);
                    uint32_t hash = engineHash(entityId);
                    uint32_t bucketCount = *(uint32_t*)(g_globalManager + 0x54);
                    uint32_t bucketIndex = hash % bucketCount;
                    uint32_t* bucketHead = *(uint32_t**)(*(int*)(g_globalManager + 0x50) + bucketIndex * 4);
                    bool foundValid = false;
                    for (uint32_t* entry = bucketHead; entry != nullptr; entry = (uint32_t*)entry[2]) {
                        if (entry[0] == hash) {
                            if (entry[1] != 0 && *(int*)(entry[1] + 0x24) == 0) {
                                foundValid = true;
                                break;
                            }
                            break; // if not valid, break anyway (entry exists but invalid)
                        }
                    }
                    if (!foundValid) {
                        actionNode = (ActionNode*)(actionNode->next); // actually puVar1 = (undefined4*)*puVar1
                        // Move to next action in container's list
                        actionNode = (ActionNode*)*((void**)actionNode);
                        continue;
                    }
                }
                // For both passes, evaluate priority
                int32_t actionPriority = actionNode->priority * 1000 - 50;
                if (actionPriority <= bestPriority) {
                    bestPriority = actionPriority;
                    if (passIndex == 0) {
                        bestEntityId = *(uint32_t*)((uint8_t*)containerNode + 0x0c);
                    }
                    bestNode = actionNode;
                }
                actionNode = (ActionNode*)*((void**)actionNode); // next action
            }
            // Move to next container node
            containerNode = *(void**)((uint8_t*)containerNode); // next container
        }
        passIndex++;
    } while (passIndex < 2);

    // Second main list: list1 (+0x10)
    void* mainContainerNode = *(void**)((uint8_t*)this + 0x10);
    int32_t bestMainPriority = bestPriority; // iVar4 = param_2 (which was 999999)
    void* bestMainAction = nullptr;
    while (mainContainerNode != *(void**)((uint8_t*)this + 0x10)) {
        ActionNode* mainAction = *(ActionNode**)((uint8_t*)mainContainerNode + 0x10);
        while (mainAction != nullptr) {
            // FUN_008e9b70 returns some priority value for actions from list1
            int32_t mainPriority = getMainPriority(); // placeholder for FUN_008e9b70
            if (mainPriority < bestMainPriority) {
                bestMainPriority = mainPriority;
                // local_1c = (int*)puVar1[2]; so bestMainAction stores the pointer at offset +0x08 of action node
                bestMainAction = mainAction->somePointer;
            }
            mainAction = (ActionNode*)*((void**)mainAction);
        }
        mainContainerNode = *(void**)((uint8_t*)mainContainerNode);
    }

    int32_t threshold = priorityOffset * 1000 - 50; // iVar5

    // Decision logic:
    // If main list found better priority than sublists, OR sublist bestAction is null, OR threshold > sublist bestPriority
    if ((bestMainPriority < bestPriority) || (bestNode == nullptr) || (threshold < bestPriority)) {
        // Use main list candidate if it is valid and better than threshold
        if ((bestMainAction != nullptr) && (bestMainPriority < threshold)) {
            int32_t cmdParam = 0;
            // Call execute function on bestMainAction with command id 0x369ac561
            bool success = (*(bool(**)(void*, int32_t*))(*((void**)bestMainAction) + 0x10))(0x369ac561, &cmdParam);
            if (success) {
                // Check global and inner flag
                if ((g_globalManager != 0) && (*(int32_t*)(g_globalManager + 0x216c) > 0)) {
                    *(uint32_t*)(g_globalManager + 0x1f5c) |= 0x10000;
                }
                broadcastStateChange((uint8_t*)this + 0x3c);
                return true;
            }
        }
        return false;
    }
    // Use sublist candidate
    // Get the entity object from entity ID
    void* entityObj = lookupEntity(bestEntityId);
    if (entityObj == nullptr) {
        entityObj = lookupEntityAlt(bestEntityId); // FUN_008ecc80
    }
    // Activate the action
    activateAction(bestNode);
    // Check if action is already active
    bool isActive = isActionActive(bestNode->someId);
    if (!isActive) {
        deleteAction(bestNode->someId);
    }
    // If entity object is not already processed and not excluded
    if ((*((int32_t*)entityObj) == 0) && (entityObj != excludedAction)) {
        uint32_t idHash = engineHash(bestEntityId);
        if (idHash == 0) {
            removeFromHashTable(bestEntityId);
        } else {
            removeFromAnotherTable(idHash);
        }
    }
    // Handle action type
    int32_t actionType = bestNode->actionType;
    if ((actionType != 0) && (actionType != 0x48)) {
        sendCommand(actionType - 12, 1); // FUN_00408c70 with DAT_0112fde8 as base
    }
    if (actionType != 0) {
        freeAction(&bestNode->actionType); // FUN_004daf90 on offset of actionType
    }
    fullyReleaseAction(bestNode);
    return true;
}