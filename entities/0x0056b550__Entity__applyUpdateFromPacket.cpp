// FUNC_NAME: Entity::applyUpdateFromPacket
// Function at 0x0056b550: Copies data from source packet into entity state, preserving certain fields (indices 3, 7, 11).
void __fastcall Entity::applyUpdateFromPacket(Entity* this, const uint32* source)
{
    // Source indices used: 0,2,4,5,6,8,9,10,12,13,14, and 1 (via param_1[1])
    uint32 s0 = source[0];
    uint32 s2 = source[2];
    uint32 s4 = source[4];
    uint32 s5 = source[5];
    uint32 s6 = source[6];
    uint32 s8 = source[8];
    uint32 s9 = source[9];
    uint32 s10 = source[10];
    uint32 s12 = source[12];
    uint32 s13 = source[13];
    uint32 s14 = source[14];
    uint32 s1 = source[1];

    // Save original fields at indices 3, 7, 11 (these will be restored)
    uint32 orig3 = this->field3;
    uint32 orig7 = this->field7;
    uint32 orig11 = this->field11;

    // Write new values (reordered from source)
    this->field0 = s0;        // source[0]
    this->field1 = s4;        // source[4]
    this->field2 = s8;        // source[8]
    this->field3 = s12;       // source[12] (will be reverted)
    this->field4 = s1;        // source[1]
    this->field5 = s5;        // source[5]
    this->field6 = s9;        // source[9]
    this->field7 = s13;       // source[13] (will be reverted)
    this->field8 = s2;        // source[2]
    this->field9 = s6;        // source[6]
    this->field10 = s10;      // source[10]
    this->field11 = s14;      // source[14] (will be reverted)

    // Restore the three fields that should not be overwritten
    this->field3 = orig3;
    this->field7 = orig7;
    this->field11 = orig11;
}