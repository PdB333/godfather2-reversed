// FUNC_NAME: SlotArrayManager::SlotArrayManager
class SlotArrayManager {
public:
    void **vtable; // +0x00
    int field_4;   // +0x04 initialized to 1
    int field_8;   // +0x08 initialized to 0
    
    struct SlotPair {
        int first;  // +0x0C each pair
        int second; // +0x10
    };
    
    SlotPair firstSlots[500]; // +0x0C, 500 pairs (1000 ints)
    int firstExtra;           // +0xFAC (param_1[0x3EB])
    SlotPair secondSlots[500]; // +0xFB0, 500 pairs (1000 ints)
    int secondExtra;          // +0x1F50 (param_1[0x7D4])
    
    // __fastcall with this in ECX
    SlotArrayManager() {
        vtable = &PTR_FUN_00d7c2e8; // vtable pointer
        field_4 = 1;
        field_8 = 0;
        
        // Initialize firstSlots to zero
        SlotPair *p = firstSlots;
        int count = 500;
        do {
            p->first = 0;
            p->second = 0;
            p++;
            count--;
        } while (count >= 0);
        
        firstExtra = 0;
        
        // Initialize secondSlots to zero
        p = secondSlots;
        count = 500;
        do {
            p->first = 0;
            p->second = 0;
            p++;
            count--;
        } while (count >= 0);
        
        secondExtra = 0;
        
        // External initialization call (likely global manager init)
        FUN_004086b0(&DAT_012069d4, 0);
    }
};