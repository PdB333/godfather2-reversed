// FUNC_NAME: clearArray
void __fastcall clearArray(Container* this) {
    // this->count = param_1[1], this->pArray = param_1[0], this->capacity = param_1[2]
    for (int i = this->count - 1; i >= 0; i--) {
        // Each element is 0xC bytes, first 4 bytes being a pointer to an object or a flag
        if (*(int*)((char*)this->pArray + i * 0xC) != 0) {
            FUN_004daf90((int*)((char*)this->pArray + i * 0xC)); // destroy element
        }
    }
    this->count = 0;
    FUN_009c8f10(this->pArray); // free underlying buffer
    this->pArray = nullptr;
    this->capacity = 0;
}