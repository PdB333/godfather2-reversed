// FUNC_NAME: StreamManager::releaseAllHandles
// Address: 0x0056f4b0
// Role: Releases all reference-counted handles held by this manager.
// For each of five handle slots (+0x34 to +0x44), decrements the ref count,
// and if it becomes zero and the handle is flagged as freeable, unlinks
// it from the global doubly linked list of that type.

// Known structures (inferred):
struct StreamHandleNode {
    StreamHandleNode* prev; // +0x00
    StreamHandleNode* next; // +0x04
    char flags;             // +0x08
    char refCount;          // +0x09
};

// Global list heads (addresses inferred from constants)
struct StreamListHead {
    StreamHandleNode* head; // +0x00
    StreamHandleNode* tail; // +0x04
    int unknown1;           // +0x08
    int unknown2;           // +0x0c
};

// Global lists (symbolic names)
StreamListHead g_StreamList0 = *(StreamListHead*)0x01205564;
StreamListHead g_StreamList1 = *(StreamListHead*)0x01205560;
StreamListHead g_StreamList2 = *(StreamListHead*)0x01205588;
StreamListHead g_StreamList3 = *(StreamListHead*)0x0120558c;
StreamListHead g_StreamList4 = *(StreamListHead*)0x0120555c;

void StreamManager::releaseAllHandles() {
    StreamHandleNode* node;

    // Release handle at +0x34 (stream list 0)
    node = *(StreamHandleNode**)(this + 0x34);
    if (node != nullptr) {
        node->refCount--;
        if (node->flags == 0 && node->refCount == 0) {
            // Unlink from global list
            StreamHandleNode* prev = node->prev;
            StreamHandleNode* next = node->next;
            if (prev != nullptr) {
                prev->next = next;
            }
            if (next == nullptr) {
                // Node was tail, update tail and possibly head
                g_StreamList0.tail = prev;
                if (prev == nullptr) {
                    g_StreamList0.head = g_StreamList0.tail; // head = tail
                }
            } else {
                next->prev = prev;
                if (prev == nullptr) {
                    g_StreamList0.head = next;
                }
            }
        }
        *reinterpret_cast<int*>(this + 0x34) = 0;
    }

    // Release handle at +0x38 (stream list 1)
    node = *(StreamHandleNode**)(this + 0x38);
    if (node != nullptr) {
        node->refCount--;
        if (node->flags == 0 && node->refCount == 0) {
            StreamHandleNode* prev = node->prev;
            StreamHandleNode* next = node->next;
            if (prev != nullptr) {
                prev->next = next;
            }
            if (next == nullptr) {
                g_StreamList1.tail = prev;
                if (prev == nullptr) {
                    g_StreamList1.head = g_StreamList1.tail;
                }
            } else {
                next->prev = prev;
                if (prev == nullptr) {
                    g_StreamList1.head = next;
                }
            }
        }
        *reinterpret_cast<int*>(this + 0x38) = 0;
    }

    // Release handle at +0x3c (stream list 2)
    node = *(StreamHandleNode**)(this + 0x3c);
    if (node != nullptr) {
        node->refCount--;
        if (node->flags == 0 && node->refCount == 0) {
            StreamHandleNode* prev = node->prev;
            StreamHandleNode* next = node->next;
            if (prev != nullptr) {
                prev->next = next;
            }
            if (next == nullptr) {
                g_StreamList2.tail = prev;
                if (prev == nullptr) {
                    g_StreamList2.head = g_StreamList2.tail;
                }
            } else {
                next->prev = prev;
                if (prev == nullptr) {
                    g_StreamList2.head = next;
                }
            }
        }
        *reinterpret_cast<int*>(this + 0x3c) = 0;
    }

    // Release handle at +0x40 (stream list 3)
    node = *(StreamHandleNode**)(this + 0x40);
    if (node != nullptr) {
        node->refCount--;
        if (node->flags == 0 && node->refCount == 0) {
            StreamHandleNode* prev = node->prev;
            StreamHandleNode* next = node->next;
            if (prev != nullptr) {
                prev->next = next;
            }
            if (next == nullptr) {
                g_StreamList3.tail = prev;
                if (prev == nullptr) {
                    g_StreamList3.head = g_StreamList3.tail;
                }
            } else {
                next->prev = prev;
                if (prev == nullptr) {
                    g_StreamList3.head = next;
                }
            }
        }
        *reinterpret_cast<int*>(this + 0x40) = 0;
    }

    // Release handle at +0x44 (stream list 4)
    node = *(StreamHandleNode**)(this + 0x44);
    if (node != nullptr) {
        node->refCount--;
        if (node->flags == 0 && node->refCount == 0) {
            StreamHandleNode* prev = node->prev;
            StreamHandleNode* next = node->next;
            if (prev != nullptr) {
                prev->next = next;
            }
            if (next == nullptr) {
                g_StreamList4.tail = prev;
                if (prev == nullptr) {
                    g_StreamList4.head = g_StreamList4.tail;
                }
            } else {
                next->prev = prev;
                if (prev == nullptr) {
                    g_StreamList4.head = next;
                }
            }
        }
        *reinterpret_cast<int*>(this + 0x44) = 0;
    }
}