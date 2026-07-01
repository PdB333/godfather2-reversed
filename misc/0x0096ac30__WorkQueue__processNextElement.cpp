// FUNC_NAME: WorkQueue::processNextElement
void __fastcall WorkQueue::processNextElement(WorkQueue* this)
{
    // Calculate pointer to next element: base + currentIndex * elementSize (0x114 bytes)
    char* elementPtr = this->arrayBase + this->currentIndex * 0x114;
    // Process the element (calls a function on it, likely a virtual method or handler)
    FUN_00968cc0(elementPtr);
    
    // Advance index, wrap around if past capacity
    this->currentIndex++;
    this->remaining--;
    
    if (this->capacity <= this->currentIndex) {
        this->currentIndex = 0;
    }
}