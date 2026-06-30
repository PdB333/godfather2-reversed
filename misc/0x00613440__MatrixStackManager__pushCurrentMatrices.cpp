// FUNC_NAME: MatrixStackManager::pushCurrentMatrices
// Function at 0x00613440: Pushes current transformation matrices onto one or more stacks based on a bitmask.
// Each stack holds up to 8 matrices (64 bytes each = 4x4 float matrix).
// Global data at 0x011f69b0..0x011f6a6c holds the current matrices for each stack.
// The bitmask selects which stacks to push:
//   bit0 (0x01) -> stack0 (modelview?)
//   bit1 (0x02) -> stack1 and stack2 (projection and texture?)
//   bit2 (0x04) -> stack3 (something else)

// Global state (offsets relative to 0x011f6000 base, but absolute addresses used)
// Stack0: count at 0x011f6bf0, data at 0x011f6c00 (8 * 64 bytes)
// Stack1: count at 0x011f7010, data at 0x011f7020
// Stack2: count at 0x011f6e00, data at 0x011f6e10
// Stack3: count at 0x011f7220, data at 0x011f7230

// Current matrices (each 16 floats = 64 bytes):
//   matrix0 at 0x011f69b0
//   matrix1 at 0x011f69f0
//   matrix2 at 0x011f6b30
//   matrix3 at 0x011f6a30

