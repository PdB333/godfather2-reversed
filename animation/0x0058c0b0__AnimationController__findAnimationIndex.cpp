// FUNC_NAME: AnimationController::findAnimationIndex
int AnimationController::findAnimationIndex(void* param_1, float param_2)
{
    code* pcVar1;
    float* pfVar2;
    float fVar3;
    int iVar4;
    int iVar5;
    int* piVar6;
    int iVar7;
    
    fVar3 = param_2;
    iVar4 = (int)*(short*)(*(int*)((int)param_2 + 4) + 4);
    if (((-1 < iVar4) && (iVar4 < DAT_01205574)) &&
       (pcVar1 = *(code**)(DAT_01205570 + 4 + iVar4 * 0xc), pcVar1 != (code*)0x0)) {
      (*pcVar1)(param_1,iVar4,&param_2);
    }
    iVar7 = (int)*(char*)((int)fVar3 + 1);
    iVar5 = 0;
    iVar4 = iVar5;
    if ((iVar7 != 0) && (iVar4 = 0, 0 < iVar7)) {
      piVar6 = (int*)((int)fVar3 + 0xc);
      do {
        pfVar2 = *(float**)(*piVar6 + 8);
        if (((pfVar2 != (float*)0x0) && (*pfVar2 <= param_2)) &&
           (iVar4 = iVar5, param_2 <= pfVar2[1])) {
          return iVar5;
        }
        iVar5 = iVar5 + 1;
        piVar6 = piVar6 + 1;
      } while (iVar5 < iVar7);
    }
    return iVar4;
}