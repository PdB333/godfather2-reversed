// FUNC_NAME: NetObject::constructor
class NetObject {
public:
    // +0x00: vtable pointer (initialized to &PTR_LAB_00d5ebb0)
    void* vtable;
    // +0x04: secondary vtable (initialized to &PTR_LAB_00d5eb9c)
    void* vtable2;
    // +0x08: unknown field
    int field_08;
    // +0x0C: manager pointer (param_2)
    void* pManager;
    // +0x10: data pointer (param_3)
    void* pData;
    // +0x14: resource handle (from secondary init)
    int hResource;
    // +0x18: field set by FUN_006beed0
    int field_18;
    // +0x1C .. +0x3C: zeroed fields
    int field_1C;
    int field_20;
    int field_24;
    int field_28;
    int field_2C;
    int field_30;
    int field_34;
    int field_38;
    int field_3C;

    // Constructor-like method
    NetObject* constructor(void* pManager, void* pData, int param_4, char bFlag1, char bFlag2);
};

// External function declarations
extern void FUN_006b4ca0();
extern int FUN_008c74d0(void* ptr);
extern void FUN_006beed0(int param_4, int* outVal, int arg3);
extern void FUN_006bf2b0();
extern int FUN_0043b870(void* global);
extern void FUN_009aefd0(int* ptr, int flags);
extern void FUN_006bec10();
extern void FUN_008c36b0(int msgId, void* manager, int zero);
extern void FUN_008c3660(int msgId, void* manager, int zero);

// Global data
extern int* DAT_012233a0;
extern void* DAT_01131018;

NetObject* NetObject::constructor(void* pManager, void* pData, int param_4, char bFlag1, char bFlag2) {
    // Zero initial fields
    field_08 = 0;
    vtable2 = &PTR_LAB_00d58278; // placeholder global label
    pManager = pManager;
    pData = pData;
    vtable = &PTR_LAB_00d5ebb0;
    vtable2 = &PTR_LAB_00d5eb9c;
    hResource = 0;
    field_18 = 0;
    field_1C = 0;
    field_20 = 0;
    field_24 = 0;
    field_28 = 0;
    field_2C = 0;
    field_30 = 0;
    field_34 = 0;
    field_38 = 0;
    field_3C = 0;

    // Base initialization
    FUN_006b4ca0();

    // Get resource from manager (offset 0x40)
    hResource = FUN_008c74d0(*(void**)((char*)pManager + 0x40));

    // Initialize field at +0x18
    FUN_006beed0(param_4, &field_18, *(int*)((char*)pData + 0x54));

    // Additional setup
    FUN_006bf2b0();

    if (bFlag1 != '\0') {
        field_2C |= 2; // set bit 1 at offset 0x2C
        // Check global condition
        if ((*(int**)(DAT_012233a0 + 4) != nullptr) && (*(int**)(DAT_012233a0 + 4) != (int*)0x1f30)) {
            if (FUN_0043b870(DAT_01131018) != 0) {
                // Set flag on secondary vtable (offset +4)
                FUN_009aefd0((int*)&vtable2, 0x8000);
            }
        }
    }

    if (bFlag2 != '\0') {
        FUN_006bec10();
        return this;
    }

    // Conditional message sending
    if ((field_20 != 0) && (field_28 != 0)) {
        if (*(int*)((char*)hResource + 0x54) != 0x637b907) {
            if (*(int*)((char*)pData + 0x54) == 0x637b907) {
                FUN_008c36b0(0xdb4df9fa, pManager, 0);
                return this;
            }
            FUN_008c3660(0xdb4df9fa, pManager, 0);
            return this;
        }
        FUN_008c36b0(0x4c2f9353, pManager, 0);
    }
    return this;
}