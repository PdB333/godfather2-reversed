// FUNC_NAME: setGlobalTransformMatrices
void __fastcall setGlobalTransformMatrices(uint* pSrcA, uint* pSrcB)
{
    // Copy 16 DWORDs (64 bytes) from pSrcA (ECX) to global buffer at 0x011f6b30
    *(uint*)0x011f6b30 = pSrcA[0];
    *(uint*)0x011f6b34 = pSrcA[1];
    *(uint*)0x011f6b38 = pSrcA[2];
    *(uint*)0x011f6b3c = pSrcA[3];
    *(uint*)0x011f6b40 = pSrcA[4];
    *(uint*)0x011f6b44 = pSrcA[5];
    *(uint*)0x011f6b48 = pSrcA[6];
    *(uint*)0x011f6b4c = pSrcA[7];
    *(uint*)0x011f6b50 = pSrcA[8];
    *(uint*)0x011f6b54 = pSrcA[9];
    *(uint*)0x011f6b58 = pSrcA[10];
    *(uint*)0x011f6b5c = pSrcA[11];
    *(uint*)0x011f6b60 = pSrcA[12];
    *(uint*)0x011f6b64 = pSrcA[13];
    *(uint*)0x011f6b68 = pSrcA[14];
    *(uint*)0x011f6b6c = pSrcA[15];

    // Copy 16 DWORDs from pSrcB (EDX) to global buffer at 0x011f69f0
    *(uint*)0x011f69f0 = pSrcB[0];
    *(uint*)0x011f69f4 = pSrcB[1];
    *(uint*)0x011f69f8 = pSrcB[2];
    *(uint*)0x011f69fc = pSrcB[3];
    *(uint*)0x011f6a00 = pSrcB[4];
    *(uint*)0x011f6a04 = pSrcB[5];
    *(uint*)0x011f6a08 = pSrcB[6];
    *(uint*)0x011f6a0c = pSrcB[7];
    *(uint*)0x011f6a10 = pSrcB[8];
    *(uint*)0x011f6a14 = pSrcB[9];
    *(uint*)0x011f6a18 = pSrcB[10];
    *(uint*)0x011f6a1c = pSrcB[11];
    *(uint*)0x011f6a20 = pSrcB[12];
    *(uint*)0x011f6a24 = pSrcB[13];
    *(uint*)0x011f6a28 = pSrcB[14];
    *(uint*)0x011f6a2c = pSrcB[15];

    // If global flag (bit 0) is set, process the matrices further
    if ((*(uint*)0x011f7430 & 1) != 0) {
        processMatrices(); // FUN_00614ab0
    }
}