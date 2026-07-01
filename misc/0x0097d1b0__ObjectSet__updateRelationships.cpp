// FUNC_NAME: ObjectSet::updateRelationships
void __thiscall ObjectSet::updateRelationships(
    int this,                               // this pointer
    undefined4 param_2,                     // unknown parameter
    int* removeArray1, uint removeCount1,   // first removal list (offset +0x0c, count in +0x30)
    int* removeArray2, uint removeCount2,   // second removal list (offset +0x30, count in +0x54)
    int* removeArray3, uint removeCount3,   // third removal list (offset +0x54, count in +0x78)
    int* removeArray4, uint removeCount4    // fourth removal list (offset +0x78, count in +0x9c)
)
{
    uint uVar1;
    uint uVar2;
    uint uVar3;
    int* piVar4;
    int iVar5;
    int iVar6;
    int local_4;

    // Offset +0x30: count of objects in first array (array at +0x0c)
    iVar6 = *(int*)(this + 0x30);
    if (iVar6 != 0) {
        piVar4 = (int*)(this + 0x0c + iVar6 * 4); // start at end of array
        iVar5 = iVar6;
        do {
            iVar5 = iVar5 + -1;
            uVar1 = 0;
            if (removeCount1 != 0) {
                do {
                    if (*(int*)(removeArray1 + uVar1 * 4) == *piVar4) {
                        if (-1 < (int)uVar1) {
                            *(undefined4*)(removeArray1 + uVar1 * 4) = 0;
                            goto LAB_0097d21b;
                        }
                        break;
                    }
                    uVar1 = uVar1 + 1;
                } while (uVar1 < removeCount1);
            }
            // Remove from array: decrement count, swap with last element
            *(int*)(this + 0x30) = *(int*)(this + 0x30) + -1;
            if (iVar5 != *(int*)(this + 0x30)) {
                *piVar4 = *(int*)(this + 0x10 + *(int*)(this + 0x30) * 4);
            }
            // Check if all arrays are empty
            if (*(int*)(this + 0x9c) + *(int*)(this + 0x78) + *(int*)(this + 0x54) + *(int*)(this + 0x30) == 0) {
                FUN_0097c5d0(); // callback: all objects removed
            }
LAB_0097d21b:
            iVar6 = iVar6 + -1;
            piVar4 = piVar4 + -1;
        } while (iVar6 != 0);
    }

    // Repeat for second array (offset +0x54, array at +0x30)
    iVar6 = *(int*)(this + 0x54);
    if (iVar6 != 0) {
        piVar4 = (int*)(this + 0x30 + iVar6 * 4);
        local_4 = iVar6;
        do {
            local_4 = local_4 + -1;
            uVar1 = 0;
            if (removeCount2 != 0) {
                do {
                    if (*(int*)(removeArray2 + uVar1 * 4) == *piVar4) {
                        if (-1 < (int)uVar1) {
                            *(undefined4*)(removeArray2 + uVar1 * 4) = 0;
                            goto LAB_0097d2c4;
                        }
                        break;
                    }
                    uVar1 = uVar1 + 1;
                } while (uVar1 < removeCount2);
            }
            *(int*)(this + 0x54) = *(int*)(this + 0x54) + -1;
            if (local_4 != *(int*)(this + 0x54)) {
                *piVar4 = *(int*)(this + 0x34 + *(int*)(this + 0x54) * 4);
            }
            if (*(int*)(this + 0x9c) + *(int*)(this + 0x78) + *(int*)(this + 0x54) + *(int*)(this + 0x30) == 0) {
                uVar1 = 0;
                *(undefined4*)(this + 0xa0) = 0; // clear callback flag
                if (*(int*)(this + 0xdc) != 0) {
                    do {
                        // Call notification callbacks (vtable+4)
                        (**(code**)(** (int**)(*(int*)(this + 0xd8) + uVar1 * 4) + 4))();
                        uVar1 = uVar1 + 1;
                    } while (uVar1 < *(uint*)(this + 0xdc));
                }
            }
LAB_0097d2c4:
            iVar6 = iVar6 + -1;
            piVar4 = piVar4 + -1;
        } while (iVar6 != 0);
    }

    // Repeat for third array (offset +0x78, array at +0x54)
    iVar6 = *(int*)(this + 0x78);
    if (iVar6 != 0) {
        piVar4 = (int*)(this + 0x54 + iVar6 * 4);
        local_4 = iVar6;
        do {
            local_4 = local_4 + -1;
            uVar1 = 0;
            if (removeCount3 != 0) {
                do {
                    if (*(int*)(removeArray3 + uVar1 * 4) == *piVar4) {
                        if (-1 < (int)uVar1) {
                            *(undefined4*)(removeArray3 + uVar1 * 4) = 0;
                            goto LAB_0097d374;
                        }
                        break;
                    }
                    uVar1 = uVar1 + 1;
                } while (uVar1 < removeCount3);
            }
            *(int*)(this + 0x78) = *(int*)(this + 0x78) + -1;
            if (local_4 != *(int*)(this + 0x78)) {
                *piVar4 = *(int*)(this + 0x58 + *(int*)(this + 0x78) * 4);
            }
            if (*(int*)(this + 0x9c) + *(int*)(this + 0x78) + *(int*)(this + 0x54) + *(int*)(this + 0x30) == 0) {
                uVar1 = 0;
                *(undefined4*)(this + 0xa0) = 0;
                if (*(int*)(this + 0xdc) != 0) {
                    do {
                        (**(code**)(** (int**)(*(int*)(this + 0xd8) + uVar1 * 4) + 4))();
                        uVar1 = uVar1 + 1;
                    } while (uVar1 < *(uint*)(this + 0xdc));
                }
            }
LAB_0097d374:
            iVar6 = iVar6 + -1;
            piVar4 = piVar4 + -1;
        } while (iVar6 != 0);
    }

    // Fourth array (offset +0x9c, array at +0x78)
    iVar6 = *(int*)(this + 0x9c);
    if (iVar6 != 0) {
        piVar4 = (int*)(this + 0x78 + iVar6 * 4);
        local_4 = iVar6;
        do {
            local_4 = local_4 + -1;
            uVar1 = 0;
            if (removeCount4 != 0) {
                do {
                    if (*(int*)(removeArray4 + uVar1 * 4) == *piVar4) {
                        if (-1 < (int)uVar1) {
                            *(undefined4*)(removeArray4 + uVar1 * 4) = 0;
                            goto LAB_0097d44a;
                        }
                        break;
                    }
                    uVar1 = uVar1 + 1;
                } while (uVar1 < removeCount4);
            }
            *(int*)(this + 0x9c) = *(int*)(this + 0x9c) + -1;
            if (local_4 != *(int*)(this + 0x9c)) {
                *piVar4 = *(int*)(this + 0x7c + *(int*)(this + 0x9c) * 4);
            }
            if (*(int*)(this + 0x78) + *(int*)(this + 0x9c) + *(int*)(this + 0x54) + *(int*)(this + 0x30) == 0) {
                uVar1 = 0;
                *(undefined4*)(this + 0xa0) = 0;
                if (*(int*)(this + 0xdc) != 0) {
                    do {
                        (**(code**)(** (int**)(*(int*)(this + 0xd8) + uVar1 * 4) + 4))();
                        uVar1 = uVar1 + 1;
                    } while (uVar1 < *(uint*)(this + 0xdc));
                }
            }
            if (*(int*)(this + 0x9c) == 0) {
                FUN_004086d0(&DAT_0112a638); // log message
            }
LAB_0097d44a:
            iVar6 = iVar6 + -1;
            piVar4 = piVar4 + -1;
        } while (iVar6 != 0);
    }

    // Now add objects from the removal lists back (if flags allow)
    // Flag bit 0: allow add to first array
    uVar1 = 0;
    if (removeCount1 != 0) {
        do {
            iVar6 = *(int*)(removeArray1 + uVar1 * 4);
            if (iVar6 != 0) {
                if ((*(byte*)(this + 0x100) & 1) != 0) {
                    iVar5 = *(int*)(this + 0x30);
                    uVar2 = *(int*)(this + 0x78) + iVar5 + *(int*)(this + 0x9c) + *(int*)(this + 0x54);
                    if (uVar2 < 8) { // max total count check
                        uVar3 = 0;
                        if (iVar5 != 0) {
                            piVar4 = (int*)(this + 0x10);
                            do {
                                if (*piVar4 == iVar6) {
                                    if (-1 < (int)uVar3) goto LAB_0097d4ea;
                                    break;
                                }
                                uVar3 = uVar3 + 1;
                                piVar4 = piVar4 + 1;
                            } while (uVar3 < *(uint*)(this + 0x30));
                        }
                        // Add to end of first array
                        *(int*)(this + 0x10 + iVar5 * 4) = iVar6;
                        *(int*)(this + 0x30) = *(int*)(this + 0x30) + 1;
                        if ((uVar2 == 0) && (*(int*)(this + 0xdc) != 0)) {
                            uVar2 = 0;
                            do {
                                // Call notification callbacks (vtable+0)
                                (**(code**)** (undefined4**)(*(int*)(this + 0xd8) + uVar2 * 4))();
                                uVar2 = uVar2 + 1;
                            } while (uVar2 < *(uint*)(this + 0xdc));
                        }
                    }
                }
LAB_0097d4ea:
                *(undefined4*)(removeArray1 + uVar1 * 4) = 0;
            }
            uVar1 = uVar1 + 1;
        } while (uVar1 < removeCount1);
    }

    // Similar for second array (flag bit 1)
    uVar1 = 0;
    if (removeCount2 != 0) {
        do {
            iVar6 = *(int*)(removeArray2 + uVar1 * 4);
            if (iVar6 != 0) {
                if ((*(byte*)(this + 0x100) >> 1 & 1) != 0) {
                    iVar5 = *(int*)(this + 0x54);
                    uVar2 = *(int*)(this + 0x78) + iVar5 + *(int*)(this + 0x9c) + *(int*)(this + 0x30);
                    if (uVar2 < 8) {
                        uVar3 = 0;
                        if (iVar5 != 0) {
                            piVar4 = (int*)(this + 0x34);
                            do {
                                if (*piVar4 == iVar6) {
                                    if (-1 < (int)uVar3) goto LAB_0097d58c;
                                    break;
                                }
                                uVar3 = uVar3 + 1;
                                piVar4 = piVar4 + 1;
                            } while (uVar3 < *(uint*)(this + 0x54));
                        }
                        *(int*)(this + 0x34 + iVar5 * 4) = iVar6;
                        *(int*)(this + 0x54) = *(int*)(this + 0x54) + 1;
                        if ((uVar2 == 0) && (uVar2 = 0, *(int*)(this + 0xdc) != 0)) {
                            do {
                                (**(code**)** (undefined4**)(*(int*)(this + 0xd8) + uVar2 * 4))();
                                uVar2 = uVar2 + 1;
                            } while (uVar2 < *(uint*)(this + 0xdc));
                        }
                    }
                }
LAB_0097d58c:
                *(undefined4*)(removeArray2 + uVar1 * 4) = 0;
            }
            uVar1 = uVar1 + 1;
        } while (uVar1 < removeCount2);
    }

    // Third array (flag bit 2)
    uVar1 = 0;
    if (removeCount3 != 0) {
        do {
            iVar6 = *(int*)(removeArray3 + uVar1 * 4);
            if (iVar6 != 0) {
                if ((*(byte*)(this + 0x100) >> 2 & 1) != 0) {
                    iVar5 = *(int*)(this + 0x78);
                    uVar2 = *(int*)(this + 0x9c) + iVar5 + *(int*)(this + 0x54) + *(int*)(this + 0x30);
                    if (uVar2 < 8) {
                        uVar3 = 0;
                        if (iVar5 != 0) {
                            piVar4 = (int*)(this + 0x58);
                            do {
                                if (*piVar4 == iVar6) {
                                    if (-1 < (int)uVar3) goto LAB_0097d62c;
                                    break;
                                }
                                uVar3 = uVar3 + 1;
                                piVar4 = piVar4 + 1;
                            } while (uVar3 < *(uint*)(this + 0x78));
                        }
                        *(int*)(this + 0x58 + iVar5 * 4) = iVar6;
                        *(int*)(this + 0x78) = *(int*)(this + 0x78) + 1;
                        if ((uVar2 == 0) && (uVar2 = 0, *(int*)(this + 0xdc) != 0)) {
                            do {
                                (**(code**)** (undefined4**)(*(int*)(this + 0xd8) + uVar2 * 4))();
                                uVar2 = uVar2 + 1;
                            } while (uVar2 < *(uint*)(this + 0xdc));
                        }
                    }
                }
LAB_0097d62c:
                *(undefined4*)(removeArray3 + uVar1 * 4) = 0;
            }
            uVar1 = uVar1 + 1;
        } while (uVar1 < removeCount3);
    }

    // Fourth array: call FUN_0097d020 on each remaining object (destructor?)
    uVar1 = 0;
    if (removeCount4 != 0) {
        do {
            iVar6 = *(int*)(removeArray4 + uVar1 * 4);
            if (iVar6 != 0) {
                FUN_0097d020(iVar6);
                *(undefined4*)(removeArray4 + uVar1 * 4) = 0;
            }
            uVar1 = uVar1 + 1;
        } while (uVar1 < removeCount4);
    }
    // Final cleanup
    FUN_0097c890(param_2);
    return;
}