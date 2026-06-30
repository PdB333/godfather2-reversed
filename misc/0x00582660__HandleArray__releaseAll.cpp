// FUNC_NAME: HandleArray::releaseAll
class HandleArray {
public:
    int count;            // +0x04
    int** elementArray;   // +0x08
    int* vtableOrFunc;    // +0x0C

    void releaseAll();
};

void HandleArray::releaseAll() {
    for (int i = 0; i < count; i++) {
        int* element = elementArray[i];
        if (element != nullptr) {
            // element is a handle (pointer to pointer)
            // *element is the actual object pointer
            void* objPtr = *reinterpret_cast<void**>(element);
            // Call virtual function at vtable[1] (offset 4) on the object
            typedef void (__thiscall *DestroyFunc)(void*, int);
            DestroyFunc destroy = (DestroyFunc)(*(int**)this->vtableOrFunc)[1];
            destroy(objPtr, 0);          // release object
            destroy(element, 0);          // release handle
        }
    }
}