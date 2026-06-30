// FUNC_NAME: NetworkPacketWindow::NetPacketWindow

#include <cstdint>

// Forward declaration of base class constructor (unknown)
void __fastcall BaseClassConstructor(void* thisPtr);

class NetworkPacketWindow {
public:
    // Virtual function table at offset 0
    // Sentinels at offsets: +0x58, +0x5C, +0x60, +0x64, +0x68, +0x6C, +0x70, +0x74
    // Additional fields at +0x78 through +0x8C zeroed
    // +0x90: global data pointer (DAT_00d5d740)
    // +0x94: window size (0x21)
    
    void __fastcall constructor(void);
};

void __fastcall NetworkPacketWindow::constructor(void) {
    uint32_t* thisPtr = reinterpret_cast<uint32_t*>(this);
    
    // Base class constructor
    BaseClassConstructor(this);
    
    // Set virtual function table
    thisPtr[0] = reinterpret_cast<uint32_t>(&PTR_FUN_00d5f134);
    
    // Set secondary function table pointers (or something similar)
    thisPtr[0xf] = reinterpret_cast<uint32_t>(&PTR_LAB_00d5f124);  // +0x3C
    thisPtr[0x12] = reinterpret_cast<uint32_t>(&PTR_LAB_00d5f120); // +0x48
    thisPtr[0x14] = reinterpret_cast<uint32_t>(&PTR_LAB_00d5f11c); // +0x50
    
    // Set first group of sentinel values
    thisPtr[0x16] = 0xBADBADBA;  // +0x58
    thisPtr[0x19] = 0x91100911;  // +0x64
    thisPtr[0x17] = 0xBEEFBEEF;  // +0x5C
    thisPtr[0x18] = 0xEAC15A55;  // +0x60
    
    // Set second group of sentinel values (same pattern, different order?)
    thisPtr[0x1d] = 0x91100911;  // +0x74
    thisPtr[0x1a] = 0xBADBADBA;  // +0x68
    thisPtr[0x1b] = 0xBEEFBEEF;  // +0x6C
    thisPtr[0x1c] = 0xEAC15A55;  // +0x70
    
    // Zero out a block of fields
    thisPtr[0x1e] = 0;  // +0x78
    thisPtr[0x1f] = 0;  // +0x7C
    thisPtr[0x20] = 0;  // +0x80
    thisPtr[0x21] = 0;  // +0x84
    thisPtr[0x22] = 0;  // +0x88
    thisPtr[0x23] = 0;  // +0x8C
    
    // Set global data reference and window size
    thisPtr[0x24] = DAT_00d5d740;  // +0x90
    thisPtr[0x25] = 0x21;          // +0x94, window size = 33
}