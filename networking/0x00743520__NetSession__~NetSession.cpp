// FUNC_NAME: NetSession::~NetSession
// Address: 0x00743520
// Role: Destructor for NetSession (EARS networking session)
// Offsets:
//   +0x50 (param_1[0x14]): Pointer to a managed resource (released via FUN_00878dc0 if state not 0 or 0x48)
//   +0x54 (param_1[0x15]): State/tag field – if != 0 and != 0x48, triggers release of the resource at +0x50; later freed as pointer block via FUN_004daf90
//   +0x6C (param_1[0x1b]): Another pointer block released via FUN_004daf90
//   vtable: set to base class vtable before cleanup (PTR_LAB_00d63bdc)

void __thiscall NetSession::~NetSession(class NetSession* this)
{
    int* stateField = reinterpret_cast<int*>(reinterpret_cast<uint8_t*>(this) + 0x54); // piVar1 = this + 0x15*4
    this->vtable = &PTR_LAB_00d63bdc; // set vtable to base class (NetSession or common base)
    if (*stateField != 0 && *stateField != 0x48) {
        FUN_00878dc0(*reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(this) + 0x50)); // release resource at +0x50
    }
    FUN_007429f0(); // base class destructor (NetSession::__base_dtor?) or member cleanup
    if (*reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(this) + 0x6C) != 0) {
        FUN_004daf90(reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(this) + 0x6C)); // release linked list / block at +0x6C
    }
    if (*stateField != 0) {
        FUN_004daf90(stateField); // release the state block itself (pointer array)
    }
    FUN_004ac1e0(); // final cleanup (e.g., base destructor chain end)
}