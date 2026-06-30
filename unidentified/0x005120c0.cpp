// FUN_005120c0: EARSCharacter::updateTransform

// Global data references from the decompiled output
extern int DAT_0121b638; // Possibly a pointer to some system or state (e.g., active scene)
extern int DAT_0121b63c; // Another pointer, used when DAT_0121b638 is zero
extern int DAT_0121a390; // Global handle/pointer (e.g., render system)
extern int DAT_01218d40; // Global constant or resource
extern int* DAT_0121b0a4; // Pointer to structure with vtable (e.g., a factory or manager)
extern float DAT_00e2b04c; // Global scale factor (e.g., time delta or resolution scaling)
extern float* DAT_012233a4; // Pointer to float array (e.g., color multiplier or contrast values)
// FS segment offset 0x2c is TLS pointer in Windows, used to get per-thread data
#define TLS_BASE (*(int**)(__readfsdword(0x2c)))  // Simplified; actual inline asm

// Forward declarations of called functions (these would be part of the engine)
void __thiscall FUN_005379d0(int arg1, int arg2); // e.g., setSomeValue
void __cdecl FUN_0060b020(int a, int b, int* c); // e.g., applyEffect
void __thiscall FUN_0056b420(int a, int b, float* vec3); // e.g., computeTransform
void __thiscall FUN_00537bb0(int arg1, float* vec4); // e.g., setLighting

struct TransformComponent {
    char unknown_0x60[0x61]; // +0x00 to +0x60 padding
    uint8_t slotIndex; // +0x61 – used in virtual call
    char unknown_0x62[0x0A]; // padding to 0x6C
    int field_0x6C; // +0x6C
    float position[3]; // +0x70 – assumed 3 floats (12 bytes)
    char unknown_0x7C[0x24]; // padding to 0xA0
    int someInt; // +0x64? Actually +0x64 is exactly 100 decimal -> 0x64. Wait, within this sub-object at +0x10 of main, offset +100 means offset 0x64 from sub-object base.
    // But in the code: *(int *)(*(int *)(in_EAX + 0x10) + 100) -> that's offset 0x64 from the sub-object.
    // Since TransformComponent is at this+0x10, the offset 0x64 within it is transformComponent+0x64.
    // We'll define that field as someInt here, but note it's after position and some padding.
    // Actually let's recalculate: sub-object base = this+0x10. Fields: +0x61 (byte), +0x6c (int), +0x70 (start of vector), +0x64 (100 decimal) is before those? Wait, 0x64 < 0x70, so it's after +0x61 but before +0x6c. This indicates the structure layout is not contiguous in a simple way; we'll put the field at the correct offset.
};

struct RenderComponent {
    void** vtable; // +0x00
    // +0x08: virtual function at index 2 (offset 8) is called
    // Actual data follows
};

class EARSCharacter {
public:
    // Assume vtable at +0x00
    int field_0x08; // +0x08
    TransformComponent* transformComp; // +0x10
    int field_0x58; // +0x58 – actually a pointer to RenderComponent (cast to int? but used as first arg to virtual call)
    int field_0x68; // +0x68
    int field_0x64; // +0x64 (100 decimal) – but note: 0x64 is also offset within this for first arg to FUN_005379d0. Wait, the code uses *(int *)(in_EAX + 100) (100 decimal = 0x64) and *(int *)(in_EAX + 0x68). So both are direct members of the main class. So the class has fields at +0x64 and +0x68. That conflicts with the transformComp pointer at +0x10? No, that's fine, they are different offsets.
    // So: +0x00 vtable, +0x08 field, +0x10 TransformComponent*, +0x58 some int, +0x64 some int, +0x68 some int.

    void updateTransform();
};

void EARSCharacter::updateTransform() {
    // First call: FUN_005379d0(this->field_0x64, this->field_0x68)
    FUN_005379d0(field_0x64, field_0x68);

    int iVar1;
    if (DAT_0121b638 == 0) {
        iVar1 = *(int*)(DAT_0121b63c + 0x20);
    } else {
        iVar1 = *(int*)(DAT_0121b638 + 0x18);
    }
    if (iVar1 != 0) {
        FUN_0060b020(DAT_0121a390, iVar1, &DAT_01218d40);
    }

    // Virtual call on the object pointed to by DAT_0121b0a4
    // The object at DAT_0121b0a4 has a vtable; we call the 3rd virtual function (offset +8)
    // First argument is this->field_0x58 (interpreted as a pointer to some object)
    // Second argument is a byte from transformComp->slotIndex
    void** vtable = *(void***)DAT_0121b0a4;
    auto func = (void(__thiscall*)(int, uint8_t))vtable[2]; // index 2 = offset 8 / 4
    func(field_0x58, transformComp->slotIndex);

    // Compute scaled floats from global data
    float scaledVec4[4];
    scaledVec4[0] = DAT_00e2b04c * DAT_012233a4[0x40 / 4]; // offset 0x40 -> 16th float
    scaledVec4[1] = DAT_00e2b04c * DAT_012233a4[0x44 / 4];
    scaledVec4[2] = DAT_00e2b04c * DAT_012233a4[0x48 / 4];
    scaledVec4[3] = DAT_00e2b04c * DAT_012233a4[0x4c / 4];

    // Compute argument for FUN_0056b420 using TLS and this fields
    int* tlsPtr = *(int**)TLS_BASE; // unaff_FS_OFFSET + 0x2c gives base of TLS
    int someValue = *(int*)((char*)tlsPtr + 8); // deref tlsPtr, then +8
    int firstArg = (int)((char*)tlsPtr + 0x50) + field_0x08; // Actually: *(int *)(**(int **)(unaff_FS_OFFSET + 0x2c) + 8) + 0x50 + this->field_0x08
    // Let's recalc properly:
    // **(int **)(unaff_FS_OFFSET + 0x2c) gives a pointer p, then *(int*)(p + 8) gives p2_int, then that + 0x50 + this+8.
    // So p = *(int**)TLS_BASE; p2 = *(int*)(p + 8); then firstArg = p2 + 0x50 + field_0x08;
    int p2 = *(int*)((char*)tlsPtr + 8);
    int firstArg = p2 + 0x50 + field_0x08;

    int secondArg = (int)&transformComp->position; // transformComp + 0x70
    // auStack_38 is a 12-byte buffer on stack; we allocate a local array
    float vec3Buf[3]; // 12 bytes (3 floats)
    FUN_0056b420(firstArg, secondArg, vec3Buf);

    // Store something from transformComp->field_0x6C into local (though not used further, maybe for debug)
    int stored = transformComp->field_0x6C;

    // Final call: FUN_00537bb0(transformComp->someInt, &scaledVec4)
    // Note: transformComp + 100 decimal = transformComp + 0x64
    FUN_00537bb0(transformComp->someInt, scaledVec4);
}