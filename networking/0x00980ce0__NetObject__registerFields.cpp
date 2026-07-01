// FUNC_NAME: NetObject::registerFields
// Address: 0x00980ce0
// This function registers all network-replicated fields for a class.
// Called during initialization of a NetObject-derived instance.
// The repeated calls to registerField set up offsets, types, and optional callbacks for ghost replication.

void __thiscall NetObject::registerFields(void* thisPtr)
{
    // Base class initialization (likely SimObject or NetObject base)
    baseInit();

    // Register fields with the net property system.
    // Each call: registerField(typeInfo, fieldAddress, typeCode, callback, flags1, flags2)
    // typeCode: 0=float, 1=int32, 2=byte, 5=short? 6=likely quaternion/vector3?
    // callback: function for validation or custom setter, 0 = none
    // flags: last two ints appear to be booleans for network behaviour

    registerField(&DAT_00d88600, reinterpret_cast<uint8_t*>(thisPtr) + 0xf8, 6, nullptr, 0, 1);   // +0xf8: quaternion? type 6
    registerField(&DAT_00d8c238, reinterpret_cast<uint8_t*>(thisPtr) + 0x60, 0, nullptr, 0, 1);   // +0x60: position (float3)
    registerField(&DAT_00e40ec8, reinterpret_cast<uint8_t*>(thisPtr) + 100, 0, nullptr, 0, 1);    // +100: float field
    registerField(&DAT_00e3d6f8, reinterpret_cast<uint8_t*>(thisPtr) + 0x68, 0, nullptr, 0, 1);   // +0x68: rotation (float)
    registerField(&DAT_00d8e6e4, reinterpret_cast<uint8_t*>(thisPtr) + 0x6c, 0, &LAB_00980cc0, 0, 0); // +0x6c: float with notification callback
    registerField(&DAT_00d90498, reinterpret_cast<uint8_t*>(thisPtr) + 0x70, 5, &LAB_00980cd0, 0, 0); // +0x70: type 5 (16-bit? short)
    registerField(&DAT_00d8e774, reinterpret_cast<uint8_t*>(thisPtr) + 0xb4, 5, &LAB_00980330, 0, 0); // +0xb4: type 5 with callback
    registerField(&DAT_00d86468, reinterpret_cast<uint8_t*>(thisPtr) + 0x100, 1, nullptr, 0, 1);   // +0x100: int32
    registerField(&DAT_00d856e8, reinterpret_cast<uint8_t*>(thisPtr) + 0x104, 1, nullptr, 0, 1);   // +0x104: int32
    registerField(&DAT_00d90490, reinterpret_cast<uint8_t*>(thisPtr) + 0x108, 1, nullptr, 0, 1);   // +0x108: int32
    registerField(&DAT_00d878bc, reinterpret_cast<uint8_t*>(thisPtr) + 0x10c, 1, nullptr, 0, 1);   // +0x10c: int32
    registerField(&DAT_00d878c4, reinterpret_cast<uint8_t*>(thisPtr) + 0x110, 1, nullptr, 0, 1);   // +0x110: int32
    registerField(&DAT_00d90488, reinterpret_cast<uint8_t*>(thisPtr) + 0x114, 1, nullptr, 0, 1);   // +0x114: int32
    registerField(&DAT_00d90480, reinterpret_cast<uint8_t*>(thisPtr) + 0x118, 1, nullptr, 0, 1);   // +0x118: int32
    registerField(&DAT_00d90478, reinterpret_cast<uint8_t*>(thisPtr) + 0x11c, 1, nullptr, 0, 1);   // +0x11c: int32
    registerField(&DAT_00d873d4, reinterpret_cast<uint8_t*>(thisPtr) + 0x120, 1, nullptr, 0, 1);   // +0x120: int32
    registerField(&DAT_00d878b4, reinterpret_cast<uint8_t*>(thisPtr) + 0x124, 1, nullptr, 0, 1);   // +0x124: int32
    registerField(&DAT_00d90470, reinterpret_cast<uint8_t*>(thisPtr) + 0x128, 2, nullptr, 0, 1);   // +0x128: uint8
    registerField(&DAT_00d90468, reinterpret_cast<uint8_t*>(thisPtr) + 0x12a, 2, nullptr, 0, 1);   // +0x12a: uint8
    registerField(&DAT_00d90460, reinterpret_cast<uint8_t*>(thisPtr) + 0x129, 2, nullptr, 0, 1);   // +0x129: uint8
    registerField(&DAT_00d90458, reinterpret_cast<uint8_t*>(thisPtr) + 299, 2, &LAB_0097f060, 0, 0); // offset 299 decimal (0x12b): uint8 with callback
    registerField(&DAT_00d90450, reinterpret_cast<uint8_t*>(thisPtr) + 300, 2, nullptr, 0, 1);   // offset 300 decimal (0x12c): uint8
    registerField(&DAT_00d6e9d8, reinterpret_cast<uint8_t*>(thisPtr) + 0x12d, 2, nullptr, 0, 1); // +0x12d: uint8
    registerField(&DAT_00d90448, reinterpret_cast<uint8_t*>(thisPtr) + 0xfc, 6, nullptr, 0, 1);   // +0xfc: type 6 (quat?)
    registerField(&DAT_00d90440, reinterpret_cast<uint8_t*>(thisPtr) + 0x130, 0, nullptr, 0, 1);  // +0x130: float (last field)
}