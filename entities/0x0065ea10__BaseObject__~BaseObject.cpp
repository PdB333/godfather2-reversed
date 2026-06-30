// FUNC_NAME: BaseObject::~BaseObject

// 0x0065ea10 - Destructor with optional memory deallocation.
// Calls the actual cleanup routine (FUN_0065ea30), then if the deleteFlag's
// lowest bit is set, calls operator delete (FUN_009c8eb0) to free the object.
void __thiscall BaseObject::~BaseObject(byte deleteFlag) {
    this->destroy();
    if (deleteFlag & 1) {
        this->operator delete(this);
    }
}