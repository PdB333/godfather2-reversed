// FUNC_NAME: NodeManager::NodeConstructor or NodeManager::createNode
undefined4 * __thiscall FUN_00899580(undefined4 *this, char *name, undefined4 param3, undefined4 param4, undefined4 param5)
{
    // Call base constructor or default initialization
    FUN_0064cc90();
    
    // Set vtable pointer
    *this = &PTR_LAB_00d77e10;
    
    // Copy name string with max length 63 (0x3F) characters
    _strncpy((char *)(this + 8), name, 0x3f);
    
    // Store parameters at specific offsets
    this[1] = param3;   // +0x04 - likely node type or flags
    this[3] = param4;   // +0x0C - likely index or ID
    this[2] = param5;   // +0x08 - likely parent or owner
    
    // Initialize linked list pointers to null
    this[4] = 0;        // +0x10 - previous node pointer
    this[5] = 0;        // +0x14 - next node pointer
    this[6] = 0;        // +0x18 - child pointer
    this[7] = 0;        // +0x1C - sibling pointer
    
    // Link this node into a global list
    this[0x1c] = DAT_012059ec;  // +0x70 - set next to current head
    DAT_012059ec = this;         // update global head pointer
    
    return this;
}