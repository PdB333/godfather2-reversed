// FUNC_NAME: Node::init
void __thiscall Node::init(int container) {
    int* newNode = reinterpret_cast<int*>(this);
    int iVar1 = allocateNode(); // FUN_006382f0 - allocates a new node or ID
    newNode[0] = iVar1; // +0x00: some ID or pointer
    newNode[2] = *(int*)(container + 0x1c); // +0x08: next pointer (previous head->next)
    newNode[3] = container; // +0x0c: prev pointer (points to container)
    newNode[4] = *(int*)(container + 0x20); // +0x10: another pointer (maybe tail)
    *(int**)(container + 0x1c) = newNode; // update container's head->next to this node
    newNode[6] = 0; // +0x18: field
    newNode[7] = 0; // +0x1c: field
    newNode[8] = -1; // +0x20: field (initialized to -1)
    newNode[9] = 0; // +0x24: field
    newNode[10] = 0; // +0x28: field
    int iVar2 = allocateSomething(0, 0); // FUN_00637c50 - allocates another resource
    newNode[0xb] = 0; // +0x2c: field
    newNode[0xc] = 0; // +0x30: field
    newNode[0xd] = 0; // +0x34: field
    newNode[5] = 0; // +0x14: field
    newNode[1] = iVar2; // +0x04: second ID or pointer
    *(int*)(iVar1 + 0x20) = *(int*)(container + 0x2c); // copy some value from container to allocated object
    *(char*)(iVar1 + 0x47) = 2; // set a byte field to 2
}