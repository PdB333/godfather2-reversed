// FUN_004a9400: AnimationCompressor::compressTransform
// Compresses a bone transform (rotation + translation) into a compact bitstream.
// param_2: pointer to structure containing rotation matrix (9 floats) and translation (3 floats),
//          possibly as: rotation rows (3x4, each row 4 floats with padding), then translation XYZ,
//          then additional data at offsets 6,8,9,10,12,13,14.
// Uses: QT to extract quaternion, then encodes signs and magnitudes of 4 quaternion components,
//       followed by encoding of 3 translation components.

#include <cstdlib>
#include <cmath>

// Forward declarations
namespace AnimCompress {
    struct Compressor;
}

// Bitstream write function (likely adaptive arithmetic or simple bitpack)
void bitPackEncodedValue(uint32 contextID, int* pValue);

// Matrix to quaternion conversion (takes 3x3 rotation matrix, returns normalized quaternion)
// Actually takes 6 floats? We'll assume it's a 3x3 matrix stored in 6 floats? Not exact.
void matrix3x3ToQuaternion(const float* mat, float* quat);

struct AnimCompress::Compressor {
    // +0x00: likely vtable? skip.
    // +0x04: (unknown)
    // +0x08: (unknown)
    // +0x0C: m_pBitBuffer          (byte*)
    // +0x10: m_allocatedSize       (uint)
    // +0x14: m_ownsBuffer          (bool)
    // +0x18: m_bitPosition         (int)
    // +0x1C: m_needRealloc         (byte)
    // +0x20-0x28: padding
    // +0x2C: m_bitCapacity         (uint)
    // +0x30: m_bitCapacity2        (uint)  (duplicated)
};

