// FUNC_NAME: GeometryGenerator::generateVertexBatch
// Function address: 0x00589450
// Role: Generates a batch of vertices using a random pattern from index arrays.
// The object has a current index (m_curIdx at +0x1C), and two arrays of ushort indices (m_indicesA at +0x10, m_indicesB at +0x14).
// The output vertices are stored in an array of 16-byte structures pointed by param_1 (vertexBuffer).
// The constants DAT_00e44564 (likely 1.0f) and DAT_00e44820 (scale factor) are used to compute positions.
// The random number generator is derived from __aullshr (64-bit shift of global state).

void __thiscall GeometryGenerator::generateVertexBatch(void* thisObj, void* vertexBuffer, int startIdx, int endIdx)
{
    uint uVar1;
    int iVar2;
    float fVar3, fVar4;

    // Access members via thisObj (assuming offsets)
    int* m_curIdx = (int*)((char*)thisObj + 0x1C);
    unsigned short** m_indicesA = (unsigned short**)((char*)thisObj + 0x10);
    unsigned short** m_indicesB = (unsigned short**)((char*)thisObj + 0x14);

    // First loop: advance current index to startIdx by skipping some indices
    while (*m_curIdx < startIdx) {
        iVar2 = *m_curIdx;  // current index
        // Generate random number from __aullshr (likely part of PRNG)
        uVar1 = __aullshr();  // returns uint, low bits of 64-bit shift
        if ((uVar1 & 3) - 1 < 3) {  // if (uVar1 & 3) != 0
            // case 1,2,3: skip 2 shorts in m_indicesA
            *m_indicesA += 2;
        } else {
            // case 0: skip 6 shorts in m_indicesA
            *m_indicesA += 6;
        }
        // Always skip 6 shorts in m_indicesB
        *m_indicesB += 6;
        (*m_curIdx)++;
    }

    // Second loop: process from current index to endIdx
    iVar2 = *m_curIdx;
    while (true) {
        if (iVar2 >= endIdx) {
            return;
        }
        // Generate random number
        uVar1 = __aullshr();
        uVar1 = uVar1 & 3;  // pick 2-bit random value (0-3)

        if (uVar1 == 1) {
            // case 1: use m_indicesA[0], m_indicesB[1]
            fVar3 = DAT_00e44564 - (float)**m_indicesA * DAT_00e44820;
            fVar4 = DAT_00e44564 - (float)(*m_indicesB)[1] * DAT_00e44820;
            goto LAB_005895f7;
        }
        else if (uVar1 == 2) {
            // case 2: use m_indicesB[0], m_indicesA[0]
            fVar3 = DAT_00e44564 - (float)**m_indicesB * DAT_00e44820;
            fVar4 = DAT_00e44564 - (float)**m_indicesA * DAT_00e44820;
            goto LAB_005895f7;
        }
        else if (uVar1 == 3) {
            // case 3: use m_indicesB[0], m_indicesB[2]
            fVar3 = DAT_00e44564 - (float)**m_indicesB * DAT_00e44820;
            fVar4 = DAT_00e44564 - (float)((*m_indicesB)[2]) * DAT_00e44820;
            goto LAB_005895f7;
        }
        else {
            // case 0: use m_indicesA[2], m_indicesA[0]
            fVar3 = DAT_00e44564 - (float)((*m_indicesA)[2]) * DAT_00e44820;
            fVar4 = DAT_00e44564 - (float)**m_indicesA * DAT_00e44820;
            // no goto, fall through to call
        }

        // Call the vertex-setter function with (x, y, vertexBufferPtr)
        FUN_0056d040(fVar4, fVar3, vertexBuffer);
        // For case 0, also advance m_indicesA by 6
        *m_indicesA += 6;
        // For other cases, the call is at LAB_005895f7 and jump here
        goto LAB_005895f8;

LAB_005895f7:
        // Common call for cases 1,2,3
        FUN_0056d040(fVar4, fVar3, vertexBuffer);
        // Advance m_indicesA by 2 (for these cases)
        *m_indicesA += 2;

LAB_005895f8:
        // Common advancement for all cases
        *m_indicesB += 6;
        (*m_curIdx)++;
        vertexBuffer = (void*)((char*)vertexBuffer + 0x10);
        iVar2 = *m_curIdx;
    }
}