// FUNC_NAME: EAudioEmitter::updateAudioState

void __fastcall EAudioEmitter::updateAudioState(int thisObj)
{
    int *piVar1;
    undefined4 uVar2;
    int iVar3;
    undefined4 *puVar4;
    undefined4 local_70;
    undefined4 local_6c;
    undefined4 local_68;
    undefined4 uStack_64;
    float local_60;
    float local_5c;
    float local_58;
    undefined4 local_54;
    undefined4 auStack_50[5];
    undefined4 uStack_3c;
    undefined4 uStack_28;
    undefined4 uStack_20;
    undefined4 uStack_1c;
    undefined4 uStack_18;
    undefined4 uStack_14;

    if (*(int *)(thisObj + 0x1fc) == 0)   // mIsStreaming/mIsMoving flag (0 = moving source, 1 = static/streaming)
    {
        // Compute magnitude of position vector, scaled by audio distance scale
        local_60 = SQRT(*(float *)(thisObj + 0x180) * *(float *)(thisObj + 0x180) +
                        *(float *)(thisObj + 0x184) * *(float *)(thisObj + 0x184) +
                        *(float *)(thisObj + 0x188) * *(float *)(thisObj + 0x188)) * DAT_00e2cd54;
        local_54 = DAT_00e2b1a4;   // zero constant

        // Copy target position (listener or sound destination)
        local_70 = *(undefined4 *)(thisObj + 0x1b0);
        local_6c = *(undefined4 *)(thisObj + 0x1b4);
        local_68 = *(undefined4 *)(thisObj + 0x1b8);

        // Compute magnitude of velocity vector
        local_5c = SQRT(*(float *)(thisObj + 0x190) * *(float *)(thisObj + 0x190) +
                        *(float *)(thisObj + 0x194) * *(float *)(thisObj + 0x194) +
                        *(float *)(thisObj + 0x198) * *(float *)(thisObj + 0x198)) * DAT_00e2cd54;

        // Compute magnitude of acceleration vector
        local_58 = SQRT(*(float *)(thisObj + 0x1a0) * *(float *)(thisObj + 0x1a0) +
                        *(float *)(thisObj + 0x1a4) * *(float *)(thisObj + 0x1a4) +
                        *(float *)(thisObj + 0x1a8) * *(float *)(thisObj + 0x1a8)) * DAT_00e2cd54;

        // Get thread-local storage (likely pointer to audio manager)
        TlsGetValue(DAT_01139810);

        // Allocate a 0x30 byte message object (type 0x27)
        iVar3 = FUN_00aa2680(0x30, 0x27);
        uVar2 = _DAT_00ef3a9c;
        *(undefined2 *)(iVar3 + 4) = 0x30;   // store size in header

        // Encode the three magnitudes into the message payload
        puVar4 = (undefined4 *)FUN_00a66df0(&local_60, uVar2);
        uStack_20 = local_70;
        uStack_1c = local_6c;
        piVar1 = *(int **)(thisObj + 0x200);   // mpAudioProxy (vtable pointer)
        uStack_18 = local_68;
        uStack_14 = DAT_00e2b1a4;

        if (piVar1 != (int *)0x0)
        {
            // Transform world position to something (maybe camera space)
            FUN_004b59d0(thisObj + 0x180, auStack_50);
            (**(code **)(*piVar1 + 0xc))(puVar4);   // virtual function call (play/update?)
            FUN_004c2060();   // cleanup
            FUN_009f17c0(auStack_50);   // free transformed data
            goto LAB_004c1ddd;
        }

        FUN_004b59d0(thisObj + 0x180, auStack_50);
    }
    else
    {
        // For non-moving/streaming sources: only position magnitude is needed
        TlsGetValue(DAT_01139810);
        iVar3 = FUN_00aa2680(0x20, 0x27);
        *(undefined2 *)(iVar3 + 4) = 0x20;

        puVar4 = (undefined4 *)FUN_00a64b00(
            SQRT(*(float *)(thisObj + 0x188) * *(float *)(thisObj + 0x188) +
                 *(float *)(thisObj + 0x184) * *(float *)(thisObj + 0x184) +
                 *(float *)(thisObj + 0x180) * *(float *)(thisObj + 0x180)) *
            DAT_00e2cd54);

        local_70 = *(undefined4 *)(thisObj + 0x1b0);
        local_6c = *(undefined4 *)(thisObj + 0x1b4);
        local_68 = *(undefined4 *)(thisObj + 0x1b8);
        uStack_64 = 0;

        if (*(int **)(thisObj + 0x200) != (int *)0x0)
        {
            (**(code **)(**(int **)(thisObj + 0x200) + 0xc))(puVar4);
            FUN_004c2060();
            FUN_009f1820(&local_70, 0);
            goto LAB_004c1ddd;
        }

        FUN_0045cbe0();
        auStack_50[0] = DAT_00e2b1a4;
        uStack_3c = DAT_00e2b1a4;
        uStack_28 = DAT_00e2b1a4;
        uStack_20 = local_70;
        uStack_1c = local_6c;
        uStack_18 = local_68;
        uStack_14 = uStack_64;
    }

    // Common path for both branches when the proxy is null
    TlsGetValue(DAT_01139810);
    iVar3 = FUN_00aa2680(0x160, 0x31);   // allocate larger message (type 0x31)
    *(undefined2 *)(iVar3 + 4) = 0x160;
    FUN_009f0c70(puVar4, auStack_50, 0x3e3);   // post event with id 0x3e3
    FUN_004c2060();
    FUN_0043b490();
    FUN_009f01f0(0x2001, thisObj, 0);   // register/update something

LAB_004c1ddd:
    // Decrement reference count and possibly delete
    if ((*(short *)(puVar4 + 1) != 0) &&   // offset +4? (assuming pointer arithmetic on undefined4*)
        (*(short *)((int)puVar4 + 6) = *(short *)((int)puVar4 + 6) + -1,
         *(short *)((int)puVar4 + 6) == 0))
    {
        (**(code **)*puVar4)(1);   // vtable destructor/release
    }
    return;
}