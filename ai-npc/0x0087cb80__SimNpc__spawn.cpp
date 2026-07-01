// FUNC_NAME: SimNpc::spawn

undefined1 __thiscall SimNpc::spawn(SimNpc *npc, SpawnData *spawnData, undefined4 arg3, undefined4 arg4, undefined4 arg5)
{
    char cVar1;
    undefined4 uVar2;
    SpawnData *piVar3;
    char unaff_retaddr;
    undefined1 auStack_24 [20];
    int aiStack_10 [3];
    SpawnData *piStack_4;
    
    uVar2 = arg5;
    cVar1 = validateSpawnData(spawnData, arg3, arg4, arg5);
    if (cVar1 == '\0') {
        return 0;
    }
    arg4 = 0;
    cVar1 = (**(code **)(*spawnData + 0x10))(0x383225a1, &arg4);
    piVar3 = spawnData;
    if ((cVar1 != '\0') && (piVar3 = piStack_4, spawnData != (SpawnData *)0x0)) {
        initFromSpawnData(spawnData);
        npc->spawned = 0;                              // +0x287 (int flag)
        addToWorld(1);                                   // +0x288 (byte?) maybe world handle
        npc->byte288 = 0;                                // +0x288
        if ((npc->flags322 | 4U) != npc->flags322) {    // +0x322 bit2 (0x4)
            (**(code **)(npc->someObjPtr + 0x28))(0x10); // +0x16 pointer to some TNL object
            npc->flags322 = npc->flags322 | 4;
        }
        npc->someGlobalPtr = (int)&DAT_008755c0;         // +0x56 pointer to global data
        uVar2 = getEntityID(spawnData);                   // +0x7b5? spawnData offset
        setEntityID(npc, uVar2);                          // +0x2e4? npc offset
        constructAnimationRequest(&stack0xffffffd0, 0);   // local stack struct
        if ((((uint)npc->flags322 >> 9 & 1) == 0) && (npc->flags2e4 != spawnData->spawnFlags)) {
            registerWithManager();                        // +0x7b5? offset in spawnData
            uVar2 = 0x4875b42e;
            if (((uint)npc->flags322 >> 0xf & 1) == 0) {
                if ((char)spawnData->byte84c != '\0') {  // +0x84c*4? huge offset maybe spawnData
                    uVar2 = 0xddb7685f;
                }
            }
            else {
                uVar2 = 0xcf826fcc;
                playSound(0x2f);                          // sound index
            }
            resetAnimation(0);
            loadAnimation(spawnData, 1);                  // 1 = maybe load from spawnData
            playAnimation(uVar2, auStack_24);            // uVar2 is hash, auStack_24 is anim request
            if (aiStack_10[0] != 0) {
                destroyAnimationState(aiStack_10);        // destructor for local object
            }
        }
        if ((npc->flags322 | 0x200U) != npc->flags322) { // bit9 (0x200)
            (**(code **)(npc->someObjPtr + 0x28))(0x10);
            npc->flags322 = npc->flags322 | 0x200;
        }
        if (unaff_retaddr == '\0') {                      // maybe a flag from spawnData
            constructAnimationRequest(&stack0xffffffd0, 0);
            goto LAB_0087cd7b;
        }
        constructAnimationRequest(&stack0xffffffd0, 0);
        piVar3 = piStack_4;
        uVar2 = arg3;
    }
    piStack_4 = piVar3;
    if (unaff_retaddr != '\0') {
        (**(code **)(*npc + 0x210))(0, uVar2);           // vtable calls: maybe reloadAI
        (**(code **)(*npc + 0x1cc))(uVar2);
        (**(code **)(*npc + 0x210))(piVar3, uVar2);
    }
LAB_0087cd7b:
    if (_DAT_00d577a0 < (float)npc->someTimer) {         // +0x38b float/time
        *(int *)(npc->healthBarPtr + 8) = npc->someTimer; // +0xe0 pointer, offset 8
    }
    notifySpawnComplete(piStack_4);                       // +0x7b5? actually piStack_4 is spawnData
    return 1;
}