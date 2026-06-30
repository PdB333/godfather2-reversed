// FUNC_NAME: EARSObject::~EARSObject
// Function address: 0x004528e0
// Destructor: removes object from global list, then calls base destructor.
// Offsets: +0x00 = vtable_ptr, +0x0c = second vtable_ptr for MI, +0x30 = next in linked list, +0x34 = prev in linked list.
// Global flag at 0x01223408 is reset.

void __fastcall EARSObject::~EARSObject(undefined4 *this)
{
    int iVar1;
    undefined4 *puVar2;
    undefined4 *puVar3;

    // Set vtable pointers for this class (most derived)
    *this = &PTR_FUN_00e31700;                      // +0x00: vtable for this class
    this[3] = &PTR_LAB_00e31710;                    // +0x0c: second vtable (possibly for base)

    // Call helper destructor (frees internal resources)
    FUN_00452b90();

    // Remove this object from a global linked list (stored at offsets +0x30 and +0x34)
    iVar1 = this[0xc];                              // +0x30: next pointer in list
    if (iVar1 != 0) {
        puVar2 = *(undefined4 **)(iVar1 + 4);       // Read next->next (offset +4 in node)
        if (puVar2 == this + 0xc) {                // If next node points back to our list head address
            // Single node case: unlink by setting next->next to our prev
            *(undefined4 *)(iVar1 + 4) = this[0xd]; // +0x34: prev pointer
        } else {
            // Traverse list to find the node whose 'next' equals our list head address
            puVar3 = (undefined4 *)puVar2[1];      // puVar2[1] = puVar2->next
            while (puVar3 != this + 0xc) {
                puVar2 = (undefined4 *)puVar2[1];  // Move to next node
                puVar3 = (undefined4 *)puVar2[1];  // Get its next
            }
            // Set that node's 'next' to our prev, effectively unlinking us
            puVar2[1] = this[0xd];                 // +0x34: prev pointer
        }
    }

    // Switch to base class vtable and call base destructor/cleanup
    this[3] = &PTR_LAB_00e31714;                   // +0x0c: base class vtable
    DAT_01223408 = 0;                              // Reset global flag
    FUN_004083d0();                                // Final deallocation (likely operator delete)
    return;
}