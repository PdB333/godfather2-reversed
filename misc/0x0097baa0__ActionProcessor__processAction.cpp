// FUNC_NAME: ActionProcessor::processAction

void __fastcall ActionProcessor::processAction(void* thisPtr)
{
    // +0x30: pointer to first action handler
    int* actionHandler0 = *(int**)((char*)thisPtr + 0x30);
    // +0x54: pointer to second action handler
    int* actionHandler1 = *(int**)((char*)thisPtr + 0x54);
    // +0x78: pointer to third action handler
    int* actionHandler2 = *(int**)((char*)thisPtr + 0x78);
    // +0x9c: pointer to fourth action handler
    int* actionHandler3 = *(int**)((char*)thisPtr + 0x9c);
    // +0xe4: vtable pointer for handler interface
    int* handlerVtable = *(int**)((char*)thisPtr + 0xe4);

    if (actionHandler0 == 0)
    {
        if (actionHandler1 == 0)
        {
            if (actionHandler2 == 0)
            {
                if (actionHandler3 != 0 && handlerVtable != 0)
                {
                    // +0x7c: argument for fourth handler
                    void* arg3 = *(void**)((char*)thisPtr + 0x7c);
                    // vtable[3] offset 0x0c (third virtual function)
                    ((void (__thiscall*)(void*))handlerVtable[3])(arg3);
                }
            }
            else if (handlerVtable != 0)
            {
                // +0x58: argument for third handler
                void* arg2 = *(void**)((char*)thisPtr + 0x58);
                // vtable[2] offset 0x08
                ((void (__thiscall*)(void*))handlerVtable[2])(arg2);
            }
        }
        else if (handlerVtable != 0)
        {
            // +0x34: argument for second handler
            void* arg1 = *(void**)((char*)thisPtr + 0x34);
            // vtable[1] offset 0x04
            ((void (__thiscall*)(void*))handlerVtable[1])(arg1);
        }
    }
    else if (handlerVtable != 0)
    {
        // +0x10: argument for first handler
        void* arg0 = *(void**)((char*)thisPtr + 0x10);
        // vtable[0] offset 0x00
        ((void (__thiscall*)(void*))handlerVtable[0])(arg0);
    }
}