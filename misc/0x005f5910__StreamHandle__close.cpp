// FUNC_NAME: StreamHandle::close
// __thiscall
int StreamHandle::close() {
    int result = 0;
    if (this != nullptr) {
        if ((this->somePointer != nullptr) && ((this->flags & 1) != 0)) {
            // Get global manager singleton (DAT_01223518) and call its release method (vtable+4)
            // with this->somePointer and a zero parameter
            void** mgrPtr = *(void***)(DAT_01223518 + 4);
            if (mgrPtr != nullptr) {
                (*(void(__thiscall**)(void*, int))(*mgrPtr + 4))(this->somePointer, 0);
            }
        }
        // Clear all fields
        this->field_0 = 0;
        this->somePointer = nullptr;
        this->field_8 = 0;
        this->field_C = 0;
        this->field_10 = 0;
        this->flags = 0;
        result = 1;
    }
    return result;
}