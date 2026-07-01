// FUNC_NAME: ChatterNode::ChatterNode
undefined4 * __thiscall ChatterNode::ChatterNode(undefined4 *this, char *name, undefined4 param3, undefined4 param4, undefined4 param5)
{
    // Call base class constructor (likely some base object)
    FUN_0064cc90();
    
    // Set vtable pointer
    *this = &PTR_LAB_00d6a74c; // vtable for ChatterNode
    
    // Copy name string (max 63 chars + null) into buffer at offset 0x20
    _strncpy((char *)(this + 8), name, 0x3f);
    
    // Set additional parameters (order from decompiler: [1]=param3, [3]=param4, [2]=param5)
    this[1] = param3;      // +0x04: field1 (e.g., ID or pointer)
    this[3] = param4;      // +0x0C: field2
    this[2] = param5;      // +0x08: field3
    
    // Initialize linked list pointers (next/prev?) to NULL
    this[4] = 0;           // +0x10: next pointer?
    this[5] = 0;           // +0x14: prev pointer?
    this[6] = 0;           // +0x18: extra field?
    this[7] = 0;           // +0x1C: extra field?
    
    // Link into global list: store old head (DAT_012059ec) into this->next (at offset 0x70)
    this[0x1c] = DAT_012059ec; // +0x70: link to next node (or head pointer)
    
    // Update global head to this node
    DAT_012059ec = this;
    
    return this;
}