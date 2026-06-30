// FUNC_NAME: BaseClass::constructor
// Address: 0x00598130
// Role: Constructor initializing a large object (size 0x54C) via vtable calls on sub-objects.

class BaseClass {
public:
    // Constructor returns object size (0x54C) for verification.
    // Calls a virtual function at vtable offset 0x10 on 'this' and then on sub-objects.
    int constructor() {
        // vTablePtr is a global pointer to the vtable of the class.
        void (*vtableMethod)(void*) = (void (*)(void*))(*(int*)DAT_01205590 + 0x10);
        int *pThis = (int*)this;
        
        // Initialize base class (call vtable method on 'this' with no extra args)
        vtableMethod(this);
        
        // Prepare constants
        int stackVal14 = 2; // offset value ??
        int *pStackVal14 = &stackVal14;
        
        // Initialize sub-object at offset +2 (likely a small member)
        vtableMethod((char*)pThis + 2, pStackVal14);
        
        // Pointer to local initialization data (0x50 bytes)
        char *localInitData = (char*)&stack0xffffffe4; // local struct/array
        vtableMethod((char*)pThis + 4, localInitData); // sub-object at +4
        
        // Initialize sub-object at +8 using updated stack value (now 2)
        vtableMethod((char*)pThis + 8, &stackVal20); // stackVal20 was set to 2 earlier
        // stackVal20 is reused; after first call it was set to 2
        
        // Initialize sub-object at +0xC with pointer to +2 area
        vtableMethod((char*)pThis + 0xC, (char*)pThis + 2);
        
        // Initialize sub-object at +0x4C with a block copy of 0x50 bytes from localInitData
        vtableMethod((char*)pThis + 0x4C, localInitData, 0x50);
        
        return 0x54C; // size of this object (1356 bytes)
    }
};