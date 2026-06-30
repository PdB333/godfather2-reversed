// FUNC_NAME: EventDispatcher::registerHandler
bool __thiscall EventDispatcher::registerHandler(int this, int* handler) {
    // this+0x1c: current count of registered handlers (max 5)
    uint count = *(uint*)(this + 0x1c);
    
    // Store handler in the fixed-size array at this+0x08 if space remains
    if (count < 5) {
        *(int**)(this + 8 + count * 4) = handler;    // array of 5 pointers at +0x08
        *(int*)(this + 0x1c) = count + 1;
    }
    
    // Retrieve the target object from this+0x20
    int* target = *(int**)(this + 0x20);
    
    // Call handler's method at vtable+0x14 to produce a value
    int result = (**(int (__thiscall**)(int*))(*handler + 0x14))(handler);
    
    // Pass that value to the target's method at vtable+0x30
    (**(void (__thiscall**)(int, int))(*target + 0x30))(target, result);
    
    // Return true if we added the handler (if count < 5), false otherwise
    return count < 5;
}