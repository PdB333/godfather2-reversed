// FUNC_NAME: ReliableSendWindow::~ReliableSendWindow
void __fastcall ReliableSendWindow::~ReliableSendWindow(ReliableSendWindow* this)
{
    // Array of 32 packet slots (12 bytes each) starts at offset 0x0C from this.
    // The first 4 bytes of each slot is a pointer to a dynamically allocated object;
    // if non-null, the object is freed.
    int* slotEnd = reinterpret_cast<int*>(this) + 99; // +99 ints = offset 0x18C (end of array)
    int iterationCount = 0x1F; // 31, but the loop runs 32 times (do-while with i >= 0)
    do {
        slotEnd -= 3; // move back one slot (3 ints = 12 bytes)
        if (*slotEnd != 0) {
            // Free the object at this slot (FUN_004daf90 -> likely operator delete or destructor)
            FUN_004daf90(slotEnd);
        }
        --iterationCount;
    } while (iterationCount >= 0);
    // Set vtable to purecall to prevent further virtual calls
    *reinterpret_cast<void**>(this) = &PTR___purecall_00e407a4;
}