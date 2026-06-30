// FUNC_NAME: TwoPointerObject::~TwoPointerObject
void __fastcall TwoPointerObject::~TwoPointerObject(int *this) {
    // +0x08: second pointer member
    if (this[2] != 0) {
        FreePointer(this + 2);  // FUN_004daf90 – deallocates the second pointer
    }
    // +0x00: first pointer member
    if (*this != 0) {
        FreePointer(this);      // deallocates the first pointer
    }
    // There is an unused field at +0x04 (int) not handled here.
}