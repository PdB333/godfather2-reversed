// FUNC_NAME: notifyInteractiveObjectAndSetFlag
void __thiscall notifyInteractiveObjectAndSetFlag(int this, int* listener)
{
    int* subject;

    if (listener != (int*)0x0) {
        subject = (int*)FUN_0072d1e0(this + 0x17c); // get component at this+0x17c
        if (subject != (int*)0x0) {
            // Call virtual function at vtable offset 0x260 on listener
            (**(code**)(*listener + 0x260))();
            // Set flag 0x4000 on subject at offset 0x1d0
            *(uint*)(subject + 0x1d0) |= 0x4000;
        }
    }
}