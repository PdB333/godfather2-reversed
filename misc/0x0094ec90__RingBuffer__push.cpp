// FUNC_NAME: RingBuffer::push
void __thiscall RingBuffer::push(int *this, int *element)
{
  int *currentSlot;
  int slotValue;
  
  // Calculate the current slot pointer based on head index and element size (8 bytes each)
  currentSlot = (int *)(*this + this[2] * 8);
  
  if (element != currentSlot) {
    slotValue = *currentSlot;
    if (*element != slotValue) {
      // If the element already has a value, release it first
      if (*element != 0) {
        FUN_004daf90(element); // likely release/decRef
      }
      *element = slotValue;
      // Update linked list pointers (doubly linked list)
      if (slotValue != 0) {
        element[1] = *(int *)(slotValue + 4);
        *(int **)(slotValue + 4) = element;
      }
    }
  }
  
  // Advance head index (circular buffer)
  this[2] = this[2] + 1;
  this[3] = this[3] - 1; // tail index decrement
  
  // Wrap head index if it exceeds capacity
  if (this[1] <= this[2]) {
    this[2] = 0;
  }
}