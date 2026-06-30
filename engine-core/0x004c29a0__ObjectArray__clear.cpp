// FUNC_NAME: ObjectArray::clear
void __fastcall ObjectArray::clear(int thisPtr) {
    // +0x208: pointer to array of node pointers (Node**)
    // +0x20c: count of nodes (array length)
    // +0x210: capacity (set to 0 after clear)
    Node** current = *(Node***)(thisPtr + 0x208);
    Node** end = current + *(int*)(thisPtr + 0x20c);
    
    if (current != end) {
        do {
            Node* node = *current;
            if (node != nullptr) {
                // Node structure: at offset 0: pointer to ref-counted object
                RefCountedObject* obj = node->object;
                // Decrement reference count (assumed to be at offset 0 of object)
                obj->refCount--;
                if (obj->refCount == 0) {
                    // vtable pointer at offset 0x10C (0x43*4), call virtual destructor at vtable+0x18
                    (**(code**)(*(int*)obj->vtablePtr + 0x18))(obj);
                }
                // Node+0x4: another pointer (maybe name string or resource handle)
                if (node->extraData != nullptr) {
                    operatorDelete(node->extraData);
                }
                operatorDeleteArray(node);
            }
            current++;
        } while (current != end);
    }
    
    // Reset array state
    *(int*)(thisPtr + 0x20c) = 0;            // count = 0
    operatorDelete(*(void**)(thisPtr + 0x208)); // free the array buffer
    *(void**)(thisPtr + 0x208) = nullptr;    // buffer = nullptr
    *(int*)(thisPtr + 0x210) = 0;            // capacity = 0
}