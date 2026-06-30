// FUNC_NAME: SimNpc::getInternalDataPointer
// Accesses a nested pointer chain: this->field_0x30->field_0x18 + 0x30
// Returns a pointer into a sub-structure (likely a buffer or component array)
int __fastcall SimNpc::getInternalDataPointer(int thisPtr)
{
    // Dereference this + 0x30 to get a pointer to an intermediate object
    int* pIntermediate = *(int**)(thisPtr + 0x30);
    // Dereference intermediate + 0x18 to get a base pointer
    int* pBase = *(int**)(pIntermediate + 0x18);
    // Return the address of the data at offset 0x30 from the base pointer
    return (int)(pBase + 0x30); // Equivalent: (char*)pBase + 0x30
}