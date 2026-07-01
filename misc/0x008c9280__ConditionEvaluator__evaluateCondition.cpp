// FUNC_NAME: ConditionEvaluator::evaluateCondition

bool __fastcall ConditionEvaluator::evaluateCondition(int this) // ecx = this
{
    int character;
    byte flagByte;
    bool conditionMet = false;

    // Get the character object from the component at this+0x50
    character = FUN_008c74d0(*(undefined4 *)(this + 0x50)); // +0x50: component/character pointer

    // Static string table pointer (used for debug messages)
    undefined **stringTable = &PTR_LAB_00d7bf04;
    int conditionData = 0;

    if (character != 0) {
        // +0x6c: condition type (enum: 0-4)
        switch (*(undefined4 *)(this + 0x6c)) {
        case 0:
            // Check bit 4 of character flags at character+0x84
            flagByte = (byte)(*(uint *)(character + 0x84) >> 4);
            break;
        case 1:
            // Evaluate a more complex condition using FUN_008c1320 at this+0x70
            {
                int result = FUN_008c1320(this + 0x70);
                if (result == 0 || *(int *)(result + 4) != 7) {
                    goto switchDefault;
                }
                conditionMet = true;
                goto LAB_008c9349;
            }
        case 2:
            // Query another system using FUN_008c03c0 and FUN_008c59e0
            FUN_008c03c0(); // apparently no parameters
            undefined1 local_1c[8];
            int local_14;
            int local_c;
            FUN_008c59e0(local_1c, 1, 1); // fills local_1c with some structure
            int iVar1 = 0;
            if (local_14 != 0) {
                iVar1 = *(int *)(local_14 + 0x38);
                conditionData = iVar1;
            }
            conditionMet = (iVar1 != 0);
            if (local_c != 0) {
                FUN_009c8f10(local_c); // release resource
            }
            goto LAB_008c9345;
        case 3:
            // Check bit 6 (inverted) of character flags
            flagByte = ~(byte)(*(uint *)(character + 0x84) >> 6);
            break;
        case 4:
            // Check bit 9 of character flags
            flagByte = (byte)(*(uint *)(character + 0x84) >> 9);
            break;
        default:
            goto switchDefault;
        }
        // For cases 0,3,4: conditionMet = (flagByte & 1)
        conditionMet = (bool)(flagByte & 1);

LAB_008c9345:
        if (conditionMet != false) {
LAB_008c9349:
            // Set success message (from this+0x5c) and string table pointer
            undefined4 message = *(undefined4 *)(this + 0x5c); // +0x5c: success string offset
            undefined ***messageArg = &stringTable;
            goto LAB_008c936f;
        }
    }

switchDefault:
    // Set failure message (from this+100) and null argument
    undefined4 message = *(undefined4 *)(this + 100); // +0x64: failure string offset
    undefined ***messageArg = (undefined ***)0x0;

LAB_008c936f:
    // Call debug/log function with the message and argument
    local_20 = 0; // unused
    FUN_00408a00(&message, 0); // likely logs "message" with argument 0
    return conditionMet;
}