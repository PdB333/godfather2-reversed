// FUNC_NAME: AptActionInterpreter::relocateActionData
// Address: 0x005ac340
// Role: Relocates pointers in serialized APT action bytecode during read/write.
// param_1: baseOffset to add/subtract (usually the buffer's base address)
// param_2: writeFlag (0 = reading/loading (subtract offsets), non-zero = writing/saving (add offsets))
// param_3: pOutConstantIndex - pointer to a running constant index counter (incremented when constants are consumed)

#include <cstdint>

// Unknown assertion handler (FUN_0059bf00)
extern void aptAssert(const char* expression, const char* file, uint32_t line, uint32_t level, const char* msg);

// Global allocator (FUN_0059caf0)
extern void* (*g_aptAllocator)(uint32_t size, uint32_t flags);

// Known APT atom types (from the constant table handling)
enum AptAtomType : uint32_t {
    kAtomType_String = 1,
    kAtomType_Number = 3,  // not implemented? uses DAT_0119cbbc
    kAtomType_Integer = 4, // FUN_005abff0
    kAtomType_Float = 5,   // FUN_005a8580
    kAtomType_Register = 6,// stores a uint32 value
    kAtomType_Property = 7,// stores a uint32 value
    kAtomType_Method = 8,  // FUN_005ac020
};

// Atom header (first 4 bytes). Type masked by 0x7fff, flags by 0x8000
struct AptAtom {
    uint32_t header; // lower 15 bits = type, bit 15 = some flag
    // followed by type-specific data
};

// Forward declarations for atom constructors
void AptAtom_constructString(AptAtom* atom, const char* str);
void AptAtom_constructInteger(AptAtom* atom, uint32_t value);
void AptAtom_constructFloat(AptAtom* atom, float value);
void AptAtom_constructRegister(AptAtom* atom, uint32_t value);
void AptAtom_constructProperty(AptAtom* atom, uint32_t value);
void AptAtom_constructMethod(AptAtom* atom, uint32_t value);

// Function that releases an atom (FUN_0059c230)
extern void AptAtom_release(AptAtom* atom);

