// FUN_NAME: EARSObject::constructor
// 0x00476d80 - Constructor for EARS game object base. Calls base initialization and conditionally invokes a virtual initialization function (vtable index 1) if bit 0 of initFlags is set.

class EARSObject {
public:
    EARSObject(unsigned char initFlags) {
        // Call base construction (FUN_00476dd0)
        baseConstruct();

        // If bit 0 set, call vtable function at index 1 (probably Initialize)
        if (initFlags & 1) {
            // Obtain vtable pointer from global object manager at offset 0x2d4
            int* globalManager = (int*)DAT_01223410;
            int* vtablePtr = *(int**)((char*)globalManager + 0x2d4); // +0x2d4
            // Vtable entry index 1 (offset 4 bytes) – typical virtual method slot
            void (*initFunc)(void*, int) = (void (*)(void*, int))vtablePtr[1];
            initFunc(this, 0);
        }
    }
};