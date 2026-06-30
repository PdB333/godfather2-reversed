// FUN_0041f620: CharacterRenderer::setSubTransformMatrix

#include <cstdint>

// Forward declarations of external functions
extern void FUN_00422a40(uint, uint, int, int);
extern void FUN_00423410();
extern void FUN_00420820(int);
extern void FUN_0041e660(float, float);
extern void FUN_0041f4b0(int, float *, float *, int);
extern void FUN_00414c90(float *, int);
extern uint FUN_00609260();
extern void FUN_00609340(int, uint, uint);
extern void FUN_0060db60(int, int, int, float, float);
extern void FUN_00609730(float, float, float, int, float, int);
extern void FUN_00609810(int);
extern void FUN_00609890(int);

// External globals (addresses from Ghidra)
extern float _DAT_011f6b70;      // 0x011f6b70 - source matrix row0
extern float _DAT_011f6b80;      // etc.
extern float _DAT_011f6b90;
extern float _DAT_011f6ba0;
extern float _DAT_011f6b74;
extern float _DAT_011f6b78;
extern float _DAT_011f6b7c;
extern float _DAT_011f6b84;
extern float _DAT_011f6b88;
extern float _DAT_011f6b8c;
extern float _DAT_011f6b94;
extern float _DAT_011f6b98;
extern float _DAT_011f6b9c;
extern float _DAT_011f6ba4;
extern float _DAT_011f6ba8;
extern float _DAT_011f6bac;
extern float _DAT_011f6a30;       // 0x011f6a30 - another matrix?
extern float DAT_00e2b1a4;        // 0x00e2b1a4 - default scale?
extern float DAT_00e2b04c;        // 0x00e2b04c
extern float DAT_00e44578;        // 0x00e44578 - large float for rounding
extern int DAT_012233b0;          // 0x012233b0 - pointer to some structure
extern int DAT_01206880;          // 0x01206880 - pointer to vtable?
extern int DAT_01205750;          // 0x01205750 - pointer to something
extern int DAT_0110aae7;          // 0x0110aae7 - flag (0 or 1)
extern int DAT_0110acc8;          // 0x0110acc8 - flag
extern int DAT_011f38f0;          // 0x011f38f0
extern int DAT_011f38f4;          // 0x011f38f4
extern int DAT_011f3910;          // 0x011f3910
extern int DAT_011f3914;          // 0x011f3914
extern int DAT_01163ccc;          // 0x01163ccc - some computed value
extern int DAT_01223538;          // 0x01223538 - flag
extern int DAT_01163650;          // base address of matrix array
extern int DAT_01163710;          // base address of transform node array (?) 
extern int DAT_01163820;          // base address of some int array
extern int DAT_01163834;          // base address of some int array (first field of struct?)
extern int DAT_01163840;          // base address of byte array (flags)
extern int DAT_01163848;          // base address of int array
extern int DAT_0110ac80;          // array of floats indexed by partIndex
extern int DAT_0110ac98;          // array of floats
extern int DAT_0110acb0;          // array of floats

// Constants for struct sizes
const int kObjectStructSize = 0x84;   // size of per-object data
const int kSubObjectCount = 4;        // each object has 4 sub-objects? (0x210/0x84)
const int kMatrixStride = 0x40;       // 16 floats = 0x40 bytes per matrix

// Matrix structure (column-major? actually row-major as stored)
struct Matrix4 {
    float m[4][4];
};

