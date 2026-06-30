// FUNC_NAME: processActiveNodeList
// Function address: 0x005ddd90
// Purpose: Process a linked list of active nodes, checking validity and executing an action on each.
//          Returns true if all nodes processed successfully, false otherwise.
//          The context struct holds a result flag, enable flag, count, and head pointer.
// Node struct: first field int handle, next pointer at offset 0x28 (10 ints later)

typedef struct ActiveListNode {
    int handle;                 // +0x00
    // padding / unknown fields
    struct ActiveListNode* next; // +0x28 (offset 40 bytes)
} ActiveListNode;

typedef struct ActiveListContext {
    uint8_t resultFlag;         // +0x00 – final result (1 = success, 0 = failure)
    uint8_t pad[0x23];          // padding to reach +0x24
    uint8_t enabled;            // +0x24 – bit 0 enables processing
    uint32_t count;             // +0x28 – number of nodes to process
    ActiveListNode* head;       // +0x2c – pointer to first node
} ActiveListContext;

// External functions (declared elsewhere)
void acquireLock(void);               // FUN_005ddd30
int isValidHandle(int handle);        // FUN_005dc670
uint8_t executeHandle(int handle);    // FUN_005dd510

uint8_t processActiveNodeList(ActiveListContext* context) {
    // Check if the list is enabled (bit 0 of enabled field)
    if ((context->enabled & 1) == 0) {
        return 0;
    }

    acquireLock();

    ActiveListNode* node = context->head;
    uint8_t currentResult = 1;       // uVar2 in original
    context->resultFlag = 1;

    if (node != (ActiveListNode*)0x0 && context->count != 0) {
        uint32_t i = 0;
        do {
            if (node == (ActiveListNode*)0x0) {
                context->resultFlag = 0;
            } else {
                int valid = isValidHandle(node->handle);
                if (valid == 0) {
                    context->resultFlag = 0;
                } else {
                    uint8_t execResult = executeHandle(node->handle);
                    context->resultFlag = currentResult;   // preserve previous cumulative result
                    if (execResult == 0) {
                        // Note: label LAB_005dde48 – sets resultFlag to 0
                        context->resultFlag = 0;
                    }
                }
                node = node->next;   // puVar6[10] – next pointer at offset 0x28
            }
            currentResult = context->resultFlag;   // uVar2 = param_2._0_1_
            i++;
        } while (i < context->count);
    }

    return context->resultFlag;
}