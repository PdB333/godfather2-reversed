// FUNC_NAME: InputManager::updateControllerSlot
void __thiscall InputManager::updateControllerSlot(ControllerManager* controllerMgr, uint slotIndex) {
    uint uVar8;
    int iVar1;
    int iVar6;
    bool bVar3;
    byte bVar4;
    char cVar5;
    byte *pbVar7;
    byte *pbVar9;
    undefined4 *puVar10;
    undefined4 *puVar11;
    undefined4 *puVar12;
    undefined4 local_4;

    // Extract a byte from the upper part of 'this' pointer (likely input data)
    bVar3 = false;
    local_4._3_1_ = (byte)((uint)this >> 0x18);
    bVar4 = local_4._3_1_;
    local_4 = (uint)local_4._3_1_ << 0x18;

    if (0xf < slotIndex) {
        return;
    }

    // Slot structure at controllerMgr + 0x14 + slotIndex * 0x18 (each 0x18 bytes)
    ControllerSlot* slot = reinterpret_cast<ControllerSlot*>(controllerMgr + 0x14 + slotIndex * 0x18);
    if (slot == nullptr) {
        return;
    }

    if (slot->name[0] != '\0') {
        // Check if bit 3 of flags is set (value 0x8)
        if ((slot->flags & 8) != 0) {
            if (slot->counter < g_FrameCounter) {
                slot->flags &= 0xfffffff7;  // Clear bit 3
                slot->field_0x10 = 0;
                slot->counter = 0;
            } else {
                cVar5 = slot->field_0x10;
                local_4 = CONCAT22(CONCAT11(bVar4, cVar5), CONCAT11(cVar5, cVar5));
            }
        }

        // If bit 1 NOT set and bit 0 IS set
        if (((slot->flags & 2) == 0) && ((slot->flags & 1) != 0)) {
            puVar10 = nullptr;
            puVar11 = reinterpret_cast<undefined4*>(slot->pLinkedList);
            if (slot->pLinkedList != nullptr) {
                do {
                    iVar1 = FUN_00444e70();  // Some function (returns 2 for a condition)
                    if (iVar1 == 2) {
                        if (slot->pLinkedList == puVar11) {
                            slot->pLinkedList = reinterpret_cast<ListNode*>(*puVar11);
                        } else {
                            *puVar10 = *puVar11;
                        }
                        puVar12 = reinterpret_cast<undefined4*>(*puVar11);
                        *puVar11 = *(undefined4*)(controllerMgr + 0x2d8);  // Free list head at controllerMgr+0x2d8
                        *(undefined4**)(controllerMgr + 0x2d8) = puVar11;
                        puVar11 = puVar10;
                    } else {
                        bVar3 = true;
                        if ((slot->flags & 4) == 0) {  // Check bit 2 of flags
                            pbVar7 = reinterpret_cast<byte*>(&local_4);
                            pbVar9 = reinterpret_cast<byte*>(puVar11 + 1);  // Node data at offset 4
                            iVar1 = 3;
                            do {
                                if (*pbVar7 < *pbVar9) {
                                    *pbVar7 = *pbVar9;
                                }
                                pbVar9 = pbVar9 + 1;
                                pbVar7 = pbVar7 + 1;
                                iVar1 = iVar1 + -1;
                            } while (iVar1 != 0);
                        }
                        puVar12 = reinterpret_cast<undefined4*>(*puVar11);
                    }
                    puVar10 = puVar11;
                    puVar11 = puVar12;
                } while (puVar12 != nullptr);

                if (bVar3) goto LAB_00444894;
            }
            slot->flags &= 0xfffffffe;  // Clear bit 0
            FUN_00444db0();  // Related function
        }
    }

LAB_00444894:
    iVar6 = reinterpret_cast<int>(g_pInputManager);
    cVar5 = FUN_00410af0();  // Is a controller active? (returns non-zero if so)
    if (cVar5 != '\0') {
        uVar8 = slotIndex & 0xff;
        if (((char)slotIndex == *(char*)(iVar6 + 0x53d)) && (*(byte*)(iVar6 + 0x568) != 0x12)) {
            uVar8 = (uint)*(byte*)(iVar6 + 0x568);
        }
        iVar1 = iVar6 + uVar8 * 0x44;
        if (*(char*)(iVar1 + 0x6a) != '\0') {
            *(undefined1*)(iVar1 + 0x6b) = reinterpret_cast<byte*>(&local_4)[1];
            *(undefined1*)(iVar1 + 0x6c) = reinterpret_cast<byte*>(&local_4)[2];
        }
    }
    return;
}