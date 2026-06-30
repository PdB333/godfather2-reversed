// FUNC_NAME: EARSBase::constructor
void __fastcall EARSBase::constructor(EARSBase* this)
{
    // Set vtable to a base virtual table (likely for cleanup purposes)
    this->vtable = (void**)&PTR_FUN_00da9810; // +0x00

    // If the child count at +0x20 exceeds the maximum (15), destroy the existing child
    if (this->childCount > 15) // childCount at offset +0x20
    {
        // Call destructor for the child object pointer at +0x0C
        childDestructor(this->child); // FUN_009c8eb0, child at offset +0x0C
    }

    // Reset child count to maximum (15)
    this->childCount = 15; // +0x20
    // Reset some counter to 0
    this->someCounter = 0; // +0x1C
    // Clear the low byte of the child pointer (or flags) at +0x0C
    *((uint8_t*)&this->child) = 0; // first byte of field at +0x0C

    // Set vtable to the final derived virtual table
    this->vtable = (void**)&PTR_LAB_00e31044; // +0x00
}