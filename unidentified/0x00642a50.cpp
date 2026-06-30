// 00642a50 - Wrapper to set a priority or type constant (4) on a target object
// FUNC_NAME: setPriorityTo4
void __fastcall setPriorityTo4(void* unusedThis, int targetObject)
{
    // Buffer to hold the constant value; only first element used
    int priorityBuffer[3];
    priorityBuffer[0] = 4;
    // Call internal priority setter with the buffer
    setPriority(targetObject, priorityBuffer);
}