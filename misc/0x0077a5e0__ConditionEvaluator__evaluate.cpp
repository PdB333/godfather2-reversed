// FUNC_NAME: ConditionEvaluator::evaluate
bool __thiscall ConditionEvaluator::evaluate(int this, undefined4 param_2)
{
    char extraout_AL;
    char cVar2;
    float unaff_EBX;
    bool bVar3;
    float10 fVar4;
    
    bVar3 = false;
    switch(*(int *)(this + 4) + -4) {
    case 0: // Greater than
        (**(code **)(**(int **)(this + 8) + 4))(param_2);
        fVar4 = (float10)(**(code **)(**(int **)(this + 0xc) + 4))(param_2);
        if ((float10)unaff_EBX < fVar4) {
            return true;
        }
        break;
    case 1: // Less than
        (**(code **)(**(int **)(this + 8) + 4))(param_2);
        fVar4 = (float10)(**(code **)(**(int **)(this + 0xc) + 4))(param_2);
        if (fVar4 < (float10)unaff_EBX) {
            return true;
        }
        break;
    case 2: // Greater than or equal
        (**(code **)(**(int **)(this + 8) + 4))(param_2);
        fVar4 = (float10)(**(code **)(**(int **)(this + 0xc) + 4))(param_2);
        if ((float10)unaff_EBX <= fVar4) {
            return true;
        }
        break;
    case 3: // Less than or equal
        (**(code **)(**(int **)(this + 8) + 4))(param_2);
        fVar4 = (float10)(**(code **)(**(int **)(this + 0xc) + 4))(param_2);
        if (fVar4 <= (float10)unaff_EBX) {
            return true;
        }
        break;
    case 4: // Equal
        (**(code **)(**(int **)(this + 8) + 4))(param_2);
        fVar4 = (float10)(**(code **)(**(int **)(this + 0xc) + 4))(param_2);
        if ((float10)unaff_EBX == fVar4) {
            return true;
        }
        break;
    case 5: // Logical AND
        cVar2 = (**(code **)**(undefined4 **)(this + 8))(param_2);
        if (cVar2 == '\0') {
            return false;
        }
        goto LAB_0077a719;
    case 6: // Logical OR
        (**(code **)**(undefined4 **)(this + 8))(param_2);
        if (extraout_AL != '\0') {
            return true;
        }
LAB_0077a719:
        uVar1 = (**(code **)**(undefined4 **)(this + 0xc))(param_2);
        return (bool)uVar1;
    case 7: // Logical NOT
        cVar2 = (**(code **)**(undefined4 **)(this + 8))(param_2);
        bVar3 = cVar2 == '\0';
    default:
        return bVar3;
    }
    return false;
}