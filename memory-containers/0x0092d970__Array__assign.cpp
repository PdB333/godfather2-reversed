// FUNC_NAME: Array::assign
int * __thiscall Array::assign(int *this, int *other)
{
    int iVar1;
    int *newData;
    uint i;

    if (this != other) {
        if (this->capacity < other->size) {
            // Free existing buffer
            FUN_009c8f10(this->data);
            // Allocate new buffer with capacity = other->size
            iVar1 = other->size;
            this->capacity = iVar1;
            if (iVar1 == 0) {
                iVar1 = 0;
            }
            else {
                iVar1 = FUN_009c8e80(iVar1 * 4);
            }
            this->data = (int *)iVar1;
        }
        // Copy elements from other to this
        i = 0;
        if (other->size != 0) {
            do {
                newData = (int *)(this->data + i);
                if (newData != (int *)0x0) {
                    *newData = *(int *)(i * 4 + other->data);
                }
                i = i + 1;
            } while (i < other->size);
        }
        this->size = other->size;
    }
    return this;
}