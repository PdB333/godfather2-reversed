// FUNC_NAME: CommandDispatcher::dispatch
// Address: 0x00591eb0
// Role: Dispatches a command for each handler in a list, if the handler's type byte is a small index (<10) and the corresponding handler function returns nonzero.

// The class structure (inferred):
// struct CommandDispatcher {
//     char count;          // +0x1: number of handlers
//     // padding to align pointer?
//     Handler** handlers;  // +0x8: pointer to array of Handler* (each Handler has at least a type byte at offset 0)
// };

typedef int (__thiscall *HandlerFunc)(void* param);

int __thiscall CommandDispatcher::dispatch(void* param_2) {
    char count = *(char*)((int)this + 1); // number of handlers
    if (count > 0) {
        int i = 0;
        do {
            // Get the handler's object pointer from the handlers array
            int handlerObjPtr = *(int*)(*(int*)((int)this + 8) + i * 4);
            // Read the first byte of the handler object (type field)
            char typeByte = **(char**)handlerObjPtr;
            // Only process if typeByte is a control character (< newline = 0x0a)
            if (typeByte < '\n') {
                // Call the dispatch function from the global jump table indexed by typeByte
                HandlerFunc func = (HandlerFunc)(&PTR_FUN_0103af90)[typeByte];
                if (func(param_2) != 0) {
                    return 1;
                }
            }
            i++;
        } while (i < count);
    }
    return 0;
}