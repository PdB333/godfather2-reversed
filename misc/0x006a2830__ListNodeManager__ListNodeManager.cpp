// FUNC_NAME: ListNodeManager::ListNodeManager
// Address: 0x006a2830
// Role: Constructor for a manager that owns 6 independent list head nodes. Each node has a vtable pointer (or function table) and a next pointer. Initially, each next points to itself, forming an empty circular list. The last two fields (count?) are zeroed.

void ListNodeManager::ListNodeManager(void* param_1) // __thiscall, param_1 is 'this'
{
    // Each list head occupies two 4-byte fields: a pointer to a vtable/function table and a next pointer.
    // Initialize 6 heads.
    this->head0.vtable = &PTR_FUN_00d5d3c0; // +0x00
    this->head0.next  = this;               // +0x04, points to self for empty list
    this->head1.vtable = &PTR_FUN_00d5d3c0; // +0x08
    this->head1.next  = this;               // +0x0C
    this->head2.vtable = &PTR_FUN_00d5d3c0; // +0x10
    this->head2.next  = this;               // +0x14
    this->head3.vtable = &PTR_FUN_00d5d3c0; // +0x18
    this->head3.next  = this;               // +0x1C
    this->head4.vtable = &PTR_FUN_00d5d3c0; // +0x20
    this->head4.next  = this;               // +0x24
    this->head5.vtable = &PTR_FUN_00d5d3c0; // +0x28
    this->head5.next  = this;               // +0x2C

    // Zero out a count or flag at offset 0x30 and 0x34.
    this->field_0x30 = 0; // +0x30
    this->field_0x34 = 0; // +0x34
}