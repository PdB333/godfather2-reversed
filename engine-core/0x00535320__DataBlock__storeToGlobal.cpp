// FUNC_NAME: DataBlock::storeToGlobal

// Reconstructed from 0x00535320 - stores a 16-int data block to global and updates registered handlers

// Global data (extern definitions for clarity)
extern int g_dataBlock[16];              // +0x01219b90 : copied data buffer
extern char g_flag;                      // +0x01219b38 : activation flag
extern int* g_currentIndex1;             // +0x01219b20 : index for first set of handlers
extern int* g_currentIndex2;             // +0x01219b21 : index for second set of handlers
extern char g_anotherFlag;               // +0x01163840 : secondary flag for label selection

extern int* g_somePointer;               // +0x012058e8 : context pointer
extern int* g_expectedPointer;           // +0x01219a70 : expected singleton address

extern int g_manager1;                   // +0x01219a80 : first manager handle
extern int g_manager2;                   // +0x01219a84 : second manager handle

// Arrays of pointers (each entry size 0x30 or 0x3c)
extern void* g_array1;                   // +0x01219cc4 : stride 0x30
extern void* g_array2;                   // +0x01219cd8 : stride 0x30
extern void* g_array3;                   // +0x01219d70 : stride 0x3c
extern void* g_array4;                   // +0x01219d74 : stride 0x3c

// Label strings
extern char g_label1;                    // +0x011280d0
extern char g_label2;                    // +0x00e2e770
extern char g_label3;                    // +0x01163810
extern char g_label4;                    // +0x00e2e760
extern char g_label5;                    // +0x011637d0
extern char g_label6;                    // +0x00e2e720

// External helper functions (EA EARS engine)
void registerWithPointer(int manager, int* handler, int* dataBlock);   // FUN_0060b020
void registerWithString(int manager, int* handler, char* label);       // FUN_0060add0

void __thiscall DataBlock::storeToGlobal(int* thisDataBlock, char flag)
{
    char* labelPtr;

    // Copy 16 integers from the caller's data block to the global buffer
    g_dataBlock[0] = thisDataBlock[0];
    g_dataBlock[1] = thisDataBlock[1];
    g_dataBlock[2] = thisDataBlock[2];
    g_dataBlock[3] = thisDataBlock[3];
    g_dataBlock[4] = thisDataBlock[4];
    g_dataBlock[5] = thisDataBlock[5];
    g_dataBlock[6] = thisDataBlock[6];
    g_dataBlock[7] = thisDataBlock[7];
    g_dataBlock[8] = thisDataBlock[8];
    g_dataBlock[9] = thisDataBlock[9];
    g_dataBlock[10] = thisDataBlock[10];
    g_dataBlock[11] = thisDataBlock[11];
    g_dataBlock[12] = thisDataBlock[12];
    g_dataBlock[13] = thisDataBlock[13];
    g_dataBlock[14] = thisDataBlock[14];
    g_dataBlock[15] = thisDataBlock[15];

    // Store the activation flag
    g_flag = flag;

    // Only update handlers if we are in the expected context (singleton check)
    if (g_somePointer != &g_expectedPointer)
        return;

    // --- First set of handlers (indexed by g_currentIndex1, stride 0x30) ---
    {
        int* handler1 = *(int**)((char*)g_array1 + (int)g_currentIndex1 * 0x30);
        if (handler1 != 0)
            registerWithPointer(g_manager1, handler1, thisDataBlock);

        int* handler2 = *(int**)((char*)g_array2 + (int)g_currentIndex1 * 0x30);
        if (handler2 != 0)
        {
            labelPtr = &g_label1;
            if (flag == 0)
                labelPtr = &g_label2;
            registerWithString(g_manager1, handler2, labelPtr);
        }
    }

    // --- Second set of handlers (indexed by g_currentIndex2, stride 0x3c) ---
    {
        int* handler3 = *(int**)((char*)g_array3 + (int)g_currentIndex2 * 0x3c);
        if (handler3 != 0)
        {
            labelPtr = &g_label3;
            if (g_anotherFlag == 0)
                labelPtr = &g_label4;
            registerWithString(g_manager2, handler3, labelPtr);
        }

        int* handler4 = *(int**)((char*)g_array4 + (int)g_currentIndex2 * 0x3c);
        if (handler4 != 0)
        {
            // This call uses the data block pointer, not a label
            registerWithPointer(g_manager2, handler4, thisDataBlock);
        }
    }
}