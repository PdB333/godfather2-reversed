// FUNC_NAME: UnknownClass::evaluateAttractivenessForRivalCrimeAttacks
int* __thiscall evaluateAttractivenessForRivalCrimeAttacks(byte* thisEntityFlags, int* target, int* optionalTarget2, int* optionalTarget3)
{
    int* result;
    char isValid;
    int checkResult;
    int* componentPtr;
    long double vtableCheck;

    // First branch: check if optionalTarget3 is valid and passes visibility/bit checks
    if (optionalTarget3 != nullptr &&
        (((*thisEntityFlags & 1) != 0 ||  // +0x00 bit 0 = always visible check
        (vtableCheck = (long double)(**(code**)(*optionalTarget3 + 0xc0))(), // virtual function at vtable+0xC0 (e.g., isVisible)
        (long double)0.0 < vtableCheck)) &&
        (target != nullptr) &&
        ((*thisEntityFlags & 1) != 0 ||
        (vtableCheck = (long double)(**(code**)(*target + 0xc0))(), (long double)0.0 < vtableCheck)))) &&
        
        // Check crime flags at thisEntityFlags+0x14
        ((((thisEntityFlags[0x14] >> 2 & 1) != 0 &&  // +0x14 bit 2 = crimeType1 flag
          (checkResult = FUN_006c9470(optionalTarget3, 0x383225a1), checkResult != 0)) || // check if target has component with GUID 0x383225a1
         
         ((((thisEntityFlags[0x14] >> 4 & 1) != 0 &&  // +0x14 bit 4 = crimeType2 flag
           (checkResult = FUN_006bc8d0(optionalTarget3, 0x369ac561), checkResult != 0)) && // check if target has component with GUID 0x369ac561
          ((componentPtr = (int*)FUN_006bc8b0(optionalTarget3), componentPtr == nullptr ||
           ((isValid = FUN_006eb940(), isValid == '\0' ||
            (isValid = (**(code**)(*componentPtr + 0x1c))(0x100), isValid == '\0')))))))) ||  // virtual call at vtable+0x1C with param 0x100 (e.g., isAlive)
        
         (((thisEntityFlags[0x15] & 1) != 0 &&  // +0x15 bit 0 = additional crime flag
          ((((checkResult = FUN_006bc8d0(optionalTarget3, 0x369ac561), checkResult != 0 &&
             (componentPtr = (int*)FUN_006bc8b0(optionalTarget3), componentPtr != nullptr)) &&
            (isValid = FUN_006eb940(), isValid != '\0')) &&
           (isValid = (**(code**)(*componentPtr + 0x1c))(0x100), isValid != '\0')))))) {
        return optionalTarget3;
    }

    // Second branch: check if target is valid
    if (target != nullptr &&
        ((*thisEntityFlags & 1) != 0 ||
        (vtableCheck = (long double)(**(code**)(*target + 0xc0))(), (long double)0.0 < vtableCheck))) {
        
        // Check creation flags at target+0x14 bit 1
        if ((thisEntityFlags[0x14] >> 1 & 1) != 0) {
            result = nullptr;
            isValid = (**(code**)(*target + 0x10))(0x383225a1, &result); // virtual call at vtable+0x10 with component GUID
            componentPtr = result;
            if (((isValid != '\0') && (result != nullptr)) &&
               ((checkResult = FUN_007ff880(), checkResult == 0 && (((uint)componentPtr[0x238] >> 4 & 1) == 0)))) { // +0x8E0 check
                return target;
            }
        }

        // Check creation flags at target+0x14 bit 2
        if ((thisEntityFlags[0x14] >> 2 & 1) != 0) {
            result = nullptr;
            isValid = (**(code**)(*target + 0x10))(0x383225a1, &result);
            if ((((isValid != '\0') && (result != nullptr)) && (checkResult = FUN_007ff880(), checkResult != 0)) &&
               (isValid = FUN_00690150(4), isValid == '\0')) {
                return target;
            }
        }

        // Check creation flags at target+0x14 bit 3
        if ((thisEntityFlags[0x14] >> 3 & 1) != 0) {
            result = nullptr;
            isValid = (**(code**)(*target + 0x10))(0x369ac561, &result);
            componentPtr = result;
            if ((((isValid != '\0') && (result != nullptr)) &&
                ((checkResult = FUN_007ff880(), checkResult == 0 && (isValid = FUN_00690150(4), isValid == '\0'))))) {
                componentPtr = (int*)FUN_006bc8b0(componentPtr);
                if (componentPtr == nullptr) {
                    return target;
                }
                isValid = FUN_006eb940();
                if (isValid == '\0') {
                    return target;
                }
                isValid = (**(code**)(*componentPtr + 0x1c))(0x100);
                if (isValid == '\0') {
                    return target;
                }
            }
        }

        // Check creation flags at target+0x14 bit 7 (signed check)
        if ((signed char)thisEntityFlags[0x14] < '\0') {
            result = nullptr;
            isValid = (**(code**)(*target + 0x10))(0x369ac561, &result);
            componentPtr = result;
            if ((((isValid != '\0') && (result != nullptr)) &&
                ((checkResult = FUN_007ff880(), checkResult == 0 &&
                 ((((isValid = FUN_00690150(4), isValid == '\0' &&
                    (componentPtr = (int*)FUN_006bc8b0(componentPtr), componentPtr != nullptr)) &&
                   (isValid = FUN_006eb940(), isValid != '\0')) &&
                  (isValid = (**(code**)(*componentPtr + 0x1c))(0x100), isValid != '\0')))))) {
                return target;
            }
        }
    }

    // Third branch: check if optionalTarget2 is valid
    if (((((thisEntityFlags[0x14] >> 5 & 1) == 0) || (optionalTarget2 == nullptr)) ||
        (((*thisEntityFlags & 1) == 0 &&
         (vtableCheck = (long double)(**(code**)(*optionalTarget2 + 0xc0))(), vtableCheck <= (long double)0)))) &&
       (((((thisEntityFlags[0x14] >> 6 & 1) == 0 || (optionalTarget2 == nullptr)) ||
         (((*thisEntityFlags & 1) == 0 &&
          (vtableCheck = (long double)(**(code**)(*optionalTarget2 + 0xc0))(), vtableCheck <= (long double)0)))) ||
        ((optionalTarget3 != nullptr && (checkResult = FUN_006c9470(optionalTarget3, 0x383225a1), checkResult != 0)))))) {
        return (int*)0x0;
    }

    return optionalTarget2;
}