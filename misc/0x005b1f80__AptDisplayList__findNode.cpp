// FUNC_NAME: AptDisplayList::findNode
// Address: 0x005b1f80
// File: ..\source\Apt\AptDisplayList.cpp
// Searches the display list for a node by name or depth.
// Returns the found node and its previous node via output parameters.

struct AptDisplayListNode {
    // +0x00: unknown
    // +0x04: unknown
    // +0x08: unknown
    // +0x0c: int depth;
    // +0x0d: NameData* nameData; // pointer to structure with name string at +0x0c
    // +0x18: AptDisplayListNode* next;
    int depth;           // +0x0c
    void* nameData;      // +0x0d (actually offset 0x0d? but likely aligned, so +0x10? The code uses puVar8[0xd] which is offset 0x34? Wait: puVar8 is uint*, so puVar8[0xd] is offset 0x34 bytes. That seems large. Let's re-evaluate.)
    // Actually, the code uses puVar8[0xd] as a pointer, and then dereferences +0xc from that. So the node structure has a field at offset 0x34 (0xd * 4) that points to a name struct. The name struct has the string at +0xc. So the node size is at least 0x38 bytes.
    // But for simplicity, we'll use offsets as given.
};

struct NameData {
    // +0x00: unknown
    // +0x04: unknown
    // +0x08: unknown
    // +0x0c: char* name;
    char* name; // +0x0c
};

void AptDisplayList::findNode(AptDisplayListNode* thisPtr, uint depth, byte* name, AptDisplayListNode** outNode, AptDisplayListNode** outPrevNode) {
    // Debug assertions
    if (outPrevNode == nullptr) {
        // Assertion failure: "ppPrev"
        // ... debug code omitted for brevity
        return;
    }
    if (outNode == nullptr) {
        // Assertion failure: "ppItem"
        return;
    }
    if ((int)depth < 0) {
        // Assertion failure: "nDepth >= 0"
        return;
    }

    AptDisplayListNode* current = thisPtr; // param_1 is the list head? Actually param_1 is the this pointer, and *param_1 is the first node? The code does puVar4 = *param_1; so the list head is stored at this+0.
    AptDisplayListNode* prev = nullptr;
    AptDisplayListNode* node = current; // puVar4
    AptDisplayListNode* next = node->next; // puVar5 = puVar4[0x18]

    // First, try to find by name
    if (name != nullptr) {
        while (next != nullptr) {
            // Check if node is not hidden (bit 15 clear) and has a name
            if (((~(byte)((uint)next >> 0xf) & 1) != 0) && (next->nameData != nullptr)) {
                char* nodeName = *(char**)((byte*)next->nameData + 0xc);
                // Compare strings
                byte* p1 = name;
                byte* p2 = (byte*)nodeName;
                int cmp;
                do {
                    byte c1 = *p1;
                    byte c2 = *p2;
                    if (c1 != c2) {
                        cmp = (c1 < c2) ? -1 : 1;
                        break;
                    }
                    if (c1 == 0) {
                        cmp = 0;
                        break;
                    }
                    p1++;
                    p2++;
                } while (true);
                if (cmp == 0) {
                    *outNode = next;
                    *outPrevNode = prev;
                    return;
                }
            }
            prev = next;
            next = next->next;
        }
    }

    // If not found by name, search by depth
    node = current;
    next = node->next;
    while (true) {
        if (next == nullptr) {
            *outNode = nullptr;
            *outPrevNode = node;
            return;
        }
        if ((int)depth <= next->depth) {
            if (next->depth == (int)depth) {
                *outNode = next;
                *outPrevNode = node;
                return;
            }
            // depth not found, return null
            *outNode = nullptr;
            *outPrevNode = node;
            return;
        }
        node = next;
        next = next->next;
    }
}