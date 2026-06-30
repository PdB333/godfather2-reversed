// FUNC_NAME: BaseSlotManager::~BaseSlotManager
// Destructor for a base class containing a fixed array of 32 slots (each 12 bytes, first int is a pointer)
// The array is located at offset 0x10 (this[4]) and ends at offset 0x190 (this[100])
void __thiscall BaseSlotManager_destructor(BaseSlotManager* this)
{
    int* slotPtr;
    int** slotPtrPtr;
    int index;

    // Start pointer just past the array end (this + 0x190)
    slotPtrPtr = (int**)(this + 100);
    index = 31;
    do
    {
        // Move back by one slot (3 ints = 12 bytes)
        slotPtr = slotPtrPtr[-3];
        slotPtrPtr = slotPtrPtr - 3;
        if (*slotPtrPtr != 0)
        {
            // Destructor for the slot object
            FUN_004daf90(slotPtr);
        }
        index--;
    } while (index >= 0);

    // Set vtable to purecall placeholder (base class)
    this->vtable = &PTR___purecall_00e407a4;
}