// FUN_00460020: SquadManager::addSquadMembers

void __thiscall SquadManager::addSquadMembers(int count)
{
    SquadNode* headNode;
    SquadNode* newNode;
    int i;
    void* allocator;
    int allocArgs[3];
    
    headNode = (SquadNode*)this->field_0x218; // offset 0x86 * 4 = 0x218
    if (headNode != nullptr && count > 0 && headNode->next == nullptr) {
        i = 0;
        allocArgs[0] = 2;   // allocation type?
        allocArgs[1] = 0x10;
        allocArgs[2] = 0;
        do {
            allocator = GetMemoryManager(); // FUN_009c8f80
            newNode = (SquadNode*)((code**)allocator)[0](0x3b0, allocArgs); // create new squad node
            newNode->field_0x70 = headNode->field_0x70; // copy parent data
            int someId = this->vtable->GetSomeId(); // virtual call at +0x17c
            RegisterNewNode(this, (void*)this->field_0x230, someId); // FUN_00570060
            allocator = GetMemoryManager(); // again
            if (newNode->field_0x10c == 0) {
                newNode->field_0x10c = ConvertShortToInt(newNode->field_0xb0); // FUN_005827e0
            }
            newNode->parent = this + 0xf; // offset 0x3C, points back to container
            headNode->next = newNode;
            headNode = newNode;
            i++;
        } while (i < count);
        this->field_0x228 = count; // offset 0x8a * 4 = 0x228
        FinalizeSquad(); // FUN_00572720
    }
}