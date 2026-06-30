// FUNC_NAME: Table::serializeTableToStrings
// Function address: 0x00630330
// Reconstructed C++ for table serialization into a string buffer.
// The function iterates over a sorted table (hash or tree) and writes
// its contents into an output buffer, preceded by a tag (4).
// It asserts that all elements are strings.

#include <cstdint>
#include <cstring>

// Forward declarations for external functions (Ghidra stubs)
uint32_t FUN_00627fe0(void* global, uint32_t* out); // likely get singleton
float    FUN_00628080(); // get some value (maybe hash table metric)
void     FUN_00627ac0(const char* msg); // assert/error handler
int32_t  FUN_00628820(int32_t); // get count/range start
void*    FUN_00637f10(); // iterate to next element in table? returns pointer to key-value pair
int32_t  FUN_00625830(); // check if current element is a string (returns non-zero if string)
void     FUN_00628c50(); // release or advance after string check
void     FUN_00628b20(uint32_t, uint32_t); // copy key?
uint32_t FUN_00627290(); // buffer resize? returns new buffer?
void     FUN_00626f80(void* obj, int32_t); // some buffer management
void     FUN_00626fd0(int32_t); // another buffer op
void     FUN_00627010(uint32_t); // set buffer?
void     FUN_006270e0(); // finish resize?
uint32_t FUN_00638920(void* obj, void* data, int32_t size); // write block to buffer
void     FUN_00626460(); // finalize serialization
void     FUN_00627a20(void* obj, int32_t, const char* msg); // error/abort

// External globals used
extern uint32_t DAT_00e2f044;      // some global singleton pointer
extern float    DAT_00e2b1a4;      // some threshold or default value
extern const char* PTR_s_table_00e2a8b0; // string "table"

class Table {
public:
    // Undefined offsets based on decompilation:
    // +0x00: unknown (likely vtable or type)
    // +0x04: unknown
    // +0x08: output buffer pointer (current write position)
    // +0x0c: pointer to table internal data (e.g., hash array)
    // +0x10: pointer to buffer control structure (for output)
    // Internal data structure (pointed by +0x0c):
    //   +0x00: type field? (compared to 5)
    //   +0x10: pointer to first bucket iterator?
    //   +0x18: pointer to second bucket iterator?
    //   +0x20: output buffer current size?
    //   +0x24: output buffer capacity?

