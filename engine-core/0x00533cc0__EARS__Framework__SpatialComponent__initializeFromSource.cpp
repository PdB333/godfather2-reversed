// FUNC_NAME: EARS::Framework::SpatialComponent::initializeFromSource
// Address: 0x00533cc0
// Role: Initializes a SpatialComponent (allocates two 4x4 matrix slots, copies source data, sets flags)
// Known class: EARS::Framework::SpatialComponent (based on vtable at 0x00e37110 and identity matrix setup)

#include <cstdint>

// Forward declarations
struct MatrixPool; // managed per-thread via FS[0x2c]
extern uint32_t* getThreadLocalPoolBase(); // from FS[0x2c] -> [0x8]
extern uint64_t allocateMatrixHandles(); // returns handle pair (lower=index1, higher=index2) – placeholder
extern void postSpatialInit(); // FUN_00533fb0 placeholder

// The constant value (likely 1.0f as float)
constexpr uint32_t CONST_ONE = 0x3F800000; // 1.0f

// Structure representing a matrix slot in the pool
struct Matrix4x4 {
    float m[4][4];
};

// Decompiled function
// This assumes the function is a member taking 'this' in ECX and a source pointer in EAX (non-standard __thiscall)
// We model it as __thiscall with an additional parameter in EAX (source)
SpatialComponent* __thiscall SpatialComponent::initializeFromSource(SpatialComponent* this, SpatialComponent* source) {
    // this: ECX
    // source: EAX (passed by caller; in decompiler as 'in_EAX')
    // local_18[0] is a pointer to source+4

    // Step 1: Set vtable
    this->vtable = (VTablePtr)&PTR_FUN_00e37110;

    // Step 2: Initialize handle fields to zero before allocation
    this->matrixHandleLow  = 0; // offset +0x10
    this->matrixHandleHigh = 0; // offset +0x14

    // Step 3: Allocate two matrix indices from the pool (FUN_00534560 returns a 64-bit pair)
    uint32_t handlePairLow, handlePairHigh;
    uint64_t handlePair = allocateMatrixHandles(); // returns in EAX:EDX
    this->matrixHandleLow  = (uint32_t)(handlePair & 0xFFFFFFFF);
    this->matrixHandleHigh = (uint32_t)(handlePair >> 32);

    this->unkField0x18 = 0; // offset +0x18

    // Step 4: If allocation failed, set error flag at +0xD and return early
    if (this->matrixHandleLow == 0) {
        *(uint8_t*)((intptr_t)this + 0x0D) = 1; // error flag
        return this;
    }

    // Step 5: Copy first field from source to this
    this->ownerOrType = source->field0x00; // offset +0x04 = *source

    // Step 6: Get source's second field (used for flags processing later)
    uint32_t* sourceFlagsPtr = (uint32_t*)(source->field0x04); // offset +0x04 of source? Actually source[1] -> local_18[0]

    // Step 7: Access per-thread matrix pool base
    int* threadData = *(int**)(__readfsdword(0x2C)); // FS segment offset 0x2C
    int* poolBasePtr = *(int**)(threadData + 2); // threadData[2] is the matrix pool base? Actually deref: *(int *)(iVar1 + 8)

    // Step 8: Initialize first 4x4 matrix (at offset 0x10 within pool, indexed by matrixHandleLow)
    Matrix4x4* mat1 = (Matrix4x4*)( (uint8_t*)poolBasePtr + 0x10 + this->matrixHandleLow );
    mat1->m[0][0] = *(float*)&CONST_ONE; mat1->m[0][1] = 0.0f; mat1->m[0][2] = 0.0f; mat1->m[0][3] = 0.0f;
    mat1->m[1][0] = 0.0f; mat1->m[1][1] = *(float*)&CONST_ONE; mat1->m[1][2] = 0.0f; mat1->m[1][3] = 0.0f;
    mat1->m[2][0] = 0.0f; mat1->m[2][1] = 0.0f; mat1->m[2][2] = *(float*)&CONST_ONE; mat1->m[2][3] = 0.0f;
    mat1->m[3][0] = 0.0f; mat1->m[3][1] = 0.0f; mat1->m[3][2] = 0.0f; mat1->m[3][3] = *(float*)&CONST_ONE;

    // Step 9: Initialize second 4x4 matrix (at offset 0x50 + matrixHandleLow)
    Matrix4x4* mat2 = (Matrix4x4*)( (uint8_t*)poolBasePtr + 0x50 + this->matrixHandleLow );
    mat2->m[0][0] = *(float*)&CONST_ONE; mat2->m[0][1] = 0.0f; mat2->m[0][2] = 0.0f; mat2->m[0][3] = 0.0f;
    mat2->m[1][0] = 0.0f; mat2->m[1][1] = *(float*)&CONST_ONE; mat2->m[1][2] = 0.0f; mat2->m[1][3] = 0.0f;
    mat2->m[2][0] = 0.0f; mat2->m[2][1] = 0.0f; mat2->m[2][2] = *(float*)&CONST_ONE; mat2->m[2][3] = 0.0f;
    mat2->m[3][0] = 0.0f; mat2->m[3][1] = 0.0f; mat2->m[3][2] = 0.0f; mat2->m[3][3] = *(float*)&CONST_ONE;

    // Step 10: Additional fields
    this->unkField0x08 = 0; // offset +0x08
    // Zero the first word of the first matrix base? Actually *(poolBasePtr + matrixHandleLow) = 0
    *(uint32_t*)( (uint8_t*)poolBasePtr + this->matrixHandleLow ) = 0;

    // Step 11: Read from source's sub-object (at source->field0x10 -> object + 0x1e) and store masked value
    uint32_t sourceSubObj = *(uint32_t*)( (uint8_t*)this->ownerOrType + 0x10 );
    // This reads a ushort from offset 0x1e of that sub-object, mask to 11 bits, store at this+0x0C
    this->field0x0C_Low = ( *(uint16_t*)( sourceSubObj + 0x1E ) ) & 0x7FF;

    // Step 12: Copy a ushort from source+0x08 to this+0x0E
    this->field0x0E = *(uint16_t*)( (uint8_t*)source + 0x08 );

    // Step 13: Set flags in the first matrix's control word (at poolBasePtr + matrixHandleLow)
    uint32_t* controlFlags = (uint32_t*)( (uint8_t*)poolBasePtr + this->matrixHandleLow );

    // Evaluate conditions from source's sub-object byte at +0x14 and sourceFlagsPtr
    uint8_t subObjByte = *(uint8_t*)( sourceSubObj + 0x14 );
    int8_t flagByte = (int8_t)(*sourceFlagsPtr); // low byte of sourceFlags

    if ( (subObjByte & 0x80) == 0 && flagByte >= 0 ) {
        // Check additional sub-conditions: (subObjByte & 1) != 0 OR (*sourceFlagsPtr & 1) != 0
        if ( (subObjByte & 1) != 0 || (*sourceFlagsPtr & 1) != 0 ) {
            *controlFlags |= 0x4; // set bit 2
        }
    } else {
        *controlFlags |= 0x40; // set bit 6
    }

    // Check bit 10 in source->field0x0C (offset +0x0C of ownerOrType?)
    if ( ( *(uint32_t*)( (uint8_t*)this->ownerOrType + 0x0C ) & 0x400 ) != 0 ) {
        *controlFlags |= 0x80; // set bit 7
    }

    // Check individual bits in *sourceFlagsPtr
    if ( *sourceFlagsPtr & 0x10 )   *controlFlags |= 0x8;   // bit 3
    if ( *sourceFlagsPtr & 0x20 )   *controlFlags |= 0x10;  // bit 4
    if ( *sourceFlagsPtr & 0x40 )   *controlFlags |= 0x20;  // bit 5
    if ( *sourceFlagsPtr & 0x80000 ) *controlFlags |= 0x80000; // bit 19
    if ( *sourceFlagsPtr & 0x2 )    *controlFlags |= 0x200; // bit 9

    // Step 14: Clear bit 20 in sourceFlags (0x00100000)
    *sourceFlagsPtr &= 0x7FEFFFFF;

    // Step 15: Post-initialization callback
    postSpatialInit(); // FUN_00533fb0

    return this;
}