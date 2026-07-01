// FUNC_NAME: Container::removeByValue
void __fastcall Container::removeByValue(int *this)
{
    uint index = 0;
    if (this[0x14] != 0) {
        int *arrayPtr = (int *)this[0x13];
        do {
            if (*arrayPtr == this[0x20]) {
                if (index == 0xffffffff) {
                    return;
                }
                // Call virtual function at vtable+0x90 (likely onBeforeRemove)
                (**(code **)(*this + 0x90))();
                if (index != this[0x14] - 1U) {
                    // Shift last element into removed slot
                    *(undefined4 *)(this[0x13] + index * 4) =
                         *(undefined4 *)(this[0x13] + -4 + this[0x14] * 4);
                }
                this[0x14] = this[0x14] + -1;
                // Call virtual function at vtable+0x94 (likely onAfterRemove)
                (**(code **)(*this + 0x94))();
                return;
            }
            index = index + 1;
            arrayPtr = arrayPtr + 1;
        } while (index < (uint)this[0x14]);
    }
    return;
}