// FUNC_NAME: BaseObject::deletingDestructor
// Function address: 0x006bc900
// Role: Scalar deleting destructor for a base object with virtual table.
//   Calls the actual destructor (FUN_004daf90) if the object is initialized
//   (i.e., the vtable pointer at offset 0 is non-null).
//   If deleteFlag's lowest bit is set, frees the memory via FUN_009c8eb0 (operator delete).
//   Returns the this pointer (common for destructors).

int* __thiscall BaseObject::deletingDestructor(int* this_, byte deleteFlag)
{
    // +0x00: vtable pointer; check if object is properly constructed
    if (*this_ != 0) {
        FUN_004daf90(this_);  // virtual destructor / cleanup
    }
    // Bit 0 of deleteFlag indicates ownership: if set, call operator delete
    if ((deleteFlag & 1) != 0) {
        FUN_009c8eb0(this_);  // operator delete / free
    }
    return this_;
}