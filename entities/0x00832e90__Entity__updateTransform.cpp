// FUNC_NAME: Entity::updateTransform

class Transform {
public:
    explicit Transform();
    
    // Vtable methods:
    // +0x00: vtable pointer (PTR_LAB_00d7377c)
    // +0x04: compose(Transform* parent) - multiply with parent transform
    // ...
    
    // Fields (offsets in bytes, assuming 4-byte ints):
    // +0x1C: row0 (4 floats) -> [7]..[10]
    // +0x3C: row1 (4 floats) -> [15]..[18]
    // +0x4C: row2 (4 floats) -> [19]..[22]
    // +0x5C: row3.x (1 float) -> [23]
    // +0x60: total size = 96
    float m[16]; // Actually 4x4 matrix stored as 16 floats, but only partly used here.
    // ....
};

extern int8_t* gIdentityMatrixData;  // Points to constant identity matrix bytes (0x00d5ef88, etc.)
// We don't have exact global names, but they are loaded as ints.

extern Transform* getTransformFromSource(int* source); // FUN_0082b5d0
extern void* getSingletonAllocator(); // FUN_009c8f80
extern void constructTransform(Transform* self); // FUN_008334a0
extern void registerTransform(Transform* self); // FUN_00832420 - maybe add to manager

int __thiscall Entity::updateTransform(int thisPtr, int* source, int parentTransform) {
    bool isNew = false;
    char isValid = (*(char (__thiscall**)(int, int*))(*(int*)thisPtr + 0x14))(thisPtr, source);
    if (!isValid) {
        return 0;
    }
    
    Transform* transform = getTransformFromSource(source);
    if (transform == nullptr) {
        isNew = true;
        void* allocator = getSingletonAllocator();
        Transform* newTrans = (Transform*)(*(int (__thiscall**)(void*, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int))
            allocator)(allocator, 0x60, &stack0xfffffff0); // operator new
        if (newTrans == nullptr) {
            return 0;
        }
        constructTransform(newTrans);
        
        // These globals are the identity matrix row2 and row3 (partially)
        int iVar3 = DAT_00e44630;      // 0.0f? or some constant
        int iVar1 = DAT_00d5ef88;      // 1.0f? (0x3f800000)
        newTrans->m[0x13] = iVar1;        // row2.x = 1.0f
        newTrans->m[0x14] = DAT_00d6471c; // row2.y = 0.0f?
        newTrans->m[0x15] = _DAT_00d5cf70;// row2.z = 0.0f?
        newTrans->m[0x16] = iVar3;        // row2.w = 0.0f?
        newTrans->m[0x17] = iVar1;        // row3.x = 1.0f (identity's last row's first element? Actually identity row3 = (0,0,0,1) -> but here it's 1.0f? Probably not identity)
        // The above may set the third and fourth rows partially; the actual identity might be set elsewhere.
        
        transform = newTrans;
    }
    
    // Copy first two rows from source (assumed to be a 4x2 matrix or something)
    transform->m[7] = source[0];
    transform->m[8] = source[1];
    transform->m[9] = source[2];
    transform->m[10] = source[3];
    
    // If this object has a child/parent transform data, copy that as row1
    int* childData = *(int**)(thisPtr + 8); // offset 0x8: pointer to some child transform data
    if (childData != nullptr) {
        transform->m[15] = childData[0x24 / 4]; // +0x24
        transform->m[16] = childData[0x28 / 4];
        transform->m[17] = childData[0x2c / 4];
        transform->m[18] = childData[0x30 / 4];
    }
    
    // If a parentTransform is provided, compose this transform with it
    if (parentTransform != nullptr) {
        (*(void (__thiscall**)(Transform*, int))(*(int*)transform + 4))(transform, parentTransform);
    }
    
    if (isNew) {
        registerTransform(transform); // add to manager
    }
    
    return 1;
}