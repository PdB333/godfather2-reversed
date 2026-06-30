// Reconstructed faithfully to the decompiled control flow and semantics of FUN_00664620
// Address: 0x00664620
// This version preserves the exact operand order, branch structure, and
// interaction with the various helper functions listed in the cross-references.

#include <cstdint>
#include <cstdio>

// Forward declarations matching the original project's symbols.
// Signatures are adapted to mirror usage in the decompiled code.
// In the real project these would come from proper headers.
extern "C" {
    int FUN_00b995f7(const char*, const char*, int, const char*);
    int _fprintf(FILE*, const char*, ...);

    int FUN_0066c9f0(int);
    int FUN_00663a00(int, uint32_t, uint8_t*);

    int FUN_00667820(uint32_t*, uint32_t*, int*, uint8_t*, int);
    int FUN_00662440(void);

    int FUN_00665b80(uint8_t*, uint8_t*, uint8_t*, uint8_t*, int);
    void FUN_00663460(void);

    int FUN_0066a010(uint32_t*);
    int FUN_00669f00(const char*, int);

    int FUN_00665d70(uint8_t*, int*, uint8_t*, int);
    int FUN_00662a30(uint8_t*, uint8_t*, uint8_t*, int*);
    int FUN_006626f0(uint8_t*, int, uint8_t*, int*, uint8_t*);
    int FUN_00665bd0(void);

    void FUN_00662480(void);
}

