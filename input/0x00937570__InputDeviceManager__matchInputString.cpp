// FUNC_NAME: InputDeviceManager::matchInputString
// Function address: 0x00937570
// Role: Checks if a given input path string matches either a hardcoded button path or a dynamically generated control path.
//       If matched, triggers a virtual callback and returns 1; otherwise returns 0.

int __thiscall InputDeviceManager::matchInputString(int* thisPtr, byte* inputString)
{
    byte bVar1;
    byte* pbVar2;
    int cmpResult;
    byte* pbVar4;
    bool bVar5;
    undefined4 stackVar_4c;
    undefined4 stackVar_48;
    undefined1 stackVar_44;
    byte formattedPath[64];

    // Compare inputString against hardcoded button path "/fopt/buttons/button_2/button"
    cmpResult = 0x1e; // length of string? Actually used as loop counter
    bVar5 = true;
    pbVar2 = (byte*)"/fopt/buttons/button_2/button";
    pbVar4 = inputString;
    do {
        if (cmpResult == 0) break;
        cmpResult = cmpResult + -1;
        bVar5 = *pbVar2 == *pbVar4;
        pbVar2 = pbVar2 + 1;
        pbVar4 = pbVar4 + 1;
    } while (bVar5);
    if (bVar5) {
        // Call virtual function at offset 0x2c (likely onButtonPressed or similar)
        (*(code**)(*thisPtr + 0x2c))();
        // Set up some stack variables and call a function (maybe string copy or event dispatch)
        stackVar_4c = DAT_01130310; // global string constant
        stackVar_48 = 0;
        stackVar_44 = 0;
        FUN_00408a00(&stackVar_4c, 0);
        return 1;
    }

    // Format a control path using index stored at this+0x50 (thisPtr[0x14])
    FUN_00910160(formattedPath, "/fopt/content/control_%d/item", thisPtr[0x14]);

    // Compare formattedPath against inputString (two bytes at a time, likely for performance)
    pbVar2 = formattedPath;
    do {
        bVar1 = *pbVar2;
        bVar5 = bVar1 < *inputString;
        if (bVar1 != *inputString) {
LAB_00937606:
            cmpResult = (1 - (uint)bVar5) - (uint)(bVar5 != 0);
            goto LAB_0093760b;
        }
        if (bVar1 == 0) break;
        bVar1 = pbVar2[1];
        bVar5 = bVar1 < inputString[1];
        if (bVar1 != inputString[1]) goto LAB_00937606;
        pbVar2 = pbVar2 + 2;
        inputString = inputString + 2;
    } while (bVar1 != 0);
    cmpResult = 0;

LAB_0093760b:
    if (cmpResult == 0) {
        // Match found for dynamic control path
        FUN_009372f0();
        return 1;
    }
    return 0;
}