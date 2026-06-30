// FUNC_NAME: EARSObject::updateChildren
void __thiscall EARSObject::updateChildren(int this) // +0x10 is next pointer chain head
{
    // Iterate through a linked list starting at this+0x10
    // Nodes have a forward pointer at offset 0x31*4 = 0xC4 (0x31 * sizeof(int))
    for (int* piVar1 = *(int**)(this + 0x10); piVar1 != nullptr; piVar1 = (int*)piVar1[0x31]) {
        // Check if node's flags at byte offset 4 (bit 0-1) indicate active state
        if ((*(byte*)(piVar1 + 4) & 3) == 0) {
            // Call virtual method at vtable+0xc on the node
            // This is likely EARSObject::update or similar
            (**(code**)(*piVar1 + 0xc))(param_1);
        }
    }
}