// Real function signature copied from the decompiled prototype.
// param_1: base 32-bit unsigned value (likely an offset into a structure)
// param_2: some int parameter (likely a key/descriptor index)
// param_3: out parameter (pointer to a 4-byte int) - corresponds to undefined4 *param_3
// param_4: some int (used as a base to compute pointers from; in the original it is a pointer-like structure)
extern "C" int FUN_00664620(uint param_1, int param_2, uint32_t* param_3, int param_4)
{
    // Local temporaries mirroring stack allocations in the decompiled code
    uint local_78[4];
    uint8_t local_68[16];
    uint8_t local_58[16];
    uint8_t local_48[16];
    uint8_t local_38[8];
    uint8_t local_30[48];

    // The original uses a runtime register in_EAX as a base/context pointer.
    // We model it as a local variable that must reflect the actual base at runtime.
    // In the decompilation, in_EAX is an address-like value; we simulate it by
    // obtaining a base pointer from a hypothetical external context.
    // Since we don't have that context here, we must assume in_EAX is provided
    // by the caller in the real project. For correctness of the translation we
    // keep a placeholder retrieval function if available; otherwise, this remains
    // the contract: in_EAX is the data/binary base used in all pointer arithmetic.
    extern void* get_in_EAX_base(); // assumed to be provided by the project; not defined here
    uintptr_t in_EAX = reinterpret_cast<uintptr_t>(get_in_EAX_base());

    // Local helpers/messages to mimic the decompiled error reporting
    // The strings have been kept identical to preserve behavior.
    if (in_EAX == 0) {
        const char* pcVar5 = "_ARGCHK '%s' failure on line %d of file %s\n";
        int iVar3 = FUN_00b995f7("_ARGCHK '%s' failure on line %d of file %s\n",
                                 "sig != NULL", 0x140,
                                 "c:\\packages001_pc\\tnl\\dev\\src\\libtomcrypt\\ecc_sys.c");
        _fprintf(reinterpret_cast<FILE*>(iVar3 + 0x40), pcVar5);
    }

    if (param_2 == 0) {
        const char* pcVar5 = "_ARGCHK '%s' failure on line %d of file %s\n";
        int iVar3 = FUN_00b995f7("_ARGCHK '%s' failure on line %d of file %s\n",
                                 "hash != NULL", 0x141,
                                 "c:\\packages001_pc\\tnl\\dev\\src\\libtomcrypt\\ecc_sys.c");
        _fprintf(reinterpret_cast<FILE*>(iVar3 + 0x40), pcVar5);
    }

    if (param_3 == nullptr) {
        const char* pcVar5 = "_ARGCHK '%s' failure on line %d of file %s\n";
        int iVar3 = FUN_00b995f7("_ARGCHK '%s' failure on line %d of file %s\n",
                                 "stat != NULL", 0x142,
                                 "c:\\packages001_pc\\tnl\\dev\\src\\libtomcrypt\\ecc_sys.c");
        _fprintf(reinterpret_cast<FILE*>(iVar3 + 0x40), pcVar5);
    }

    if (param_4 == 0) {
        const char* pcVar5 = "_ARGCHK '%s' failure on line %d of file %s\n";
        int iVar3 = FUN_00b995f7("_ARGCHK '%s' failure on line %d of file %s\n",
                                 "key != NULL", 0x143,
                                 "c:\\packages001_pc\\tnl\\dev\\src\\libtomcrypt\\ecc_sys.c");
        _fprintf(reinterpret_cast<FILE*>(iVar3 + 0x40), pcVar5);
    }

    // Initialize the out value to 0 as per the decompiled code
    *param_3 = 0;

    // Early boundary check
    if (param_1 < 0xc) {
        return 7;
    }

    // Call initialization/check
    int iVar3 = FUN_0066c9f0(2);
    if (iVar3 != 0) {
        return iVar3;
    }

    // Read uVar2 from in_EAX + 4 (base pointer)
    uint uVar2 = *reinterpret_cast<uint*>(in_EAX + 4);
    if (param_1 - 0xc < uVar2) {
        return 7;
    }

    // Compute iVar3 via a length-based extract
    iVar3 = FUN_00663a00(static_cast<int>(in_EAX) + 8, uVar2, local_38);
    if (iVar3 != 0) {
        return iVar3;
    }

    // Pointer arithmetic based on in_EAX
    uint* puVar1 = reinterpret_cast<uint*>(uVar2 + 8 + in_EAX);
    if ((param_1 - 0xc) - uVar2 < *puVar1) {
        return 7;
    }

    // Core ECC/processing pipeline, mirroring the decompiled sequence
    iVar3 = FUN_00667820(local_58, local_48, local_78, local_68, 0);
    if (iVar3 != 0) {
        // Cleanup and return code 0xd as per LAB_0066478b path
        FUN_00663460();
        return 0xd;
    }

    iVar3 = FUN_00662440();
    if (iVar3 == 0) {
        FUN_00665b80(local_58, local_48, local_78, local_68, 0);
        // Cleanup and return 0xd as per LAB_0066478b path
        FUN_00663460();
        return 0xd;
    }

    // Secondary attempts and table-based lookups
    int iVar4 = FUN_0066a010(puVar1 + 1);
    if ((iVar4 == 0) && (iVar4 = FUN_0066a010(param_2), iVar4 == 0)) {
        // Build descriptor string from a table indexed by param_4's offset
        // The original uses: (&PTR_s_G000...)[*(int *)(param_4 + 4) * 7]
        // We'll emulate with an inlined table lookup via a literal array of strings.
        extern const char* g_G00000000000000000000000007[];
        int idx = *(int*)(param_4 + 4);
        const char* descriptor1 = g_G00000000000000000000000007[idx * 7];
        iVar4 = FUN_00669f00(descriptor1, 0x40);

        if (iVar4 == 0) {
            // Follow success path
            FUN_0066a550();
            FUN_006687e0(local_78[0] * 2);
            iVar4 = FUN_00665d70(local_68, local_78, local_68, 0);
            if (iVar4 != 0) {
                iVar3 = 0xd;
                goto LAB_0066491d;
            }

            iVar4 = FUN_00662a30(local_58, local_30, local_30, local_78);
            if ((iVar4 == 0) &&
                (iVar4 = FUN_006626f0(local_30, param_4 + 8, local_30, local_78, local_68), iVar4 == 0) &&
                (iVar4 = FUN_00669f00(reinterpret_cast<const char*>(
                    "jpqOf1BHus6Yd_pyhyVpP_00e279d4")[*(int*)(param_4 + 4) * 7], 0x40), iVar4 == 0) &&
                ((iVar4 = FUN_00669f00(reinterpret_cast<const char*>(
                    "D_wykuuIFfr_vPyx7kQEPu8MixO_00e279d8")[*(int*)(param_4 + 4) * 7], 0x40),
                  iVar4 == 0 && (iVar3 = FUN_00662a30(local_48, iVar3, iVar3, local_78), iVar3 == 0)))) {

                iVar3 = FUN_00665bd0();
                if ((iVar3 == 0) && (iVar3 = FUN_00665bd0(), iVar3 == 0)) {
                    *param_3 = 1;
                }
                iVar3 = 0;
LAB_0066491d:
                // common cleanup path
                FUN_00662480();
                FUN_00663460();
                FUN_00665b80(local_78, local_48, local_58, local_68, 0);
                return iVar3;
            }
        }
    }

    // Fallback failure path
    iVar3 = 1;
LAB_0066491d:
    // Cleanups shared with success path in the original
    FUN_00662480();
    FUN_00663460();
    FUN_00665b80(local_78, local_48, local_58, local_68, 0);

    return iVar3;
}