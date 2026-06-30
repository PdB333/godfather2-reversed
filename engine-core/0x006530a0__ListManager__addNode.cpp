// FUNC_NAME: ListManager::addNode
extern void FUN_00653230(int* param_1, int param_2);
extern void FUN_00653760();
extern void FUN_0065a6c0(int param_1, int param_2, int param_3, int param_4);
extern void FUN_0064c980(int param_1, int param_2);

struct Node {
    int vtable;     // +0x00
    int someValue;  // +0x04
    int unknown_08; // +0x08
    int unknown_0C; // +0x0C
    Node* next;     // +0x10
};

struct ListManager {
    int vtable;                 // +0x00
    // ... (offset 0x90)
    int field_0x90;             // +0x90
    int field_0x98;             // +0x98
    // ... (offset 0x11C)
    Node* head;                 // +0x11C
    Node* tail;                 // +0x120
    // ... (offset 0x1A4)
    int* basePtr;               // +0x1A4
    // ... (offset 0x1B0)
    int* anotherList;           // +0x1B0
    // ... (offset 0x1C8)
    int field_0x1C8;            // +0x1C8
};

void __thiscall ListManager::addNode(ListManager* this, int flag)
{
    // Call internal initialization, returns a pointer stored in unknownResult
    int* unknownResult = (int*)FUN_00653230((int*)this, flag);

    if (flag == 0)
    {
        // Virtual call to create a new node (vtable offset 0x4c)
        Node* newNode = (Node*)(this->vtable[0x13])();

        if (this->head == 0)
        {
            this->head = newNode;
        }
        else
        {
            this->tail->next = newNode;
        }

        this->tail = newNode;
        newNode->next = 0;

        // Set node's value from base pointer offset 100 (0x64)
        newNode->someValue = *(int*)(this->basePtr + 100);

        FUN_00653760();

        // Write a field into unknownResult
        *(int*)(unknownResult + 0x34) = this->field_0x1C8;

        // Virtual call (vtable offset 0x38)
        (this->vtable[0x0E])();
    }

    // Process another list if present
    if (this->anotherList != 0)
    {
        FUN_0065a6c0((int)this->anotherList, this->field_0x98, this->field_0x90, flag);
        FUN_0064c980(3, (int)this->anotherList);
    }
}