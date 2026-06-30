// FUNC_NAME: Entity::tryExecuteAction
void __fastcall Entity::tryExecuteAction(void)
{
    // Check if bit 12 (0x1000) is not set in flags at +0x10
    if (((this->flags >> 12) & 1) != 0) return;

    int* container = *(int**)(this + 0x70); // +0x70: pointer to an array container
    if (container == nullptr) return;

    int count = *(int*)(container + 0x18); // +0x18: number of elements
    if (count <= 0) return;

    int* dataPtr = *(int**)(container + 0x1c); // +0x1c: pointer to array of 0x18-byte elements
    if (dataPtr == nullptr) return;

    short activeIndex = *(short*)(this + 0x76); // +0x76: index into the array
    if (activeIndex < 0) return;
    if (activeIndex >= count) return;

    // Check if the element at activeIndex (offset = activeIndex * 0x18) is non-null
    // Original: *(int*)(container + 0x1c) + activeIndex * 0x18 != 0
    // This checks the address of the element, not its content.
    // Since dataPtr is already non-null, this is effectively always true,
    // but kept for fidelity.
    void* elementPtr = (void*)((int)dataPtr + activeIndex * 0x18);
    if (elementPtr == nullptr) return;

    // If all conditions pass, call the target function
    this->executeAction(); // FUN_00577a50
}