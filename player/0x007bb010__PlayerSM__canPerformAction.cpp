//FUNC_NAME: PlayerSM::canPerformAction
// Address: 0x007bb010
// Role: Determines if a given action (param_4) can be performed based on current player state.
// Returns 1 if allowed, 0 otherwise. If allowed, stores the action ID at this+0x78.

char __thiscall PlayerSM::canPerformAction(int this, int param_2, int param_3, int actionId, int param_5)
{
    int *piVar1;
    byte bVar2;
    char cVar3;
    char result;
    int iVar5;
    int iVar6;
    uint uVar7;
    int animId;
    bool bVar9;
    float10 fVar10;
    float fVar11;
    int stateIndex;
    int stateType;
    char local_5;
    int local_4;

    result = '\0';
    animId = 0;
    local_5 = '\0';
    local_4 = 0;

    switch(actionId - 0x13) {
    case 0: // actionId == 0x13
        return '\0';

    case 1: // actionId == 0x14
        getCurrentState(&local_4, &local_5); // FUN_007ba420
        if (local_5 != '\x02') {
            bVar9 = local_5 == '\x03';
            if (!bVar9) goto LAB_007bb087;
        }
        // fall through to case 3

    case 3: // actionId == 0x16
        stateType = 0;
        stateIndex = 3;
LAB_007bb075:
        stateIndex = getActionState(stateIndex); // FUN_00798f50
        result = checkActionAvailability(stateIndex, stateType); // FUN_007badc0
LAB_007bb087:
        cVar3 = isPlayerAlive(); // FUN_00481640
        if (cVar3 != '\0') {
            result = checkActionCooldown(actionId, 0xffffffff); // FUN_007bad30
        }
        break;

    case 2: // actionId == 0x15
        getCurrentState(&local_4, &local_5); // FUN_007ba420
        if ((local_5 == '\x01') || (local_5 == '\x04')) goto switchD_007bb035_caseD_3;
        if (local_5 == '\0') {
            bVar9 = local_4 == 2;
            goto LAB_007bb070;
        }
        goto LAB_007bb087;

    case 4: // actionId == 0x17
        getCurrentState(&local_4, &local_5); // FUN_007ba420
        if ((local_5 != '\x02') && (local_5 != '\x03')) goto LAB_007bb087;
        stateType = 1;
        stateIndex = 4;
        goto LAB_007bb075;

    case 5: // actionId == 0x18
        getCurrentState(&local_4, &local_5); // FUN_007ba420
        if (((local_5 != '\x01') && (local_5 != '\x04')) && ((local_5 != '\0' || (local_4 != 2))))
            goto LAB_007bb087;
        // fall through to case 6

    case 6: // actionId == 0x19
        stateType = 1;
        stateIndex = 4;
        goto LAB_007bb075;

    case 7: // actionId == 0x1A
        animId = getGlobalFlags(); // FUN_007ab160
        result = ((byte)*(undefined4 *)(animId + 4) & 2) != 2;
        break;

    case 8: // actionId == 0x1B
        bVar2 = (byte)*(undefined2 *)(this + 0x90); // flags field
        if (((bVar2 >> 2 & 1) == 0) && ((bVar2 >> 3 & 1) == 0)) {
            return '\0';
        }
        goto LAB_007bb42d;

    case 9: // actionId == 0x1C
        result = isPlayerInVehicle(); // FUN_00481660
        if (result != '\0') {
            return '\0';
        }
        result = isPlayerAlive(); // FUN_00481640
        if (result != '\0') {
            return '\0';
        }
        if (*(int *)(this + 0x188) == 0) { // currentAnimationId
            return '\0';
        }
        if (*(int *)(this + 0x188) == 0x48) {
            return '\0';
        }
        if ((*(byte *)(this + 0x90) & 1) == 0) { // flags bit 0
            return '\0';
        }
        if (*(int *)(this + 0x188) != 0) {
            animId = *(int *)(this + 0x188) + -0x48;
        }
        setAnimation(animId); // FUN_00716b80
        result = getAnimationComponent(*(undefined4 *)(this + 0x58)); // FUN_009af6f0
        if (animId == 0) {
            return '\0';
        }
        piVar1 = *(int **)(this + 0x58);
        stateIndex = 0x30000;
        fVar10 = (float10)(**(code **)(*piVar1 + 0x214))(0x30000); // vtable call
        fVar11 = (float)fVar10;
        fVar10 = (float10)(**(code **)(*piVar1 + 0x218))(fVar11); // vtable call
        cVar3 = checkAnimationBlend(animId, (float)fVar10, fVar11, stateIndex); // FUN_00798880
        if (cVar3 != '\0') {
            return '\0';
        }
        if (*(int *)(this + 0x188) == 0) {
            animId = 0;
        }
        else {
            animId = *(int *)(this + 0x188) + -0x48;
        }
        fVar10 = (float10)(**(code **)(**(int **)(this + 0x58) + 0x218))(); // vtable call
        cVar3 = checkAnimationTransition(animId, (float)fVar10); // FUN_007f81c0
        if (cVar3 == '\0') {
            return '\0';
        }
        cVar3 = isInputPressed(5); // FUN_00690150
        if (cVar3 != '\0') {
            return '\0';
        }
        if (result == '\0') {
            return '\0';
        }
        stateType = 0;
        stateIndex = 3;
        goto LAB_007bb26d;

    case 10: // actionId == 0x1D
        result = isPlayerInVehicle(); // FUN_00481660
        if (result != '\0') {
            return '\0';
        }
        result = isPlayerAlive(); // FUN_00481640
        if (result != '\0') {
            return '\0';
        }
        if (*(int *)(this + 0x188) == 0) {
            return '\0';
        }
        if (*(int *)(this + 0x188) == 0x48) {
            return '\0';
        }
        if ((*(byte *)(this + 0x90) & 1) == 0) {
            return '\0';
        }
        if (*(int *)(this + 0x188) != 0) {
            animId = *(int *)(this + 0x188) + -0x48;
        }
        setAnimation(animId); // FUN_00716b80
        result = getAnimationComponent(*(undefined4 *)(this + 0x58)); // FUN_009af6f0
        if (animId == 0) {
            return '\0';
        }
        piVar1 = *(int **)(this + 0x58);
        stateIndex = 0x30000;
        fVar10 = (float10)(**(code **)(*piVar1 + 0x214))(0x30000);
        fVar11 = (float)fVar10;
        fVar10 = (float10)(**(code **)(*piVar1 + 0x218))(fVar11);
        cVar3 = checkAnimationBlend(animId, (float)fVar10, fVar11, stateIndex); // FUN_00798880
        if (cVar3 != '\0') {
            return '\0';
        }
        if (*(int *)(this + 0x188) == 0) {
            animId = 0;
        }
        else {
            animId = *(int *)(this + 0x188) + -0x48;
        }
        fVar10 = (float10)(**(code **)(**(int **)(this + 0x58) + 0x218))();
        cVar3 = checkAnimationTransition(animId, (float)fVar10); // FUN_007f81c0
        if (cVar3 == '\0') {
            return '\0';
        }
        cVar3 = isInputPressed(5); // FUN_00690150
        if (cVar3 != '\0') {
            return '\0';
        }
        if (result == '\0') {
            return '\0';
        }
        stateType = 1;
        stateIndex = 4;
LAB_007bb26d:
        stateIndex = getActionState(stateIndex); // FUN_00798f50
        result = checkActionAvailability(stateIndex, stateType); // FUN_007badc0
        break;

    case 0xB: // actionId == 0x1E
        if (*(int *)(this + 0x188) == 0) {
            return '\0';
        }
        if (*(int *)(this + 0x188) == 0x48) {
            return '\0';
        }
        if ((*(byte *)(this + 0x90) & 1) == 0) {
            return '\0';
        }
        if (*(int *)(this + 0x188) != 0) {
            animId = *(int *)(this + 0x188) + -0x48;
        }
        result = isInCombat(); // FUN_007f47a0
        if (result == '\0') {
            return '\0';
        }
        iVar5 = getCurrentTarget(); // FUN_007ab690
        if (iVar5 != 0) {
            if (*(int *)(this + 0x188) == 0) {
                iVar5 = 0;
            }
            else {
                iVar5 = *(int *)(this + 0x188) + -0x48;
            }
            iVar6 = getCurrentTarget(); // FUN_007ab690
            if (iVar5 != iVar6) goto LAB_007bb42d;
        }
        result = isPlayerInVehicle(); // FUN_00481660
        if (result == '\0') {
            return '\0';
        }
        if (*(int *)(animId + 0x1ef4) != *(int *)(*(int *)(this + 0x58) + 0x1ef4)) {
            return '\0';
        }
LAB_007bb42d:
        *(int *)(this + 0x78) = actionId; // store current action
        return '\x01';

    case 0xC: // actionId == 0x1F
        result = checkSomeCondition(); // FUN_007b9ee0
        break;

    case 0xD: // actionId == 0x20
        result = isPlayerAlive(); // FUN_00481640
        if (result == '\0') {
            return '\0';
        }
        result = isInputPressed(0x3d); // FUN_00690150
        if (((result == '\0') && (result = isInputPressed(0x3e), result == '\0')) &&
           (result = isInputPressed(0x3f), result == '\0')) {
            return '\0';
        }
        *(int *)(this + 0x78) = actionId;
        return '\x01';

    case 0xE: // actionId == 0x21
        result = isPlayerAlive(); // FUN_00481640
        if (result == '\0') {
            return '\0';
        }
        uVar7 = getInputState(); // FUN_006252d0
        result = checkActionCooldown(uVar7 & 0x3ffffff, uVar7 >> 0x1a); // FUN_007bad30
        break;

    default:
        result = defaultActionCheck(param_2, param_3, actionId, param_5); // FUN_007ab790
    }

    if (result != '\0') {
        *(int *)(this + 0x78) = actionId;
    }
    return result;
}