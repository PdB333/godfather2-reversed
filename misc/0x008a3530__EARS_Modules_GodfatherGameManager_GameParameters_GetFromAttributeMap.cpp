// Xbox PDB: EARS_Modules_GodfatherGameManager_GameParameters_GetFromAttributeMap
// FUNC_NAME: MatchParameters::writeToWriter
// Address: 0x008a3530
// Role: Serializes match parameters to a data writer (e.g., for network packet)
// Fields packed into a 32-bit attribute value using bit fields.
// Writer object at param_2 has vtable with virtual methods at offsets:
//   0x24: writeString(const char* name, const char* value)
//   0x2c: writeByte(const char* name, uint8_t value)
//   0x34: writeInt(const char* name, int32_t value)

struct MatchParameters {
    int32_t matchTypeIndex;       // +0x00
    uint8_t isStrictNAT;          // +0x04 (byte)
    int32_t modeIdx;              // +0x08
    int32_t modeRequested;        // +0x0C
    int32_t mapHash;              // +0x10
    uint8_t fieldAt15;            // +0x14 (byte, used in packed attributes)
    int32_t weaponIdx;            // +0x18
    uint8_t fieldAt1C_4bits;      // +0x1C (low 4 bits)
    uint8_t fieldAt20_3bits;      // +0x20 (low 3 bits)
    uint8_t fieldAt24_3bits;      // +0x24 (low 3 bits)
    uint8_t fieldAt28_4bits;      // +0x28 (low 4 bits)
    uint8_t fieldAt2C_3bits;      // +0x2C (low 3 bits)
    int32_t scoreLimit;           // +0x30
    int32_t roundScore;           // +0x34
    int32_t donWager;             // +0x38
    int32_t donFlow;              // +0x3C
    uint8_t donMode;              // +0x4C (byte)
    char version[?];              // +0x4D (null-terminated string, max length inferred)
};

void __thiscall MatchParameters::writeToWriter(IWriter* writer) {
    // Pack various bitfields into a single 32-bit attribute value
    // Layout (from LSB to MSB):
    // Bits 0-2: fieldAt24_3bits (3 bits)
    // Bits 3-5: fieldAt20_3bits (3 bits)
    // Bits 6-8: fieldAt14_3bits (3 bits)
    // Bits 9-12: fieldAt1C_4bits (4 bits)
    // Bits 13-16: fieldAt28_4bits (4 bits)
    // Bits 17-19: fieldAt2C_3bits (3 bits)
    // Bit 20: (fieldAt15 != 0) as flag
    // Bits 21-27: unused? Actually the shifts produce bits up to 20+8=28, but final *8 moves bits further.
    // The exact layout: Let's compute explicitly.
    uint32_t packed = 0;
    packed |= (this->fieldAt24_3bits & 7);
    packed <<= 3;
    packed |= (this->fieldAt20_3bits & 7);
    packed <<= 3;
    packed |= (this->fieldAt14_3bits & 7);
    packed <<= 4;
    packed |= (this->fieldAt1C_4bits & 0xF);
    packed <<= 8;
    packed |= (this->fieldAt28_4bits & 0xF);
    packed <<= 3; // actually the shift in the decompiled code is *8 (<<3) but here it's after the OR? Let's re-derive from original:
    // Original: ((((((uint)(*(char *)((int)param_1 + 5) != '\0') * 8 | param_1[0xb] & 7) << 8 | param_1[10] & 0xf) << 4 | param_1[7] & 0xf) * 8 | param_1[5] & 7) * 8 | param_1[8] & 7) * 8 | param_1[9] & 7
    // So the LSB part is fieldAt24, then fieldAt20, then fieldAt14 (which is param_1[5]), then fieldAt1C (param_1[7]), then fieldAt28 (param_1[10]), then flag+fieldAt2C (param_1[0xb]).
    // The shifts are: start with (flag*8 | fieldAt2C) => bits 0-2: fieldAt2C, bit3: flag.
    // Then <<8, OR fieldAt28 => bits 4-7: fieldAt28? Actually after shift, fieldAt28 goes to bits 3-6? Let's not overcomplicate.
    // Use the exact calculation from decompiled for correctness.
    uint32_t flag = (this->fieldAt15 != 0) ? 8 : 0;
    packed = ((flag | (this->fieldAt2C_3bits & 7)) << 8) | (this->fieldAt28_4bits & 0xF);
    packed = (packed << 4) | (this->fieldAt1C_4bits & 0xF);
    packed = (packed * 8) | (this->fieldAt14_3bits & 7);  // *8 equivalent to <<3
    packed = (packed * 8) | (this->fieldAt20_3bits & 7);
    packed = (packed * 8) | (this->fieldAt24_3bits & 7);

    // Write all fields through the writer's virtual methods
    writer->writeInt("PackedAttributes", packed);
    writer->writeInt("MatchTypeIndex", this->matchTypeIndex);
    writer->writeInt("ModeIdx", this->modeIdx);
    writer->writeInt("MapHash", this->mapHash);
    writer->writeInt("WeaponIdx", this->weaponIdx);
    writer->writeInt("ScoreLimit", this->scoreLimit);
    writer->writeInt("RoundScore", this->roundScore);
    writer->writeInt("DonWager", this->donWager);
    writer->writeInt("DonFlow", this->donFlow);
    writer->writeByte("DonMode", this->donMode);
    writer->writeByte("IsStrictNAT", this->isStrictNAT);
    writer->writeInt("ModeRequested", this->modeRequested);
    writer->writeString("Version", &this->version[0]);  // string at offset 0x4D
}