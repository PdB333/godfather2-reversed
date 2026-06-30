// FUNC_NAME: ChaseCamera::Constructor

#include <cstring> // For memset

// Constructor for ChaseCamera class
// Base class constructor called at 0x0073e160
undefined4* __thiscall ChaseCamera::Constructor(ChaseCamera *this, undefined4 param2, undefined4 param3)
{
    // Call base class constructor (likely CameraBase or similar)
    FUN_0073e160(param2, param3);
    
    // Set vtable pointer (ChaseCamera vtable presumably at 0x00d645f0)
    *this = &PTR_LAB_00d645f0;
    
    // Initialize matrix/transform fields (offset 0x70 - 0xB0) to zero
    // This is a 4x4 float matrix or similar transformation data
    memset(reinterpret_cast<char*>(this) + 0x70, 0, 0x44); // 17 * 4 bytes = 68 bytes
    
    // Initialize remaining fields (offset 0xB4 - 0xE4) to zero
    // These appear to be 6 x 8-byte values and 1 byte (e.g., two sets of 4x3 matrices?)
    memset(reinterpret_cast<char*>(this) + 0xB4, 0, 0x31); // 6*8 + 1 = 49 bytes
    
    return this;
}