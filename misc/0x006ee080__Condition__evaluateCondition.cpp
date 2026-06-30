// FUNC_NAME: Condition::evaluateCondition

struct Condition {
    int type;        // +0x00: 0=bool, 1=int, 2=float
    int leftOpA;     // +0x04: left sub-condition operand A
    int leftOpB;     // +0x08: left sub-condition operand B
    int rightOpA;    // +0x0C: right sub-condition operand A
    int rightOpB;    // +0x10: right sub-condition operand B
};

// Helper functions (addresses from Ghidra):
// bool compareBool(int opA, int opB, int context)       @ 0x006ebff0
// int  compareInt(int opA, int opB, int context)        @ 0x006eb7b0
// float compareFloat(int opA, int opB, int context)     @ 0x006eb7c0

bool evaluateCondition(Condition* cond, int context) {
    int type = cond->type;
    if (type == 0) {
        bool leftResult = (bool)FUN_006ebff0(cond->leftOpA, cond->leftOpB, context);
        bool rightResult = (bool)FUN_006ebff0(cond->rightOpA, cond->rightOpB, context);
        if (leftResult && rightResult) {
            return true;
        }
    } else if (type == 1) {
        int leftResult = FUN_006eb7b0(cond->leftOpA, cond->leftOpB, context);
        int rightResult = FUN_006eb7b0(cond->rightOpA, cond->rightOpB, context);
        if (leftResult != 0) {
            if (rightResult != 0) {
                return true;
            }
            return false;
        }
    } else if (type == 2) {
        float leftResult = (float)FUN_006eb7c0(cond->leftOpA, cond->leftOpB, context);
        float rightResult = (float)FUN_006eb7c0(cond->rightOpA, cond->rightOpB, context);
        // _DAT_00d577a0 is a global float constant (likely 0.0f or epsilon)
        if (leftResult != 0.0f && rightResult != _DAT_00d577a0) {
            return true;
        }
    }
    return false;
}