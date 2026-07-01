// FUNC_NAME: GameManager::initializeComponent
void __thiscall GameManager::initializeComponent(void* param_1) {
    int* componentPtr;
    int* vtablePtr;
    undefined4* stringPtr;
    char* className;
    int* classFactory;
    int* objectPtr;
    int vtableOffset;
    undefined4 result;
    int returnAddr;

    componentPtr = (int*)FUN_004baf90(param_1); // getComponentFromEntity(param_1)
    if ((componentPtr != (int*)0x0) && ((*(byte*)(componentPtr + 0x30) & 1) != 0)) {
        stringPtr = (undefined4*)FUN_004bb600(componentPtr); // getClassNameString(componentPtr)
        className = (char*)*stringPtr;
        if (className == (char*)0x0) {
            className = (char*)&DAT_0120546e; // default class name
        }
        classFactory = (int*)FUN_00568320(className); // findClassFactory(className)
        if ((((classFactory != (int*)0x0) && (*(int*)(DAT_01223484 + 0x30) != 0)) &&
            (*(int*)(DAT_01223484 + 8) != 0)) &&
            (objectPtr = (int*)(**(code**)**(undefined4**)(DAT_01223484 + 0x30))(), objectPtr != (int*)0x0)) {
            vtableOffset = *objectPtr; // first vtable entry
            result = (**(code**)(*classFactory + 0xc))(); // factory->create()
            (**(code**)(vtableOffset + 0xc))(result); // object->setSomething(result)
            (**(code**)*objectPtr)(); // object->initialize()
            (**(code**)(*objectPtr + 0x3c))(); // object->postInitialize()
            FUN_008b3dc0(&stack0x00000000, componentPtr + 8); // attachComponent(componentPtr+8)
            *(int**)(returnAddr + 4) = objectPtr; // store object pointer in return address area
        }
    }
    return;
}