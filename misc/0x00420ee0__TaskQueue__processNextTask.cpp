// FUNC_NAME: TaskQueue::processNextTask

void __fastcall TaskQueue::processNextTask(int this)
{
    uint* delegateArray; // pointer to a delegate structure
    void* handlerObject;
    int (__thiscall *handlerFunc)(void*, int*); // handler function with this pointer and params

    // Get pointer to delegate structure from this+0x18
    delegateArray = *(uint**)(this + 0x18);

    // Build params structure on stack (order matches decompiler)
    int paramVal0 = delegateArray[2]; // +0x08 in delegate
    int paramVal1 = delegateArray[1]; // +0x04 in delegate
    int paramVal2 = *(int*)(this + 0x14); // additional parameter from this
    int* paramPtr3 = (int*)(this + 0x1c); // pointer to another member of this

    // Get the target handler object: delegateArray[0] is a pointer to an object with vtable
    handlerObject = (void*)delegateArray[0];

    // Get vtable pointer (first 4 bytes of handlerObject)
    // Function at vtable offset +0x08 (third entry) is the handler
    handlerFunc = (int (__thiscall*)(void*, int*))(*(void**)(*(int*)handlerObject + 8));

    // Call the handler with the params structure address
    handlerFunc(handlerObject, (int*)&paramVal0);
}