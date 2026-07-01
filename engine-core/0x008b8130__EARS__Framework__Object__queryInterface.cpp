// FUNC_NAME: EARS::Framework::Object::queryInterface
int __thiscall EARS::Framework::Object::queryInterface(int this, int interfaceId, int *outInterfacePtr) {
    if (interfaceId == -0x6ca03148) { // 0x935FCEB8 - Interface A ID
        if (outInterfacePtr != (int *)0x0) {
            *outInterfacePtr = this;
        }
        return 1;
    }
    else {
        if (outInterfacePtr != (int *)0x0) {
            *outInterfacePtr = 0;
        }
        if (interfaceId == -0x2d1a4f) { // 0xFFD2E4B1 - Interface B ID
            if (outInterfacePtr != (int *)0x0) {
                *outInterfacePtr = this;
            }
            return 1;
        }
    }
    return 0;
}