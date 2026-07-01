// FUNC_NAME: SimNpc::calculateThreatAssessment
int __thiscall SimNpc::calculateThreatAssessment(int* this_)
{
    byte threatCount;
    char cVar2;
    int threatValue;
    uint index;
    int totalThreat;
    
    threatCount = *(byte*)(*this_ + 9);  // +0x9: number of active threats
    totalThreat = 0;
    index = 0;
    if (threatCount != 0) {
        do {
            threatValue = *this_;
            // Get threat entity from threat list at offset +0x10
            threatValue = FUN_00405fd0(0, *(undefined4*)
                                          (*(int*)(threatValue + 0x10) +
                                          ((uint)*(byte*)(threatValue + 8) + (*(byte*)(threatValue + 10) & 1) + index) * 4
                                          ));
            if ((threatValue != 0) && (cVar2 = FUN_004a8100(), cVar2 != '\0')) {
                // Threat is valid and active
                threatValue = FUN_004a8170();  // getThreatScore
                totalThreat = totalThreat + threatValue;
            }
            index = index + 1;
        } while (index < threatCount);
    }
    threatValue = FUN_004a8170();  // getBaseThreat
    return threatValue + totalThreat;
}