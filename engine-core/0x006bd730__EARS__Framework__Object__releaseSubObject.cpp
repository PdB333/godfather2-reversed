// FUNC_NAME: EARS::Framework::Object::releaseSubObject
// Address: 0x006bd730

void __thiscall Object::releaseSubObject(Object* this) {
    // Retrieve sub-object pointer from member at offset 0x60
    int* subObject = (int*)FUN_006bca80(this + 0x60); // Getter for sub-object, returns pointer to object with vtable
    if (subObject != nullptr) {
        // Call virtual function at vtable offset 0x20 (index 8) on sub-object, passing 'this' as argument
        // Likely a destructor/cleanup method that removes this from the sub-object
        (*(void (__thiscall**)(Object*))(*subObject + 0x20))(this);
    }
}