void AptActionInterpreter::relocateActionData(
    int32_t baseOffset,
    uint32_t writeFlag,      // 0 = reading (subtract), non-zero = writing (add)
    int32_t* pOutConstantIndex
) {
    const uint8_t* pData = ...; // The actual data pointer is passed in EAX in the original code.
    // For reconstruction, assume it's passed as an additional parameter or this pointer.
    // The original uses in_EAX as the start of the byte stream.
    // We'll assume the function is called with pData as a hidden first param (like __fastcall?).
    // To match Ghidra's output, we'll treat pData as a member of a struct or just a local.
    // Since the decompiler didn't capture it as a param, we'll add it as part of the context.
    // For cleanliness, we'll make it explicit:
    const uint8_t* pByteCode = pData; // pretend this is passed

    const uint8_t* opcodePtr = pByteCode;
    // The actual code increments opcodePtr by 1 after reading each opcode.
    // But the first byte is read as cVar1.
    while (true) {
        uint8_t opcode = *opcodePtr++;
        if (opcode == 0) return;

        // Opcodes are signed characters; we cast to int8_t for easier switch.
        int8_t signedOpcode = static_cast<int8_t>(opcode);
        switch (signedOpcode) {
        case -0x7F: // 0x81
        case -0x79: // 0x87
        case -0x67: // 0x99
        case -99:   // 0x9D
        case -0x61: // 0x9F
            // Skip a DWORD-aligned block of 4 bytes (fixed size)
            opcodePtr = reinterpret_cast<const uint8_t*>(
                (reinterpret_cast<uintptr_t>(opcodePtr) + 3U) & ~3U
            ) + 4;
            break;

        case -0x7D: { // 0x83 - two string pointers (szUrl, szWin)
            uint32_t* ptrs = reinterpret_cast<uint32_t*>(
                (reinterpret_cast<uintptr_t>(opcodePtr) + 3U) & ~3U
            );
            opcodePtr = reinterpret_cast<const uint8_t*>(ptrs + 2);
            if (writeFlag == 0) {
                if (ptrs[0] != 0) ptrs[0] -= baseOffset;
                if (ptrs[1] != 0) ptrs[1] -= baseOffset;
            } else {
                // Debug assertions from original
                if (ptrs[0] >= 0xFFFFF) aptAssert("(unsigned)(pData->szUrl) < 0xfffff", "...\\AptActionInterpreter.cpp", 0x17E, 2, nullptr);
                if (ptrs[0] != 0) ptrs[0] += baseOffset;
                if (ptrs[1] >= 0xFFFFF) aptAssert("(unsigned)(pData->szWin) < 0xfffff", "...\\AptActionInterpreter.cpp", 0x17F, 2, nullptr);
                if (ptrs[1] != 0) ptrs[1] += baseOffset;
            }
            break;
        }

        case -0x78: // 0x88 - constant table array (items.apItems)
        case -0x6A: // 0x96 - same as above?
        {
            int32_t* arrayInfo = reinterpret_cast<int32_t*>(
                (reinterpret_cast<uintptr_t>(opcodePtr) + 3U) & ~3U
            );
            int32_t count = arrayInfo[0];
            int32_t* itemPtr = reinterpret_cast<int32_t*>(arrayInfo[1]); // pointer to array of constant indices
            opcodePtr = reinterpret_cast<const uint8_t*>(arrayInfo + 2);

            if (writeFlag == 0) {
                // Reading: reload constant table entries
                for (int i = 0; i < count; ++i) {
                    uint32_t* oldAtom = reinterpret_cast<uint32_t*>(itemPtr[i]);
                    if (oldAtom) {
                        // Release old atom
                        // (call with oldAtom->header & 0x7fff to dispatch? The code uses a global vtable)
                        // The original does: (**(code **)(&DAT_0103aee0 + (*puVar9 & 0x7fff) * 4))(puVar9);
                        // Assuming a jump table for release
                        // We'll call a generic release
                        AptAtom_release(reinterpret_cast<AptAtom*>(oldAtom));
                    }
                    // Assign new constant index
                    itemPtr[i] = *pOutConstantIndex;
                    (*pOutConstantIndex)++;
                }
                // Adjust the array pointer itself (subtract offset)
                if (arrayInfo[1] != 0) arrayInfo[1] -= baseOffset;
            } else {
                // Writing: populate constant table from the constant pool
                if (arrayInfo[1] >= 0xFFFFF) {
                    aptAssert("(unsigned)(pData->items.apItems) < 0xfffff", "...\\AptActionInterpreter.cpp", 0x12A, 2, nullptr);
                }
                if (arrayInfo[1] != 0) arrayInfo[1] += baseOffset;

                for (int i = 0; i < count; ++i) {
                    int32_t constIndex = itemPtr[i];
                    if (constIndex != *pOutConstantIndex) {
                        // Debug assertion failure
                        aptAssert("nConstTableIndex == *pnCurrentConstantIndex", "...\\AptActionInterpreter.cpp", 0x13A, 2, nullptr);
                    }
                    (*pOutConstantIndex)++;
                    // Read constant from constant pool (param_2 + 0x1c)
                    // In original, param_2 is some object with a constant table at offset 0x1c.
                    // For reconstruction, assume 'this' is the interpreter with member m_constTable.
                    // We'll access it via base object (assume it's a global or passed as param).
                    // Since we don't have the full context, we'll simulate:
                    int32_t tableBase = reinterpret_cast<int32_t>(this) + 0x1c; // approximate
                    int32_t constantEntryOffset = constIndex * 8; // each entry: type (4 bytes) + value (4 bytes)
                    int32_t constantType = *reinterpret_cast<int32_t*>(tableBase + constantEntryOffset);
                    int32_t constantValue = *reinterpret_cast<int32_t*>(tableBase + constantEntryOffset + 4);

                    AptAtom* newAtom = nullptr;
                    switch (constantType) {
                    case 1: { // String constant
                        if (constantValue >= 0xFFFFF) {
                            aptAssert("(unsigned)(aConstantFile->aConstants[nConstTableIndex].szString) < 0xfffff", "...\\AptActionInterpreter.cpp", 0x148, 2, nullptr);
                        }
                        // Adjust string pointer relative to base (like other strings)
                        constantValue += reinterpret_cast<int32_t>(this); // or baseOffset?
                        // In the original, they add param_2 (the interpreter base) and then later subtract it.
                        // For simplicity, we assume the string pointer is already relative to the buffer.
                        // Actually the code does: *piVar2 = iVar3 + param_2; then later subtracts param_2.
                        // So it's a relative offset from the interpreter.
                        // But we'll keep it as is.
                        newAtom = reinterpret_cast<AptAtom*>(g_aptAllocator(0x24, 0));
                        if (newAtom) {
                            newAtom->header = (newAtom->header & 0xFFFF8001) | 1;
                            *reinterpret_cast<uint16_t*>(reinterpret_cast<uint8_t*>(newAtom) + 2) = 0;
                            newAtom->header |= 0x8000;
                            AptAtom_constructString(newAtom, reinterpret_cast<char*>(constantValue));
                            // Set a sentinel (0xbeefceec) at offset 0x20? Original: puVar7[8] = 0xbeefceec;
                            // But 8 is index, so byte offset 0x20? Assuming struct size 0x24.
                            reinterpret_cast<uint32_t*>(newAtom)[8] = 0xbeefceec;
                        }
                        break;
                    }
                    case 6: { // Register constant
                        newAtom = reinterpret_cast<AptAtom*>(g_aptAllocator(8, 0));
                        if (newAtom) {
                            newAtom->header = (newAtom->header & 0xFFFF8006) | 6;
                            *reinterpret_cast<uint16_t*>(reinterpret_cast<uint8_t*>(newAtom) + 2) = 0;
                            newAtom->header |= 0x8000;
                            reinterpret_cast<uint32_t*>(newAtom)[1] = constantValue;
                        }
                        break;
                    }
                    case 7: { // Property constant
                        newAtom = reinterpret_cast<AptAtom*>(g_aptAllocator(8, 0));
                        if (newAtom) {
                            newAtom->header = (newAtom->header & 0xFFFF8007) | 7;
                            *reinterpret_cast<uint16_t*>(reinterpret_cast<uint8_t*>(newAtom) + 2) = 0;
                            newAtom->header |= 0x8000;
                            reinterpret_cast<uint32_t*>(newAtom)[1] = constantValue;
                        }
                        break;
                    }
                    case 8: // Method constant
                        newAtom = reinterpret_cast<AptAtom*>(g_aptAllocator(8, 0) ? AptAtom_constructMethod(?) : nullptr);
                        break;
                    case 5: // Float constant
                        newAtom = reinterpret_cast<AptAtom*>(g_aptAllocator(8, 0) ? AptAtom_constructFloat(?) : nullptr);
                        break;
                    case 4: // Integer constant
                        newAtom = reinterpret_cast<AptAtom*>(g_aptAllocator(8, 0) ? AptAtom_constructInteger(?) : nullptr);
                        break;
                    case 3: // Number constant (special? uses global DAT_0119cbbc)
                        newAtom = reinterpret_cast<AptAtom*>(&g_numberAtomPlaceholder); // placeholder
                        break;
                    }
                    // Store the atom in the array
                    itemPtr[i] = reinterpret_cast<int32_t>(newAtom);
                    // If newAtom is not the number placeholder, check if we need to call release?
                    // The original does some checks after storing.
                }
            }
            break;
        }

        case -0x75: { // 0x8B - single pointer (szTarget)
            uint32_t* ptr = reinterpret_cast<uint32_t*>(
                (reinterpret_cast<uintptr_t>(opcodePtr) + 3U) & ~3U
            );
            opcodePtr = reinterpret_cast<const uint8_t*>(ptr + 1);
            if (writeFlag == 0) {
                if (*ptr != 0) *ptr -= baseOffset;
            } else {
                if (*ptr >= 0xFFFFF) aptAssert("(unsigned)(pData->szTarget) < 0xfffff", "...\\AptActionInterpreter.cpp", 0x194, 2, nullptr);
                if (*ptr != 0) *ptr += baseOffset;
            }
            break;
        }

        case -0x74: { // 0x8C - single pointer (szLabel)
            uint32_t* ptr = reinterpret_cast<uint32_t*>(
                (reinterpret_cast<uintptr_t>(opcodePtr) + 3U) & ~3U
            );
            opcodePtr = reinterpret_cast<const uint8_t*>(ptr + 1);
            if (writeFlag == 0) {
                if (*ptr != 0) *ptr -= baseOffset;
            } else {
                if (*ptr >= 0xFFFFF) aptAssert("(unsigned)(pData->szLabel) < 0xfffff", "...\\AptActionInterpreter.cpp", 0x19D, 2, nullptr);
                if (*ptr != 0) *ptr += baseOffset;
            }
            break;
        }

        case -0x6C: { // 0x94 - single pointer (pEnd)
            uint32_t* ptr = reinterpret_cast<uint32_t*>(
                (reinterpret_cast<uintptr_t>(opcodePtr) + 3U) & ~3U
            );
            opcodePtr = reinterpret_cast<const uint8_t*>(ptr + 1);
            if (writeFlag == 0) {
                if (*ptr != 0) *ptr -= baseOffset;
            } else {
                if (*ptr >= 0xFFFFF) aptAssert("(unsigned)(pData->pEnd) < 0xfffff", "...\\AptActionInterpreter.cpp", 0x1C3, 2, nullptr);
                if (*ptr != 0) *ptr += baseOffset;
            }
            break;
        }

        case -0x65: { // 0x9B - complex block with name and params (szName, count, aszParams)
            uint32_t* block = reinterpret_cast<uint32_t*>(
                (reinterpret_cast<uintptr_t>(opcodePtr) + 3U) & ~3U
            );
            uint32_t namePtr = block[0];
            int32_t paramCount = block[1];
            uint32_t paramsArrayPtr = block[2];
            opcodePtr = reinterpret_cast<const uint8_t*>(block + 6); // skip 6 dwords (0x18 bytes?)

            if (writeFlag == 0) {
                if (namePtr != 0) namePtr -= baseOffset;
                // We'll adjust the name pointer later after the loop
                // Actually the original adjusts namePtr first then params later.
                // But we'll do as per original: adjust name, then adjust each param element pointer, then params array pointer.
            } else {
                if (namePtr >= 0xFFFFF) aptAssert("(unsigned)(pData->szName) < 0xfffff", "...\\AptActionInterpreter.cpp", 0x1A7, 2, nullptr);
                if (namePtr != 0) namePtr += baseOffset;
                if (paramsArrayPtr >= 0xFFFFF) aptAssert("(unsigned)(pData->aszParams) < 0xfffff", "...\\AptActionInterpreter.cpp", 0x1A8, 2, nullptr);
                if (paramsArrayPtr != 0) paramsArrayPtr += baseOffset;
            }

            // Process each parameter
            for (int i = 0; i < paramCount; ++i) {
                int32_t* paramElem = reinterpret_cast<int32_t*>(paramsArrayPtr + i * 4);
                if (writeFlag == 0) {
                    if (*paramElem != 0) *paramElem -= baseOffset;
                } else {
                    if (static_cast<uint32_t>(*paramElem) >= 0xFFFFF) {
                        aptAssert("(unsigned)(pData->aszParams[i]) < 0xfffff", "...\\AptActionInterpreter.cpp", 0x1AB, 2, nullptr);
                    }
                    if (*paramElem != 0) *paramElem += baseOffset;
                }
            }

            // Adjust the params array pointer if needed (already done above for write, for read we need to adjust after loop)
            if (writeFlag == 0 && paramsArrayPtr != 0) paramsArrayPtr -= baseOffset;

            // Set sentinel values (only on read? Original sets these only when bVar11 == true (read))
            if (writeFlag == 0) {
                block[4] = 0x98765432;
                block[5] = 0x12345678;
            }
            break;
        }

        default:
            // Unknown opcode; should not happen
            break;
        }
    }
}