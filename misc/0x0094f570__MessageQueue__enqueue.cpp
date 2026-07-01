// FUNC_NAME: MessageQueue::enqueue
void __thiscall MessageQueue::enqueue(int param_1, int param_2, int param_3)
{
  int iVar1;
  int iVar2;
  int local_14 [3]; // auto_ptr / cleanup structure
  code *local_8; // destructor / deleter function pointer
  int local_4; // stored value (param_2)

  // Only insert if type is 1 or 4 and there is space in the queue
  if (((param_3 == 1) || (param_3 == 4)) &&
     (iVar1 = *(int *)(param_1 + 0x1c) /* m_count */, iVar1 < *(int *)(param_1 + 0x14) /* m_maxSize */)) {
    iVar2 = *(int *)(param_1 + 0x18) /* m_writeOffset */ + iVar1;
    // Increment count
    *(int *)(param_1 + 0x1c) = iVar1 + 1;
    // Initialize cleanup structure
    local_14[0] = 0;
    local_14[1] = 0;
    local_14[2] = 0;
    local_8 = (code *)0x0;
    local_4 = param_2;
    // Wrap around if past end of buffer
    if (*(int *)(param_1 + 0x14) /* m_maxSize */ <= iVar2) {
      iVar2 = iVar2 - *(int *)(param_1 + 0x14);
    }
    iVar1 = *(int *)(param_1 + 0x10) /* m_buffer */;
    // Probably calls a smart pointer constructor (e.g. for reference counting)
    FUN_004d3e20(local_14);
    // Write the data into the circular buffer slot (each slot is 0x14 bytes)
    *(int *)(iVar1 + iVar2 * 0x14 + 0x10) = local_4;
    // If something was allocated, invoke deleter (unlikely here, local_8 is nil)
    if (local_14[0] != 0) {
      (*local_8)(local_14[0]);
    }
    // Release global critical section
    FUN_00408680(&DAT_012069c4);
  }
  return;
}