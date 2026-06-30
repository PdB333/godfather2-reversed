// FUNC_NAME: ObjectList::clear
void __thiscall ObjectList::clear(void)
{
    // this is a pointer to the object (in ESI)
    // offset: +0x1C (7*4) = head of linked list
    // each node: [0] vtable, [4] next pointer
    // Node's vtable+8 is a virtual function (likely destructor/release)
    int *node = this->field_1C; // unaff_ESI[7]
    while (node != 0) {
        int *nextNode = *(int **)(node + 4); // next pointer at offset +4
        this->field_1C = nextNode; // unaff_ESI[7] = next before deletion
        // Call virtual function at vtable+8 on the node
        (*(void (__thiscall **)(int *))(*(int *)node + 8))(node);
        node = this->field_1C;
    }
    // Reset counts/capacities
    this->field_0C = 0; // unaff_ESI[3]
    this->field_10 = 0; // unaff_ESI[4]
    this->field_18 = 0; // unaff_ESI[6]
}