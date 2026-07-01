// FUNC_NAME: FamilyManager::FamilyManager

// Constructor at 0x00793270 for an object that manages 4 families.
// Initializes vtable pointers and an array of 7-int structures (magic + zero fill).
// param_2 is passed to base class constructor (FUN_0046c590).

#include <cstdint>

// Forward declarations (vtable symbols from the binary)
extern void* PTR_FUN_00d69e04;
extern void* PTR_LAB_00d69df4;
extern void* PTR_LAB_00d69df0;

void __thiscall FUN_0046c590(int param_2); // Base class constructor

class FamilyManager {
public:
    // Vtable pointer at offset 0x00
    void* vtable;
    
    // Additional vtable-like pointers at offsets 0x3C (0x0F*4) and 0x48 (0x12*4)
    void* secondVtable;
    void* thirdVtable;
    
    // Array of 4 family reputation entries, each 7 ints (28 bytes), starting at offset 0x50
    struct FamilyRepEntry {
        uint32_t sentinel1; // 0xBADBADBA
        uint32_t sentinel2; // 0xBEEFBEEF
        uint32_t sentinel3; // 0xEAC15A55
        uint32_t sentinel4; // 0x91100911
        uint32_t zero1;     // 0
        uint32_t zero2;     // 0
        uint32_t zero3;     // 0
    } repEntries[4]; // offsets 0x14, 0x1B, 0x22, 0x29 (in int indices)
    
    // Extra field at offset 0x30 (0xC0 bytes)
    uint32_t extraZero;

    FamilyManager(int param_2) {
        // Call base constructor
        FUN_0046c590(param_2);
        
        // Set vtable pointers (multiple inheritance)
        this->vtable = &PTR_FUN_00d69e04;
        this->secondVtable = &PTR_LAB_00d69df4;
        this->thirdVtable = &PTR_LAB_00d69df0;
        
        // Initialize each family entry with debug sentinels and zeros
        // Group 1 (index 0x14-0x1A)
        repEntries[0].sentinel1 = 0xBADBADBA;
        repEntries[0].sentinel2 = 0xBEEFBEEF;
        repEntries[0].sentinel3 = 0xEAC15A55;
        repEntries[0].sentinel4 = 0x91100911;
        repEntries[0].zero1 = 0;
        repEntries[0].zero2 = 0;
        repEntries[0].zero3 = 0;
        
        // Group 2 (index 0x1B-0x21)
        repEntries[1].sentinel1 = 0xBADBADBA;
        repEntries[1].sentinel2 = 0xBEEFBEEF;
        repEntries[1].sentinel3 = 0xEAC15A55;
        repEntries[1].sentinel4 = 0x91100911;
        repEntries[1].zero1 = 0;
        repEntries[1].zero2 = 0;
        repEntries[1].zero3 = 0;
        
        // Group 3 (index 0x22-0x28)
        repEntries[2].sentinel1 = 0xBADBADBA;
        repEntries[2].sentinel2 = 0xBEEFBEEF;
        repEntries[2].sentinel3 = 0xEAC15A55;
        repEntries[2].sentinel4 = 0x91100911;
        repEntries[2].zero1 = 0;
        repEntries[2].zero2 = 0;
        repEntries[2].zero3 = 0;
        
        // Group 4 (index 0x29-0x2F)
        repEntries[3].sentinel1 = 0xBADBADBA;
        repEntries[3].sentinel2 = 0xBEEFBEEF;
        repEntries[3].sentinel3 = 0xEAC15A55;
        repEntries[3].sentinel4 = 0x91100911;
        repEntries[3].zero1 = 0;
        repEntries[3].zero2 = 0;
        repEntries[3].zero3 = 0;
        
        // Additional zero at the end (offset 0x30)
        extraZero = 0;
    }
};