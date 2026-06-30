// FUNC_NAME: EventManager::processEvents
// Address: 0x005bff90
// Role: Updates and processes a circular doubly-linked list of event nodes.
// Iterates through the list, calling a callback for each node, and removes nodes
// if they are inactive. Uses a sentinel node to detect end-of-list cycling.

typedef unsigned int uint32;
typedef unsigned long long uint64;

// Forward declarations
class EventManager;

// Event node structure (size 0x14? at least 0x10 + prev/next)
struct EventNode {
    void (__thiscall *callback)(int param); // +0x00: function pointer, called with arg at +0x04
    int arg;                                 // +0x04: argument passed to callback
    char isActive;                           // +0x08: flag, if 0 node is removed after callback returns 1
    EventNode *prev;                         // +0x0C: previous node in list
    EventNode *next;                         // +0x10: next node in list
};

// External sentinel node (used to mark the end of the circular list)
extern EventNode* g_sentinel; // Actually a static 8-byte key pair, but here we use a node

// Global functions called within
bool getTimeRemaining(); // FUN_005c2880: returns non-zero if more time left
bool canFreeNode(void* ptr); // FUN_005c43d0: returns true if the node can be safely deallocated

// Memory deallocation function (likely global operator delete or custom)
void __fastcall freeMemory(void* ptr, uint32 type); // called from vtable at DAT_012234ec+4

class EventManager {
public:
    EventNode* head;    // +0x00: head of the circular list (sentinel or real node)
    EventNode* current; // +0x04: current iterator node

    // Constructor or initializer (called elsewhere)
    void init() {
        head = nullptr; // Or set to sentinel
        current = nullptr;
    }

    // Main processing function
    void processEvents() {
        if (this == nullptr) return;
        current = head; // Start from head

        do {
            EventNode* node = current;
            if (node == nullptr) return;

            bool timeRemaining = getTimeRemaining(); // Check if we should continue

            // Extract the 8-byte key from the node (callback + arg combined)
            uint64 nodeKey = *(uint64*)node; // reinterpret first 8 bytes
            int callbackResult = node->callback(node->arg); // call the node's callback

            // Compare node key to sentinel's key (or a static key at 0x00f17884)
            // The sentinel is used to detect when we've wrapped around.
            // Here we assume g_sentinel is a static variable with the same layout.
            EventNode* checkNode = current;
            if (checkNode == nullptr) {
                checkNode = g_sentinel; // Use sentinel if list is empty? Actually this check seems odd.
            }
            // The sentinel check compares the 8-byte key of the current node to the sentinel's key.
            // If they match, we are at the sentinel node and need to handle it specially.
            // In practice, the sentinel's key is unique (e.g., callback = 0, arg = 0).
            if (node == checkNode) { // This is always true, but the original code uses piVar6 which is the same as node.
                // Check if the node's key equals the sentinel's key (stored at 0x00f17884)
                if ( (int)(nodeKey & 0xFFFFFFFF) == checkNode->callback && 
                     (int)(nodeKey >> 32) == checkNode->arg ) {
                    // We've reached the sentinel or a node with the sentinel key.
                    if (callbackResult == 1) {
                        node->isActive = 0; // Mark node as inactive
                    }
                    if (node->isActive == 0) {
                        // Remove the node from the list
                        EventNode* toRemove = current;
                        if (toRemove != nullptr) {
                            current = node->next; // Advance current
                            if (head == toRemove) {
                                head = node->next;
                            }
                            // Unlink toRemove from doubly-linked list
                            if (toRemove->prev != nullptr) {
                                toRemove->prev->next = toRemove->next;
                            }
                            if (toRemove->next != nullptr) {
                                toRemove->next->prev = toRemove->prev;
                            }
                            // Try to free the node
                            if (!canFreeNode(toRemove)) {
                                // If can't free, call a memory free function
                                // This likely invokes the global allocator's free (through vtable)
                                // Using the base pointer from DAT_012234ec
                                // (code) (**(int**)(DAT_012234ec + 4))[1](toRemove, 0);
                                // Simplified: call global delete or custom free
                                freeMemory(toRemove, 0);
                            }
                        }
                        if (current == nullptr) {
                            current = head; // Wrap around to head
                        }
                    } else {
                        // Node is still active, advance to next
                        if (current == nullptr) {
                            current = nullptr; // Unchanged
                        } else {
                            current = node->next;
                        }
                        if (current == nullptr) {
                            current = head; // Wrap if at end
                        }
                        if (current == nullptr) {
                            return; // List is empty
                        }
                    }
                }
                // If key doesn't match sentinel, do nothing? (Original code does nothing else)
            }
            if (!timeRemaining) {
                return; // No more time, exit
            }
        } while (true);
    }
};