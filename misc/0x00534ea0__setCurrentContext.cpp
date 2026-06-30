// FUNC_NAME: setCurrentContext
// Address: 0x00534ea0
// Role: Sets the current context pointer and triggers processing if both pointers in the current context slot are valid

// Global data (hypothetical names)
extern int* gCurrentContext;                    // DAT_01219b30
extern uint8 gCurrentSlotIndex;                 // DAT_01219b21, index into context array
extern char gContextArray[];                    // DAT_01219d44, array of ContextSlot (0x3C bytes each)

// Structure definition for a context slot (size 0x3C)
struct ContextSlot {
    int* ptr0;      // +0x00
    // padding? offset 0x0C is next field
    int* ptrC;      // +0x0C
    // remaining 0x30 bytes unknown
};

// Forward declaration of the processing function
extern void FUN_006063b0(void); // Called when both pointers are non-null

void setCurrentContext(int* context)
{
    gCurrentContext = context;

    // Access the context slot at current index
    ContextSlot* slot = (ContextSlot*)(gContextArray + (uint32)gCurrentSlotIndex * 0x3C);
    if (slot->ptr0 != 0 && slot->ptrC != 0) {
        FUN_006063b0();
    }
}