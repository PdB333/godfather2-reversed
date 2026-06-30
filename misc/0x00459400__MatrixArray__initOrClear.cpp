// FUNC_NAME: MatrixArray::initOrClear

// Global constant used as matrix diagonal value (likely 1.0f as identity)
extern unsigned int g_matrixIdentityDiagonal = 0x00e2b1a4;

void __thiscall MatrixArray::initOrClear(int count, int flag, void* basePtr)
{
    unsigned int diagonal = g_matrixIdentityDiagonal;
    
    if (flag == 0) {
        // Initialize 'count' 4x4 matrices to identity (diagonal = diagonal, rest zero)
        // Each matrix is 16 floats (64 bytes)
        if (count != 0) {
            unsigned int* pWrite = (unsigned int*)((char*)basePtr + 0x20);
            do {
                // Write diagonal elements at offsets 0, 20, 40, 60 (bytes) within the 64-byte block
                pWrite[-8] = diagonal;  // (0,0) – offset 0
                pWrite[-7] = 0;          // (0,1) – offset 4
                pWrite[-6] = 0;          // (0,2) – offset 8
                pWrite[-5] = 0;          // (0,3) – offset 12
                pWrite[-4] = 0;          // (1,0) – offset 16
                pWrite[-3] = diagonal;  // (1,1) – offset 20
                pWrite[-2] = 0;          // (1,2) – offset 24
                pWrite[-1] = 0;          // (1,3) – offset 28
                pWrite[0] = 0;           // (2,0) – offset 32
                pWrite[1] = 0;           // (2,1) – offset 36
                pWrite[2] = diagonal;   // (2,2) – offset 40
                pWrite[3] = 0;           // (2,3) – offset 44
                pWrite[4] = 0;           // (3,0) – offset 48
                pWrite[5] = 0;           // (3,1) – offset 52
                pWrite[6] = 0;           // (3,2) – offset 56
                pWrite[7] = diagonal;   // (3,3) – offset 60
                pWrite += 0x10;          // advance to next matrix (64 bytes)
                count--;
            } while (count != 0);
        }
    } else {
        // Clear/deinitialize 'count' matrices (call per-matrix handler)
        int remaining = count - 1;
        if (remaining >= 0) {
            do {
                sub_00417560();  // per-matrix cleanup function
                remaining--;
            } while (remaining >= 0);
        }
    }
}