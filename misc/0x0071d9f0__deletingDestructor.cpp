// FUNC_NAME: deletingDestructor
int * __thiscall deletingDestructor(int *this, byte isDealloc) {
    if (*this != 0) {
        destroy(this);
    }
    if ((isDealloc & 1) != 0) {
        operatorDelete(this);
    }
    return this;
}