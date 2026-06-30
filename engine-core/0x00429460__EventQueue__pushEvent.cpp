// FUNC_NAME: EventQueue::pushEvent
void EventQueue::pushEvent(int param)
{
    // g_eventQueueManager is a global pointer to the queue manager structure
    // Offset 0x14 holds a pointer to the current top of the event stack (a list of functor+parameter pairs)
    int** stackTopPtr = (int**)(g_eventQueueManager + 0x14);
    int* stackTop = *stackTopPtr;

    // Write the fixed handler address (function pointer table entry)
    *stackTop = (int)&PTR_LAB_0110b7c0;
    stackTop++;

    // Write the user-supplied parameter
    *stackTop = param;
    stackTop++;

    // Update the stored stack top pointer (advance by 8 bytes)
    *stackTopPtr = stackTop;
}