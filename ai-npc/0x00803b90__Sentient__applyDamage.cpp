// FUNC_NAME: Sentient::applyDamage
void __thiscall Sentient::applyDamage(Sentient* thisObj, DamageInfo* damageInfo, uint hitLocation, uint damageFlags, AttackerData* attackerData, bool isCritical, undefined4 param_7, bool isPenetrating)
{
    char cVar1;
    int iVar2;
    int* piVar3;
    uint unaff_EBX; // saved register value
    float unaff_EBP; // computed damage multiplier
    float10 fVar4;
    int damageValue; // iStack_94
    int localArray[2]; // aiStack_90
    int* savedPtr1; // piStack_88
    int savedPtr1_count; // iStack_84
    int* savedPtr2; // piStack_80
    int savedPtr2_count; // iStack_7c
    undefined8 attackerDataCopy; // uStack_78
    undefined4 attackerDataExtra; // uStack_70
    undefined8 thisObjData; // uStack_6c
    undefined4 thisObjDataExtra; // uStack_64
    int localInt; // iStack_60
    undefined4 localFlags; // uStack_5c
    uint localHitLocation; // uStack_54? actually uStack_54 is param_3 but then stored elsewhere
    uint localDamageFlags; // uStack_50
    undefined4 globalFlag; // uStack_4c (from DAT_01205224)
    uint localFlags2; // uStack_48

    // Check if damageInfo is valid and passes a condition via vtable call
    if ((damageInfo != nullptr) && 
        (cVar1 = (**(code**)(*damageInfo + 0x78))(), cVar1 != '\0')) 
    {
        FUN_0084dd20(); // some initialization or debug hook

        // Manage reference counting for savedPtr1 (pointing to thisObj + 0x48)
        if (thisObj == nullptr) {
            piVar3 = nullptr;
        } else {
            piVar3 = thisObj + 0x12; // offset 0x48
        }
        if (savedPtr1 != piVar3) {
            if (savedPtr1 != nullptr) {
                FUN_004daf90(&savedPtr1); // release reference
            }
            savedPtr1 = piVar3;
            if (piVar3 != nullptr) {
                savedPtr1_count = piVar3[1]; // reference count?
                piVar3[1] = (int)&savedPtr1;
            }
        }

        // Same for savedPtr2
        if (thisObj == nullptr) {
            piVar3 = nullptr;
        } else {
            piVar3 = thisObj + 0x12;
        }
        if (savedPtr2 != piVar3) {
            if (savedPtr2 != nullptr) {
                FUN_004daf90(&savedPtr2);
            }
            savedPtr2 = piVar3;
            if (piVar3 != nullptr) {
                savedPtr2_count = piVar3[1];
                piVar3[1] = (int)&savedPtr2;
            }
        }

        iVar2 = FUN_00471610(); // get some manager (e.g., GameManager)
        attackerDataCopy = *(undefined8*)(iVar2 + 0x30); // copy from manager
        attackerDataExtra = *(undefined4*)(iVar2 + 0x38);
        thisObjData = *attackerData; // copy first 8 bytes from attackerData
        thisObjDataExtra = *(undefined4*)((char*)attackerData + 8); // second dword
        globalFlag = DAT_01205224; // global flag
        localFlags = 1;
        localDamageFlags = damageFlags;
        localHitLocation = hitLocation;

        if (isCritical) {
            localFlags2 |= 2;
        }
        if (isPenetrating) {
            localFlags2 |= 8;
        }

        // Determine base damage value based on hit location
        switch(hitLocation) {
        default:
            damageValue = thisObj[0x752]; // offset 0x1D48 - base damage? or damage per hit location
            break;
        case 2:
            damageValue = thisObj[0x753]; // offset 0x1D4C
            break;
        case 3:
            damageValue = thisObj[0x754]; // offset 0x1D50
            break;
        case 6:
            damageValue = 0;
            break;
        case 7:
            damageValue = thisObj[0x756]; // offset 0x1D58
            break;
        case 8:
            damageValue = thisObj[0x757]; // offset 0x1D5C
            break;
        }

        localArray[0] = 0;
        localInt = damageValue;

        // Check weapon ability via vtable
        cVar1 = (**(code**)(*damageInfo + 0x10))(0x55859efa, localArray);
        piVar3 = (int*)(-(uint)(cVar1 != '\0') & unaff_EBX); // boolean to pointer mask

        // Compute damage multiplier (unaff_EBP)
        if ((attackerData == nullptr) || (((uint)thisObj[0x238] >> 10 & 1) == 0)) {
            // Normal case: call virtual function on thisObj to get base multiplier
            fVar4 = (float10)(**(code**)(*thisObj + 0x26c))();
            unaff_EBP = (float)(fVar4 * (float10)thisObjData._4_4_); // multiply by second float from thisObjData
        }
        else if ((piVar3 == nullptr) || 
                 (((char)piVar3[0x6e3] != '\x02' && ((char)piVar3[0x6e3] != '\x03')))) 
        {
            // If attackerData exists and thisObj has flag, use attacker's damage multiplier
            unaff_EBP = *(float*)((int)attackerData + 0x1dc) * thisObjData._4_4_;
            // Check additional condition on attackerData (bit 3 of field at offset 0x3a*4? actually attackerData+0x3a is weird)
            if (((*(uint*)((char*)attackerData + 0x3a) >> 3 & 1) != 0) &&
                (cVar1 = (**(code**)(*(int*)thisObj[0x17d] + 0x1c))(), cVar1 != '\0')) 
            {
                FUN_00707680(unaff_EBP); // apply some force
            }
        }
        else {
            // piVar3 type is 2 or 3 (melee?)
            localDamageFlags |= 0x80; // set a flag
        }

        // Check if piVar3 (attacker?) is valid and ally check
        if ((piVar3 != nullptr) && 
            (cVar1 = FUN_0043c6c0(thisObj, piVar3[0x792]), cVar1 == '\0') && // not friendly?
            (cVar1 = (**(code**)(*piVar3 + 0x78))(), cVar1 != '\0')) 
        {
            piVar3[0x7b0] = thisObj[0x7af]; // store something
        }

        // Update thisObjData with computed multiplier
        thisObjData = CONCAT44(unaff_EBP, (undefined4)thisObjData); // replace first float? but CONCAT44 combines two 32-bit values; this looks suspicious

        if (piVar3 == nullptr) {
            cVar1 = -1;
        } else {
            cVar1 = (char)piVar3[0x6e3]; // get type of piVar3
        }

        // If not penetrating and (attackerData null or flag not set) and piVar3 not melee type, scale damage
        if (((isPenetrating == '\0') &&
             ((attackerData == nullptr || (((uint)thisObj[0x238] >> 10 & 1) == 0)))) &&
            (cVar1 != '\x02') && (cVar1 != '\x03')) 
        {
            thisObjData = CONCAT44((float)thisObj[0x77b] * unaff_EBP, (undefined4)thisObjData);
        }

        // Send event? (queue damage)
        FUN_00408bb0(&DAT_0112dd94, (int)&localArray[0] + 0x3c, &damageValue, 0);

        // If logging/profiling is enabled, log damage
        cVar1 = FUN_00481660();
        if (cVar1 != '\0') {
            FUN_0084d330(); // begin logging
            FUN_0084dda0(&damageValue); // log damage value
            FUN_0070b6a0(&localFlags); // log flags?
            FUN_004a8ec0((int)&localArray[0] + 0x58); // log something else
            FUN_0084e1c0(); // end logging
        }

        // Release saved references
        if (savedPtr1 != nullptr) {
            FUN_004daf90(&savedPtr1);
        }
        if (localArray[0] != 0) {
            FUN_004daf90(localArray);
        }
    }
    return;
}