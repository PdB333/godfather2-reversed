// FUNC_NAME: EARS::Framework::Object::QueryInterface
int __thiscall EARS::Framework::Object::QueryInterface(int iid, void** outPtr) {
    // Check for first known interface ID: 0xAF50FBA6
    if (iid == 0xAF50FBA6) {
        if (outPtr != nullptr) {
            *outPtr = this;
        }
        return 1;
    }
    // Not the first interface; clear output if provided
    if (outPtr != nullptr) {
        *outPtr = nullptr;
    }
    // Check for second known interface ID: 0xFFD2E5B1
    if (iid == 0xFFD2E5B1) {
        if (outPtr != nullptr) {
            *outPtr = this;
        }
        return 1;
    }
    // Unsupported interface
    return 0;
}