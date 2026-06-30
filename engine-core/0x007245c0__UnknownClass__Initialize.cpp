// FUNC_NAME: UnknownClass::Initialize

void __thiscall UnknownClass::Initialize(int thisPtr, int param2)
{
    // Base class constructor call (FUN_0046c590) with param2
    FUN_0046c590(param2);
    
    // Global constant globals (likely read from data section)
    int global_0 = _DAT_00d5780c;
    int global_1 = DAT_00d58cbc;
    int global_2 = _DAT_00d5c458;
    int global_3 = DAT_00d5efd0;
    int global_4 = DAT_00d5eee4;
    
    // Set vtable pointer at +0x00
    *(int**)(thisPtr) = &PTR_FUN_00d62348;
    
    // Set function pointers at offsets +0x3C (0xF*4) and +0x48 (0x12*4)
    *(int*)(thisPtr + 0x3C) = &PTR_LAB_00d62338;
    *(int*)(thisPtr + 0x48) = &PTR_LAB_00d62334;
    
    // Clear pointer at +0x50 (0x14*4) and byte at +0x54 (offset 0x15*4? Actually param_1[0x15] is at 0x54)
    *(int*)(thisPtr + 0x50) = 0;
    *(unsigned char*)(thisPtr + 0x54) = 0;
    *(unsigned char*)(thisPtr + 0x55) = 0; // Byte at +0x55
    
    // Set integer fields from globals
    *(int*)(thisPtr + 0x58) = global_0;  // +0x16*4 = 0x58
    *(int*)(thisPtr + 0x5C) = global_0;  // +0x17*4 = 0x5C
    *(int*)(thisPtr + 0x64) = global_0;  // +0x19*4 = 0x64
    *(int*)(thisPtr + 0x74) = global_0;  // +0x1D*4 = 0x74
    *(int*)(thisPtr + 0x68) = global_1;  // +0x1A*4 = 0x68
    *(int*)(thisPtr + 0x78) = global_2;  // +0x1E*4 = 0x78
    *(int*)(thisPtr + 0x7C) = global_2;  // +0x1F*4 = 0x7C
    *(int*)(thisPtr + 0x80) = global_2;  // +0x20*4 = 0x80
    *(int*)(thisPtr + 0xB4) = global_2;  // +0x2D*4 = 0xB4
    *(int*)(thisPtr + 0xB8) = global_2;  // +0x2E*4 = 0xB8
    *(int*)(thisPtr + 0xBC) = global_4;  // +0x2F*4 = 0xBC
    *(int*)(thisPtr + 0xC0) = global_4;  // +0x30*4 = 0xC0
    
    // Set byte flag at +0x84 (0x21*4)
    *(unsigned char*)(thisPtr + 0x84) = 1;
    
    // Set integer fields to constant 1 (likely bools)
    *(int*)(thisPtr + 0x8C) = 1;  // +0x23*4 = 0x8C
    *(int*)(thisPtr + 0x94) = 1;  // +0x25*4 = 0x94
    *(int*)(thisPtr + 0x98) = 1;  // +0x26*4 = 0x98
    *(int*)(thisPtr + 0xA0) = 1;  // +0x28*4 = 0xA0
    *(int*)(thisPtr + 0xA8) = 1;  // +0x2A*4 = 0xA8
    *(int*)(thisPtr + 0xAC) = 1;  // +0x2B*4 = 0xAC
    
    // Set integer fields to constant 0 (likely off/empty)
    *(int*)(thisPtr + 0x6C) = 0;  // +0x1B*4 = 0x6C
    *(int*)(thisPtr + 0x88) = 0;  // +0x22*4 = 0x88
    *(int*)(thisPtr + 0x9C) = 0;  // +0x27*4 = 0x9C
    *(int*)(thisPtr + 0xB0) = 0;  // +0x2C*4 = 0xB0
    
    // Set integer fields to specific constants
    *(int*)(thisPtr + 0x60) = 2000;  // +0x18*4 = 0x60
    *(int*)(thisPtr + 0x70) = global_3; // +0x1C*4 = 0x70
    *(int*)(thisPtr + 0x90) = 10;   // +0x24*4 = 0x90
    *(int*)(thisPtr + 0xA4) = 10;   // +0x29*4 = 0xA4
    
    return;
}