// Reconstructed function
int CharacterRenderer::setSubTransformMatrix(int objectIndex, int partIndex)
{
    int objectOffset = objectIndex * (kObjectStructSize * kSubObjectCount); // 0x210 per object
    uint firstField = *((uint *)(DAT_01163834 + objectIndex * kObjectStructSize)); // first field of struct
    uint someOther = *((uint *)(DAT_01163820 + objectIndex * kObjectStructSize + partIndex * 4)); // some per-part data

    if (DAT_0110aae7 == 0) {
        someOther = 0;
    }

    FUN_00422a40(someOther, *((uint *)(DAT_01163834 + objectIndex * kObjectStructSize)), 0, 0);

    float defaultScale = DAT_00e2b1a4;
    int* structurePtr = *(int**)(DAT_012233b0 + 0x30 + objectIndex * 4); // +0x30 offset per object
    float* destMatrix = (float*)(DAT_01163650 + objectOffset + partIndex * kMatrixStride);

    char flag = *(char*)(DAT_01163840 + objectIndex * kObjectStructSize); // byte flag from object

    if ((*(char*)(DAT_0116382c + objectOffset + partIndex) != 0) && (structurePtr != nullptr)) {
        // ---------------- Branch: matrix is valid ----------------
        int* threadContext = **(int***)(__readfsdword(0x2c)); // FS register offset
        *(uint*)(threadContext + 0x24) = firstField;
        if (*(int*)(threadContext + 0x34) == 0) {
            int* vtablePtr = (int*)(DAT_01206880 + 0x14); // vtable pointer location
            **(uint***)vtablePtr = &PTR_0x0110b640; // set vtable
            *vtablePtr += 4;
            **(uint**)vtablePtr = firstField;
            *vtablePtr += 4;
        }

        FUN_00423410();
        FUN_00420820(partIndex);

        // Copy 4x4 source matrix from global memory
        float row0x = _DAT_011f6b70;
        float row0y = _DAT_011f6b74;
        float row0z = _DAT_011f6b78;
        float row0w = _DAT_011f6b7c;
        destMatrix[0] = row0x;
        destMatrix[1] = row0y;
        destMatrix[2] = row0z;
        destMatrix[3] = row0w;

        float row1x = _DAT_011f6b80;
        float row1y = _DAT_011f6b84;
        float row1z = _DAT_011f6b88;
        float row1w = _DAT_011f6b8c;
        destMatrix[4] = row1x;
        destMatrix[5] = row1y;
        destMatrix[6] = row1z;
        destMatrix[7] = row1w;

        float row2x = _DAT_011f6b90;
        float row2y = _DAT_011f6b94;
        float row2z = _DAT_011f6b98;
        float row2w = _DAT_011f6b9c;
        destMatrix[8] = row2x;
        destMatrix[9] = row2y;
        destMatrix[10] = row2z;
        destMatrix[11] = row2w;

        float row3x = _DAT_011f6ba0;
        float row3y = _DAT_011f6ba4;
        float row3z = _DAT_011f6ba8;
        float row3w = _DAT_011f6bac;
        destMatrix[12] = row3x;
        destMatrix[13] = row3y;
        destMatrix[14] = row3z;
        destMatrix[15] = row3w;

        char objectFlag = *(char*)(DAT_01163840 + objectIndex * kObjectStructSize);
        if ((objectFlag != 0) && (DAT_0110acc8 != 0)) {
            float fVar11 = (float)(int)(*((int*)(DAT_01163848 + objectIndex * kObjectStructSize)));
            if (fVar11 < 0.0f) {
                fVar11 += DAT_00e44578; // rounding correction
            }
            DAT_01163ccc = ((DAT_00e2b04c / -_DAT_011f6a30) / fVar11) *
                           *((float*)(DAT_0110ac80 + partIndex * 4));
        }

        // Get a scale factor from the structure
        float scale = *(float*)(*(int*)(threadContext + 8) + 0x8c + *(int*)(structurePtr + 0x18));
        if (scale <= 0.0f) {
            scale = DAT_00e2b1a4;
        }

        int index = partIndex + (uint)DAT_0110aae7 * 3;
        FUN_0041e660(*(float*)(DAT_0110ac98 + index * 4) * scale,
                     *(float*)(DAT_0110acb0 + index * 4) * scale);

        if (objectFlag != 0) {
            if (partIndex != 0) {
                FUN_0041f4b0(DAT_01163710 + objectOffset,
                             (float*)(DAT_01163650 + objectOffset),
                             destMatrix,
                             partIndex);
                return 1;
            }
            FUN_00414c90(&_DAT_011f6a30, DAT_01163710 + objectOffset);
        }
        return 1;
    }
    else {
        // ---------------- Branch: matrix is invalid, clear to default ----------------
        bool flag = (DAT_0110aae7 == 0);
        destMatrix[0] = DAT_00e2b1a4;
        destMatrix[1] = 0.0f;
        destMatrix[2] = 0.0f;
        destMatrix[3] = 0.0f;
        destMatrix[4] = 0.0f;
        destMatrix[5] = defaultScale;
        destMatrix[6] = 0.0f;
        destMatrix[7] = 0.0f;
        destMatrix[8] = 0.0f;
        destMatrix[9] = 0.0f;
        destMatrix[10] = defaultScale;
        destMatrix[11] = 0.0f;
        destMatrix[12] = 0.0f;
        destMatrix[13] = 0.0f;
        destMatrix[14] = 0.0f;
        destMatrix[15] = defaultScale;
        // Overwrite some entries with zeros (note: repeated assignments)
        destMatrix[10] = 0.0f;
        destMatrix[5] = 0.0f;
        destMatrix[0] = 0.0f;

        int* ptr = DAT_01205750;
        int var1 = DAT_011f38f4;
        int var2 = DAT_011f38f0;

        if (flag) {
            bool bVar10 = (DAT_011f38f0 != 0);
            DAT_011f38f0 = 0;
            DAT_011f38f4 = 0;
            if (bVar10 || (var1 != 0)) {
                int val = *DAT_01205750;
                uint uVar = FUN_00609260();
                (*(void (**)(void*, int, uint))(val + 0x94))(ptr, 0, uVar);
                DAT_01223538 = 1;
            }
        }
        else {
            DAT_011f38f0 = *((uint*)(DAT_01163834 + objectIndex * kObjectStructSize));
            DAT_011f38f4 = 0;
            FUN_00609340(0, var2, var1);
        }

        uint uVar8 = DAT_011f3914;
        uint uVar12 = DAT_011f3910;
        DAT_011f3910 = *((uint*)(DAT_01163834 + objectIndex * kObjectStructSize));
        DAT_011f3914 = 0;
        FUN_00609340(4, uVar12, uVar8);
        FUN_0060db60(4, 0, 0, 1.0f, 1.0f); // Set color? (1.0f,1.0f)

        if (DAT_0110aae7 == 0) {
            FUN_00609730(0, 0, 0, 0, 1.0f, 0); // set color
            FUN_00609810(0x10); // set blend mode?
            FUN_00609890(2);   // set something
            return 0;
        }
        else {
            FUN_00609730(1.0f, 1.0f, 1.0f, 0, 1.0f, 0);
            FUN_00609810(0x11);
            FUN_00609730(0, 0, 0, 0, 1.0f, 0);
            FUN_00609890(3);
            return 0;
        }
    }
}