void __thiscall Compressor::compressTransform(AnimCompress::Compressor* this, const float* frameData)
{
    const float epsilon = DAT_00e2cbe0;   // ~0.0
    const float scaleInv = DAT_00e2b1a4;  // likely 1.0 (inverse of scale for normalization)
    
    // Copy rotation matrix (3x4 with stride 4? store 3 rows of 4 floats)
    float row0[3] = { frameData[0], frameData[1], frameData[2] };
    float row1[3] = { frameData[4], frameData[5], frameData[6]? wait indexing: local_50[4]=param_2[4], [5]=param_2[5], local_38=param_2[6]; so rows are at offsets 0,1,2; 4,5; and row2 from local_38,local_30,local_2c? Actually row2 is: local_38 (param_2[6]), local_30 (param_2[8]), local_2c (param_2[9]). Then there is local_28 (param_2[10]) but not used? Hmm.
    // Let's reconstruct: from code: local_50[0] = param_2[0], [1]=[1], [2]=[2], [4]=[4], [5]=[5]; local_38 = param_2[6]; local_30 = [8]; local_2c = [9]; local_28 = [10]; local_20 = [12]; fStack_1c = [13]; fStack_18 = [14]; local_50[3]=0; local_34=0; local_24=0; fStack_14 = constant.
    // So row2 is composed of [6], [8], [9]? Not contiguous. That's weird. Actually it's: row0: 0,1,2; row1: 4,5,? but no 6? That's not a matrix.
    // Possibly param_2 is a struct: { float rot[3][4]; float trans[3]; float extra; ... } but offset 6 is skipped? No, param_2[6] is used as local_38, which is the first component of row2? Then [8] and [9] are next two. So row2 is stored with a gap at index 7? Or maybe param_2[7] is implied? Not there.
    // Given the normalizing loop: it normalizes three vectors each of 3 components with stride 4. So source data has 3 vectors: v0 = param_2[0..2]; v1 = param_2[4..6]? Actually stride 4: v0 at indices 0,1,2; v1 at 4,5,6; v2 at 8,9,10. But we see v0 uses [0],[1],[2]; v1 uses [4],[5] but then local_38 which is [6]? That suggests v1 = [4],[5],[6]. v2 = [8],[9],[10]. local_50[2] is *pfVar1, which is row0[2]? Actually after normalization, local_50[0..2] are normalized row0. Then pfVar1 = local_50+2 (so points to row0[2]), then next iteration it processes row1: pfVar1[-2] is row1[0], pfVar1[-1] is row1[1], *pfVar1 is row1[2]. So row1 is stored at local_50[4]? But local_50 is 6 floats? Actually local_50 is declared as float[6], indices 0..5. So row1 occupies indices 4,5,6? But index 6 would be out of bounds. However local_38 is separate, not part of local_50. So the loop uses pfVar1 which starts at &local_50[2]; first iteration: pfVar1[-2] = local_50[0]; pfVar1[-1] = local_50[1]; *pfVar1 = local_50[2]; then pfVar1 += 4 -> now points to local_50[6]? That's beyond array. So there's buffer overflow? Actually local_50 is declared as local_50 [6], so indices 0..5. Adding 4 to pointer goes to &local_50[6] which is within the stack but beyond declared array. The compiler may have allocated extra space. In the decompiled code, there are also other variables like local_38, local_30, etc. that may be adjacent. So likely the actual stack layout has space for 12 or more floats. We'll assume the rotation matrix is stored in a 3x4 layout (each row 4 floats) and the rows are at offsets 0,4,8 in param_2. So row0: [0,1,2,3? but index3 is 0]; row1: [4,5,6,7? but index7 is 0]; row2: [8,9,10,11? but index11 is 0]. local_50 then copies the first three rows? However local_50 is only 6 floats, so maybe it only uses first two rows? Confusing.

Given the complexity, we will keep the logic but use a simplified view: we have three vectors (rows of a rotation matrix) stored with stride 4 in memory starting from frameData. We'll assume there is a function that converts this to a quaternion.

We'll write:
    float rotMat[3][4]; // but only first 3 components of each row used
    // Copy rows from frameData
    for (int i=0; i<3; i++) {
        rotMat[i][0] = frameData[i*4];
        rotMat[i][1] = frameData[i*4+1];
        rotMat[i][2] = frameData[i*4+2];
        rotMat[i][3] = 0.0f; // zero
    }
    // But frameData indices: 0,1,2; then 4,5,6; then 8,9,10. So we must adjust.

We'll adapt: The actual code uses: row0: indices 0,1,2; row1: indices 4,5,? (missing index 6? Actually it uses local_38 from index 6, but that's separate). The loop uses pfVar1[-2],[-1],*pfVar1. Starting at &local_50[2], it first normalizes local_50[0..2] (row0), then after pfVar1+=4, it normalizes local_50[4..6] but local_50[6] is out of declared array. In the decompiler, local_50 is declared as [6], but later there is local_38 at a separate address. So the memory layout is: local_50[0..5], then local_38, local_34, local_30, local_2c, ... So local_50[6] overlaps local_38? Actually local_38 is declared as separate float, so it occupies the space after local_50. So the second iteration reads (local_50[4], local_50[5], local_38). So row1 is (frameData[4], frameData[5], frameData[6]). Third iteration: after second iteration, pfVar1 becomes &local_50[8]? Actually after two increments of 4, pfVar1 started at &local_50[2], first increment goes to &local_50[6] (which is &local_38), then second increment goes to &local_50[10]? That would be beyond local_38 into local_30 etc. The loop runs 3 times: first iteration uses local_50[0,1,2]; second uses local_50[4,5] and local_38; third uses local_30, local_2c, local_28? Because after second, pfVar1 = &local_50[10]? But the third iteration uses pfVar1[-2] which would be &local_50[8] = &local_30, pfVar1[-1]=&local_2c, *pfVar1=&local_28. So indeed the three vectors are: v0 = (local_50[0],1,2); v1 = (local_50[4],5,local_38); v2 = (local_30,2c,28). That matches the copy from frameData: frameData[0,1,2], frameData[4,5,6], frameData[8,9,10] (since local_30=param_2[8], 2c=[9], 28=[10]). So the rotation matrix is stored contiguously at offsets 0,4,8 but with a gap? Actually it's not contiguous: indices 0,1,2; then 4,5,6; then 8,9,10. So row size is 4? Yes, 0-3 (but index3 unused), 4-7 (6,7 unused? Actually 6 used, 7? not), 8-11 (10 used). So indeed a 3x4 matrix in memory.

Thus we'll copy:
    float rot[3][4];
    rot[0][0] = frameData[0]; rot[0][1]=frameData[1]; rot[0][2]=frameData[2]; rot[0][3]=0;
    rot[1][0] = frameData[4]; rot[1][1]=frameData[5]; rot[1][2]=frameData[6]; rot[1][3]=0;
    rot[2][0] = frameData[8]; rot[2][1]=frameData[9]; rot[2][2]=frameData[10]; rot[2][3]=0;

But wait, frameData[6] is used for row1 third component? Yes, local_38 = param_2[6] is row1[2]. So row1[2] = param_2[6]. And row2[2] = param_2[10]? Actually param_2[10] is local_28, which is third component of row2? In the third iteration, *pfVar1 = local_28 = param_2[10]. So row2[2] = param_2[10]. So row2 components: [0]=param_2[8], [1]=param_2[9], [2]=param_2[10]. So the matrix is at offsets: row0: 0,1,2; row1: 4,5,6; row2: 8,9,10. So we'll use that.

Then normalize each row (skip if zero length):
    for (int i=0; i<3; i++) {
        float lenSq = rot[i][0]*rot[i][0] + rot[i][1]*rot[i][1] + rot[i][2]*rot[i][2];
        if (lenSq > epsilon) {
            float invLen = scaleInv / sqrt(lenSq);
            rot[i][0] *= invLen; rot[i][1] *= invLen; rot[i][2] *= invLen;
        }
    }

Then call matrix3x3ToQuaternion(rot, quat); // quat is float[4]
    float quat[4];
    matrix3x3ToQuaternion((float*)rot, quat); // assuming it takes the first 3 columns? But rot is 3x4, it will read row-major 12 floats. The function likely expects a 3x3 matrix (9 floats) with stride 4? We'll assume it ignores the fourth column.

Then normalize quaternion:
    float qLenSq = quat[0]*quat[0] + quat[1]*quat[1] + quat[2]*quat[2] + quat[3]*quat[3];
    if (qLenSq > epsilon) {
        float invLen = scaleInv / sqrt(qLenSq);
        quat[0]*=invLen; quat[1]*=invLen; quat[2]*=invLen; quat[3]*=invLen;
    }

Now encode quaternion signs and magnitudes:
    for (int i=0; i<4; i++) {
        int intVal = (int)(quat[i] * DAT_00e4489c); // scale factor
        writeBitSignAndEncode(this, intVal, 0xf);
    }

Then encode translation:
    float trans[3] = { frameData[12], frameData[13], frameData[14] };
    for (int i=0; i<3; i++) {
        int intVal = (int)(trans[i] * DAT_0110ae44 + DAT_00e2cd54);
        writeBitSignAndEncode(this, intVal, 0x13);
    }
}

