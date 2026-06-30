// FUNC_NAME: UnknownClass::~UnknownClass
struct UnknownClass {
    void* innerPtr; // +0x00
};

int* __thiscall UnknownClass::~UnknownClass(UnknownClass* this, byte freeFlag) {
    // Destroy inner object if present
    if (this->innerPtr != nullptr) {
        freeObject(this->innerPtr);
    }
    // Optionally free this object's memory (if freeFlag & 1)
    if (freeFlag & 1) {
        freeThis(this);
    }
    return this;
}