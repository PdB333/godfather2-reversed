// FUNC_NAME: randomWeightedChoice
bool randomWeightedChoice(float weightA, float weightB)
{
    uint uVar1;
    uint uVar2;
    uint uVar3;
    
    uVar3 = 0;
    // Normalize weightA to a probability between 0 and 1
    weightA = weightA / (weightA + weightB);
    uVar2 = 0;
    // Loop through a table of random thresholds (DAT_010c2678 & DAT_012054b4 are likely a random seed/state)
    while ((uVar1 = DAT_010c2678 & DAT_012054b4, DAT_012054b4 = DAT_012054b4 + 1,
            weightA < *(float *)(&DAT_010c2680 + uVar1 * 4) ||
            weightA == *(float *)(&DAT_010c2680 + uVar1 * 4) || (uVar3 = uVar3 + 1, uVar3 < 2))) {
        uVar2 = uVar2 + 1;
        if (2 < uVar2) {
            return false;
        }
    }
    return true;
}