void MatrixStackManager::pushCurrentMatrices(byte bitmask)
{
    // Stack0 (bit0)
    if ((bitmask & 1) != 0) {
        if (g_stack0Count < 8) {
            int index = g_stack0Count * 0x40; // 64 bytes per entry
            // Copy matrix0 (4 rows of 4 floats)
            *(undefined4*)(&g_stack0Data[index + 0x00]) = g_currentMatrix0[0];
            *(undefined4*)(&g_stack0Data[index + 0x04]) = g_currentMatrix0[1];
            *(undefined4*)(&g_stack0Data[index + 0x08]) = g_currentMatrix0[2];
            *(undefined4*)(&g_stack0Data[index + 0x0C]) = g_currentMatrix0[3];
            *(undefined4*)(&g_stack0Data[index + 0x10]) = g_currentMatrix0[4];
            *(undefined4*)(&g_stack0Data[index + 0x14]) = g_currentMatrix0[5];
            *(undefined4*)(&g_stack0Data[index + 0x18]) = g_currentMatrix0[6];
            *(undefined4*)(&g_stack0Data[index + 0x1C]) = g_currentMatrix0[7];
            *(undefined4*)(&g_stack0Data[index + 0x20]) = g_currentMatrix0[8];
            *(undefined4*)(&g_stack0Data[index + 0x24]) = g_currentMatrix0[9];
            *(undefined4*)(&g_stack0Data[index + 0x28]) = g_currentMatrix0[10];
            *(undefined4*)(&g_stack0Data[index + 0x2C]) = g_currentMatrix0[11];
            *(undefined4*)(&g_stack0Data[index + 0x30]) = g_currentMatrix0[12];
            *(undefined4*)(&g_stack0Data[index + 0x34]) = g_currentMatrix0[13];
            *(undefined4*)(&g_stack0Data[index + 0x38]) = g_currentMatrix0[14];
            *(undefined4*)(&g_stack0Data[index + 0x3C]) = g_currentMatrix0[15];
            g_stack0Count++;
        }
    }

    // Stack1 and Stack2 (bit1)
    if ((bitmask & 2) != 0) {
        // Push matrix1 onto stack1
        if (g_stack1Count < 8) {
            int index = g_stack1Count * 0x40;
            *(undefined4*)(&g_stack1Data[index + 0x00]) = g_currentMatrix1[0];
            *(undefined4*)(&g_stack1Data[index + 0x04]) = g_currentMatrix1[1];
            *(undefined4*)(&g_stack1Data[index + 0x08]) = g_currentMatrix1[2];
            *(undefined4*)(&g_stack1Data[index + 0x0C]) = g_currentMatrix1[3];
            *(undefined4*)(&g_stack1Data[index + 0x10]) = g_currentMatrix1[4];
            *(undefined4*)(&g_stack1Data[index + 0x14]) = g_currentMatrix1[5];
            *(undefined4*)(&g_stack1Data[index + 0x18]) = g_currentMatrix1[6];
            *(undefined4*)(&g_stack1Data[index + 0x1C]) = g_currentMatrix1[7];
            *(undefined4*)(&g_stack1Data[index + 0x20]) = g_currentMatrix1[8];
            *(undefined4*)(&g_stack1Data[index + 0x24]) = g_currentMatrix1[9];
            *(undefined4*)(&g_stack1Data[index + 0x28]) = g_currentMatrix1[10];
            *(undefined4*)(&g_stack1Data[index + 0x2C]) = g_currentMatrix1[11];
            *(undefined4*)(&g_stack1Data[index + 0x30]) = g_currentMatrix1[12];
            *(undefined4*)(&g_stack1Data[index + 0x34]) = g_currentMatrix1[13];
            *(undefined4*)(&g_stack1Data[index + 0x38]) = g_currentMatrix1[14];
            *(undefined4*)(&g_stack1Data[index + 0x3C]) = g_currentMatrix1[15];
            g_stack1Count++;
        }

        // Push matrix2 onto stack2
        if (g_stack2Count < 8) {
            int index = g_stack2Count * 0x40;
            *(undefined4*)(&g_stack2Data[index + 0x00]) = g_currentMatrix2[0];
            *(undefined4*)(&g_stack2Data[index + 0x04]) = g_currentMatrix2[1];
            *(undefined4*)(&g_stack2Data[index + 0x08]) = g_currentMatrix2[2];
            *(undefined4*)(&g_stack2Data[index + 0x0C]) = g_currentMatrix2[3];
            *(undefined4*)(&g_stack2Data[index + 0x10]) = g_currentMatrix2[4];
            *(undefined4*)(&g_stack2Data[index + 0x14]) = g_currentMatrix2[5];
            *(undefined4*)(&g_stack2Data[index + 0x18]) = g_currentMatrix2[6];
            *(undefined4*)(&g_stack2Data[index + 0x1C]) = g_currentMatrix2[7];
            *(undefined4*)(&g_stack2Data[index + 0x20]) = g_currentMatrix2[8];
            *(undefined4*)(&g_stack2Data[index + 0x24]) = g_currentMatrix2[9];
            *(undefined4*)(&g_stack2Data[index + 0x28]) = g_currentMatrix2[10];
            *(undefined4*)(&g_stack2Data[index + 0x2C]) = g_currentMatrix2[11];
            *(undefined4*)(&g_stack2Data[index + 0x30]) = g_currentMatrix2[12];
            *(undefined4*)(&g_stack2Data[index + 0x34]) = g_currentMatrix2[13];
            *(undefined4*)(&g_stack2Data[index + 0x38]) = g_currentMatrix2[14];
            *(undefined4*)(&g_stack2Data[index + 0x3C]) = g_currentMatrix2[15];
            g_stack2Count++;
        }
    }

    // Stack3 (bit2)
    if ((bitmask & 4) != 0) {
        if (g_stack3Count < 8) {
            int index = g_stack3Count * 0x40;
            *(undefined4*)(&g_stack3Data[index + 0x00]) = g_currentMatrix3[0];
            *(undefined4*)(&g_stack3Data[index + 0x04]) = g_currentMatrix3[1];
            *(undefined4*)(&g_stack3Data[index + 0x08]) = g_currentMatrix3[2];
            *(undefined4*)(&g_stack3Data[index + 0x0C]) = g_currentMatrix3[3];
            *(undefined4*)(&g_stack3Data[index + 0x10]) = g_currentMatrix3[4];
            *(undefined4*)(&g_stack3Data[index + 0x14]) = g_currentMatrix3[5];
            *(undefined4*)(&g_stack3Data[index + 0x18]) = g_currentMatrix3[6];
            *(undefined4*)(&g_stack3Data[index + 0x1C]) = g_currentMatrix3[7];
            *(undefined4*)(&g_stack3Data[index + 0x20]) = g_currentMatrix3[8];
            *(undefined4*)(&g_stack3Data[index + 0x24]) = g_currentMatrix3[9];
            *(undefined4*)(&g_stack3Data[index + 0x28]) = g_currentMatrix3[10];
            *(undefined4*)(&g_stack3Data[index + 0x2C]) = g_currentMatrix3[11];
            *(undefined4*)(&g_stack3Data[index + 0x30]) = g_currentMatrix3[12];
            *(undefined4*)(&g_stack3Data[index + 0x34]) = g_currentMatrix3[13];
            *(undefined4*)(&g_stack3Data[index + 0x38]) = g_currentMatrix3[14];
            *(undefined4*)(&g_stack3Data[index + 0x3C]) = g_currentMatrix3[15];
            g_stack3Count++;
        }
    }
}