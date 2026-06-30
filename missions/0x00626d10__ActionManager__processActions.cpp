// FUNC_NAME: ActionManager::processActions
#include <cstdint>

// Structure for an action node in a linked list managed by ActionManager.
// The exact layout depends on the action type (encoded in byte at +4).
// Offsets are determined from switch cases.
struct ActionNode {
    uint32_t    data0;          // +0x00: unknown, might be part of link? 
    uint8_t     type;           // +0x04: action type (5,6,8,9 observed)
    uint8_t     pad5[3];        // +0x05 padding
    // type-specific fields follow; next pointer location varies:
    // type5: next at +0x18
    // type6: next at +0x08
    // type8: next at +0x4c
    // type9: next at +0x40
};

void ActionManager::processActions(ActionNode** headPtr)
{
    ActionNode* pCurrent = *headPtr;
    while (pCurrent != nullptr) {
        switch (pCurrent->type) {
            case 5: {
                // Type 5: next pointer at +0x18
                *headPtr = *(ActionNode**)((uint8_t*)pCurrent + 0x18);
                handleActionType5(headPtr, pCurrent);  // FUN_006267a0
                break;
            }
            case 6: {
                // Type 6: next pointer at +0x08
                *headPtr = *(ActionNode**)((uint8_t*)pCurrent + 0x08);
                handleActionType6();  // FUN_006269b0
                break;
            }
            case 8: {
                // Type 8: next pointer at +0x4c
                *headPtr = *(ActionNode**)((uint8_t*)pCurrent + 0x4c);
                handleActionType8();  // FUN_00626ac0
                break;
            }
            case 9: {
                // Type 9: next pointer at +0x40
                *headPtr = *(ActionNode**)((uint8_t*)pCurrent + 0x40);
                handleActionType9();  // FUN_00626910
                break;
            }
            // default: unknown type, could assert or skip
        }
        pCurrent = *headPtr;
    }
}