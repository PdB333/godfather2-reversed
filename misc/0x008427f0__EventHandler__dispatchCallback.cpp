// FUNC_NAME: EventHandler::dispatchCallback
void __thiscall EventHandler::dispatchCallback(uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4) {
    // this+0x34: pointer to handler container
    // container+4: pointer to method table
    // methodTable+0x48: specific handler function
    void (**handlerTable)(uint32_t, uint32_t, uint32_t, uint32_t) = *(void (***)(uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t*)(this + 0x34) + 4);
    void (*handler)(uint32_t, uint32_t, uint32_t, uint32_t) = handlerTable[0x48 / 4];
    handler(arg1, arg2, arg3, arg4);
}