    int32_t serializeTableToStrings() {
        uint32_t local_21c; // some value from singleton
        uint32_t uVar3;

        uVar3 = FUN_00627fe0(&DAT_00e2f044, &local_21c); // get some global state

        // Get pointers to internal table iteration elements
        int32_t* piVar4 = (int32_t*)(*(int32_t*)(this + 0x0c) + 0x10);
        float fVar8 = DAT_00e2b1a4;

        // Check first iterator end condition and retrieve value if valid
        if (piVar4 < *(int32_t**)(this + 0x08) && piVar4 != nullptr && *piVar4 > 0) {
            FUN_00628080(); // some function that possibly returns a float in XMM0
            fVar8 = in_XMM0_Da; // from previous call, but we need to capture it
        }

        // Now second iterator
        piVar4 = (int32_t*)(*(int32_t*)(this + 0x0c) + 0x18);
        int32_t local_224 = (int32_t)fVar8;

        if (piVar4 < *(int32_t**)(this + 0x08) && piVar4 != nullptr && *piVar4 > 0) {
            // read second iterator value
            // but fVar8 was overwritten? Actually the code computes local_224 from first, then overwrites fVar8
            // Let's follow original logic:
            // The code had: if (condition) { FUN_00628080(); fVar8 = in_XMM0_Da; } then afterwards, piVar4 = new value, local_224 = fVar8. Then if not condition else fVar8=0
            // We'll simulate with a separate variable
        } else {
            fVar8 = 0.0f;
        }

        int32_t iVar7, iVar5;
        // Now check the type field at the table data pointer
        int32_t* piData = *(int32_t**)(this + 0x0c);
        if (*(int32_t**)(this + 0x08) <= piData || piData == nullptr || *piData != 5) {
            iVar7 = 1;  // default start index
            // log error? or set default
            FUN_00627ac0(PTR_s_table_00e2a8b0); // "table"
        } else {
            iVar7 = local_224; // from earlier
        }

        int32_t local_228 = (int32_t)fVar8;
        if (iVar5 == 0) { // iVar5 is actually the previous iVar5? Wait, the decompiled code is messy. 
            // Actually the original code had:
            // iVar5 = (int)fVar8; iVar7 = local_224; *piVar4 != 5) { iVar7=1; ... }
            // Then later if(iVar5 ==0) {...}
            // So we need to keep track of iVar5 from earlier assignment.
            // Re-analyzing: The decompiled code is: 
            // iVar5 = (int)fVar8; iVar7 = local_224; if(condition) { iVar7=1; FUN_00627ac0(); iVar5 = extraout_ECX; }
            // local_228 = (int)fVar8;
            // if (iVar5 == 0) { ... }
            // So after the if block, iVar5 might be set to extraout_ECX (a register value from the function call). 
            // This is likely a bug in Ghidra decompilation. 
            // We'll assume that if the type is not 5, we set iVar7 to 1 and iVar5 to something.
            // For simplicity, we'll treat it as: if (type != 5) iVar7 = 1;
        }

        // Actually the code is messy. Let's reconstruct based on the loop condition.
        // I think the intention is:
        // - Get start index from some iterator (or default 1)
        // - Get end index from another source
        int32_t startIdx = local_224; // = first iterator value
        int32_t endIdx = local_228;   // = second iterator value (or fVar8)

        // But then there is a condition: if (iVar5 == 0)...
        // To simplify, let's write the loop as originally: do { ... } while (iVar7 <= local_228);
        // where iVar7 is startIdx and local_228 is endIdx.

        // We'll need to properly order:
        int32_t startIdx = iVar7; // from type check (could be 1 or local_224)
        int32_t endIdx = local_228; // from earlier

        // Buffer for building serialized data
        uint8_t auStack_20c[520];
        uint8_t* puStack_218 = auStack_20c;
        int32_t iStack_214 = 0; // count of writes?

        // Main iteration loop
        if (startIdx <= endIdx) {
            do {
                // Get next element from table (key-value pair, 8 bytes)
                uint32_t* puVar6 = (uint32_t*)FUN_00637f10();
                uint32_t* puVar1 = (uint32_t*)(*(int32_t*)(this + 0x08)); // current write pointer in output buffer
                *puVar1 = *puVar6;
                puVar1[1] = puVar6[1];
                *(int32_t*)(this + 0x08) = *(int32_t*)(this + 0x08) + 8; // advance output buffer

                // Verify that the element is a string
                int32_t iVar5 = FUN_00625830();
                if (iVar5 == 0) {
                    FUN_00627a20(this, 1, "table contains non-strings");
                    // Call abort/assert (int3)
                    void* pcVar2 = (void*)swi(3);
                    (*(uint32_t (*)())pcVar2)();
                    return 0;
                }

                FUN_00628c50(); // possibly release reference or advance

                // If we are not at the end, copy key again? 
                if (startIdx != endIdx) {
                    FUN_00628b20(uVar3, local_21c);
                    startIdx = local_224; // update? Actually original code: iVar7 = local_224
                }

                startIdx = startIdx + 1; // iVar7++
                // note: local_224 is updated in the loop
            } while (startIdx <= endIdx);
        }

        // After loop, compute the size of data accumulated in auStack_20c
        int32_t dataSize = (int32_t)(puStack_218 - auStack_20c);
        int32_t iVar5 = iStack_210; // which is param_1 (this)
        int32_t iVar7 = (int32_t)puStack_218 - (int32_t)auStack_20c;

        if (iVar7 != 0) {
            // Check if output buffer has enough space
            // Structure at this+0x10 -> control block -> offsets 0x20 (size) and 0x24 (capacity)
            int32_t* controlBlock = *(int32_t**)(this + 0x10);
            if (*(uint32_t*)(controlBlock + 0x20) <= *(uint32_t*)(controlBlock + 0x24)) {
                // Buffer needs reallocation?
                uint32_t uVar3 = FUN_00627290();
                FUN_00626f80(this, 0);
                FUN_00626fd0(0);
                FUN_00626f80(this, 0);
                FUN_00627010(uVar3);
                FUN_006270e0();
            }

            // Write tag (4) followed by the data
            uint32_t* puVar1 = (uint32_t*)(*(int32_t*)(this + 0x08));
            *puVar1 = 4; // tag
            uint32_t uVar3 = FUN_00638920(this, auStack_20c, iVar7);
            puVar1[1] = uVar3; // probably the data block size or something
            *(int32_t*)(this + 0x08) = *(int32_t*)(this + 0x08) + 8; // advance

            // Reset local buffer? (Not used later)
            puStack_218 = auStack_20c;
            iStack_214++;
        }

        FUN_00626460(); // finalize
        return 1;
    }
};