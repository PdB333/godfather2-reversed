// FUNC_NAME: SomeClass::init
void SomeClass::init(void* owner, SomeClass* obj) {
    int* savedObj;          // iVar1
    void* alloc1;           // local_4

    // Allocate first sub-object (size 0x20) and store at offset +0x14
    allocateMemory(0x20, &alloc1);
    savedObj = obj;
    obj->field_0x14 = alloc1;

    // Allocate second sub-object, store at offset +0x10
    allocateMemory(0x20, &obj);  // reuses obj as temporary
    savedObj->field_0x10 = obj;

    // Call initialization routine with owner and the object
    initSubObjects(owner, savedObj);

    // Allocate third sub-object, store at offset +0x18
    allocateMemory(0x20, &obj);
    savedObj->field_0x18 = obj;
}