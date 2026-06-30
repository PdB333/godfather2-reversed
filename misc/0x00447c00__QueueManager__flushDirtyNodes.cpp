// FUNC_NAME: QueueManager::flushDirtyNodes

// Reconstructed from Ghidra at 0x00447c00
// Flushes a linked list of "dirty" nodes into a processing queue,
// then processes queued array entries with type == 4.

struct QueueNode {
    QueueNode* next;      // +0x00
    QueueNode* prev;      // +0x04
    // ... other members ...
    uint32_t flags;       // +0x14 (offset 20)
};

class QueueManager {
public:
    QueueNode* dirtyHead;   // +0xA8
    QueueNode* dirtyTail;   // +0xAC
    QueueNode* procHead;    // +0x90
    QueueNode* procTail;    // +0x94
    // ... gap ...
    int32_t* cmdArray;      // +0xB0  (array of 8-byte commands)
    int32_t  cmdCount;      // +0xB4
    uint8_t  flushed;       // +0xC4 (byte flag)
    // ... other members ...

    void flushDirtyNodes();
};

// Forward declarations of called functions (likely static helpers)
extern bool canProcessDirtyNode();        // FUN_00447070
extern void processCommandType4();        // FUN_00449470

void QueueManager::flushDirtyNodes() {
    if (flushed != 0) {
        return;  // Already flushed this frame
    }

    QueueNode* node = dirtyHead;
    while (node != nullptr) {
        QueueNode* nextNode = node->next;  // save next before potential removal

        if ((node->flags & 0x100) != 0) {
            node->flags &= ~0x100;  // clear dirty flag

            if (canProcessDirtyNode()) {
                // Remove node from dirty list (doubly linked, head/tail pointers at +0xA8/+0xAC)
                if (node->prev == nullptr) {
                    // node is the head
                    dirtyHead = node->next;
                    if (dirtyHead != nullptr) {
                        dirtyHead->prev = nullptr;
                    } else {
                        // List became empty
                        dirtyTail = nullptr;
                    }
                } else {
                    // node is not the head
                    node->prev->next = node->next;
                    if (node->next != nullptr) {
                        node->next->prev = node->prev;
                    } else {
                        // node was the tail
                        dirtyTail = node->prev;
                    }
                }

                // Insert node at tail of processing list (head +0x90, tail +0x94)
                node->flags |= 0x40;      // mark as "in processing queue"
                node->next = nullptr;
                node->prev = procTail;    // prev = old tail

                if (procTail == nullptr) {
                    // Processing list was empty
                    procHead = node;
                } else {
                    // Append after old tail
                    procTail->next = node;
                }
                procTail = node;          // new tail is this node
            }
        }

        node = nextNode;
    }

    // Process command array backwards
    for (int32_t i = cmdCount - 1; i >= 0; i--) {
        // Each command is 8 bytes: base[i*8] is type, base[i*8+4] is maybe sub-type
        if (cmdArray[i * 2 + 1] == 4) {   // second int == 4
            processCommandType4();
        }
    }

    flushed = 1;  // Mark flush complete for this frame
}