// Helper function to write sign bit and then encode magnitude
void __fastcall writeBitSignAndEncode(AnimCompress::Compressor* this, int value, uint contextID)
{
    // Ensure bit buffer has space
    if (this->m_bitPosition + 1 > this->m_bitCapacity) {
        uint newByteSize = ((this->m_bitCapacity + 8) >> 3) + 0x5dc;
        if (this->m_allocatedSize < newByteSize) {
            if (this->m_ownsBuffer) {
                this->m_allocatedSize = newByteSize;
                this->m_pBitBuffer = realloc(this->m_pBitBuffer, newByteSize);
                // Update capacity
                this->m_byteCapacity = newByteSize;
                this->m_bitCapacity = newByteSize * 8;
            }
        } else {
            this->m_allocatedSize = newByteSize;
        }
        this->m_needRealloc = 1;
    }
    
    // Write sign bit
    byte* pByte = (byte*)this->m_pBitBuffer + (this->m_bitPosition >> 3);
    byte mask = 1 << (this->m_bitPosition & 7);
    if (value >= 0) {
        *pByte &= ~mask;
    } else {
        *pByte |= mask;
    }
    this->m_bitPosition++;
    
    // Now encode absolute (or signed) value
    int absVal = (value >= 0) ? value : -value;
    bitPackEncodedValue(contextID, &absVal);
}