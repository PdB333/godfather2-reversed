// FUNC_NAME: EARSObject::resolveInterface
int __thiscall EARSObject::resolveInterface(int interfaceId, int* outPtr)
{
    int result;
    
    if (interfaceId == 0x6b583526) {
        // Special case: return this object pointer.
        if (outPtr != nullptr) {
            *outPtr = (int)this;
        }
        return 1;
    }
    else if (interfaceId == 0x3eb08af9) {
        // Dispatch to a virtual method in the interface pointed to by +0x20
        if (*(int**)(this + 0x20) != nullptr) {
            // Indirect call through vtable +8 (likely a method like Execute or Dispatch)
            result = (*(code**)(**(int**)(this + 0x20) + 8))();
            return result;
        }
    }
    else {
        if (outPtr != nullptr) {
            *outPtr = 0;
        }
        if (interfaceId == 0xfff2e5b1) {  // -0x2d1a4f as unsigned
            // Another special case: return this object pointer.
            if (outPtr != nullptr) {
                *outPtr = (int)this;
            }
            return 1;
        }
    }
    return 0;
}