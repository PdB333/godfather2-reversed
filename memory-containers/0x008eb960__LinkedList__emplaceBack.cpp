// FUNC_NAME: LinkedList::emplaceBack
void __thiscall LinkedList::emplaceBack(int param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4, undefined4 param_5)
{
    // Node structure: size 0x2C (44 bytes)
    // Offset 0x00: Node* prev
    // Offset 0x04: Node* next
    // Offset 0x08..0x2B: data (size 0x24)
    struct Node {
        Node* prev;
        Node* next;
        // ... data fields
    };

    // Allocate new node
    Node* newNode = (Node*)FUN_009c8e50(0x2C);
    if (newNode == nullptr) {
        return;
    }

    // Construct node with given parameters (likely a constructor call)
    newNode = (Node*)FUN_008eac00(param_2, param_3, param_4, param_5);

    // Initialize node
    newNode->prev = nullptr;          // *puVar2 = 0
    newNode->next = *(Node**)(param_1 + 0x50); // puVar2[1] = tail

    // Update list pointers
    Node* tail = *(Node**)(param_1 + 0x50);
    if (tail != nullptr) {
        tail->prev = newNode;         // **(param_1+0x50) = puVar2
        *(Node**)(param_1 + 0x50) = newNode; // tail = newNode
    } else {
        *(Node**)(param_1 + 0x4C) = newNode; // head = newNode
        *(Node**)(param_1 + 0x50) = newNode; // tail = newNode
    }
}