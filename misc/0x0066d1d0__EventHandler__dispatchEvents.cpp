// FUNC_NAME: EventHandler::dispatchEvents
void __thiscall EventHandler::dispatchEvents(int* thisPtr, undefined4 event1, undefined4 event2)
{
    int* subObject; // local_4 - output from QueryInterface
    char queryResult; // cVar2
    int* thisObj; // unaff_EBP - likely a copy of thisPtr (decompiler artifact)

    if (overrideHandler == (code*)0x0) {
        subObject = (int*)0x0;
        // Virtual function at +0x10 is QueryInterface with a known GUID
        queryResult = (**(code**)(*thisPtr + 0x10))(0x4f3368d0, &subObject);
        if ((queryResult != '\0') && (thisObj != 0)) {
            // Dereference this +0x260 to get a sub-handler object
            subObject = (int*)*(int*)((int)thisObj + 0x260); // +0x260: pointer to sub-handler
            if (subObject != 0) {
                somePrepareFunc();
                // Call virtual function at +0x48 on the sub-handler's vtable (via subObject+0xd0)
                (**(code**)(*(int*)((int)subObject + 0xd0) + 0x48))(event1);
            }
            subObject = (int*)*(int*)((int)thisObj + 0x260);
            if (subObject != 0) {
                somePrepareFunc();
                // Call virtual function at +0x50
                (**(code**)(*(int*)((int)subObject + 0xd0) + 0x50))(event2);
            }
        }
        return;
    }
    // If override handler is set, forward the call
    subObject = thisPtr;
    (*overrideHandler)(thisPtr, event1, event2);
}