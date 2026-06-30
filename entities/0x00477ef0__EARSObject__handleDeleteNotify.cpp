// FUNC_NAME: EARSObject::handleDeleteNotify
void __thiscall EARSObject::handleDeleteNotify(int* thisPtr, int* typeId)
{
    uint uVar1;
    char cVar2;
    undefined4 uVar3;
    int iVar4;
    undefined** local_18;
    int* local_14;
    int local_10;
    int local_c;
    undefined*** local_8;
    undefined1 local_4;

    // Check if the type ID matches the expected class identifier
    if (*typeId == DAT_0120e93c) {
        // If this->someFloat > 0.0, call another function (e.g., update position)
        if (0.0 < (float)thisPtr[7]) {  // thisPtr + 0x1C
            uVar1 = thisPtr[8];         // thisPtr + 0x20
            iVar4 = FUN_009c8e50(0xc);  // Allocate 12 bytes
            if (iVar4 == 0) {
                uVar3 = 0;
            }
            else {
                uVar3 = FUN_0045ca00(thisPtr + -0xf);  // thisPtr - 0x3C
            }
            // Update some component (pos/vel?)
            FUN_00440590(thisPtr + 5, 0, (float)thisPtr[7], uVar3, (uVar1 & 2) * 2);
        }
        else {
            // Else: remove from intrusive list
            local_18 = &PTR_FUN_00e31e2c;  // Global list head pointer
            if (thisPtr == (int*)0x3c) {   // Null check via sentinel
                local_14 = (int*)0x0;
            }
            else {
                local_14 = thisPtr + 3;    // Offset to list node (thisPtr + 0xC)
            }
            local_10 = 0;
            if (local_14 != (int*)0x0) {
                // Unlink from doubly linked list
                local_10 = local_14[1];
                local_14[1] = (int)&local_14;
            }
            local_c = thisPtr[5];          // Offset 0x14
            local_8 = &local_18;
            local_4 = 0;
            FUN_00408a00(&local_c, 0);     // Notify list or manager
            FUN_0045cac0();                 // Post-removal cleanup
        }

        // Decrement reference count on the type ID
        FUN_004086d0(&DAT_0120e93c);

        // Call virtual destructor or onDelete via vtable (offset 0x8)
        (*(code**)(*thisPtr + 8))();

        // Handle global debug/memory counter
        if ((DAT_012067c4 != 0) && (cVar2 = FUN_00402080(&DAT_012067c4), cVar2 == '\0')) {
            _DAT_012067c8 = _DAT_012067c8 + 1;
            FUN_004084d0(&DAT_012067c4, 0x8000);
        }

        // If a specific flag is set in byte at offset 0x20, notify another system
        if ((*(byte*)(thisPtr + 8) & 1) != 0) {
            iVar4 = FUN_0043d0d0(thisPtr + -7, 0x137726b7, 0xffffffff);  // Find object by base-7
            if ((iVar4 == 0) &&
                (iVar4 = FUN_0043d020(0, thisPtr + -7, 0x137726b7, 0xffffffff), iVar4 != 0))
            {
                *(uint*)(iVar4 + 4) = *(uint*)(iVar4 + 4) | 1;  // Set flag in found object
            }
        }
    }
    return;
}