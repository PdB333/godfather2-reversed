//FUNC_NAME: ConditionNode::isConditionMet

class ConditionNode {
public:
    // +0x04: Condition type (0-0xC)
    int m_conditionType;
    // +0x08: First operand object (has vtable with virtual function at offset 8)
    void* m_operand1;
    // +0x0C: Second operand object (may be null)
    void* m_operand2;

    // Virtual function at vtable+8 returns an integer status (0,1,2,...)
    typedef int (__thiscall* GetStatusFunc)(void*);

    bool isConditionMet() {
        int status1 = 0;
        int status2 = 0;

        // Get status from first operand (always present)
        if (m_operand1) {
            GetStatusFunc func = *(GetStatusFunc*)(*(int*)m_operand1 + 8);
            status1 = func(m_operand1);
        }

        // Get status from second operand (may be null)
        if (m_operand2) {
            GetStatusFunc func = *(GetStatusFunc*)(*(int*)m_operand2 + 8);
            status2 = func(m_operand2);
        }

        // Evaluate based on condition type
        switch (m_conditionType) {
        case 0: case 1: case 2: case 3:
        case 4: case 5: case 6: case 7: case 8:
            // AND condition: both operands must have status == 1
            if (status1 == 1 && status2 == 1) {
                return true;
            }
            break;

        case 9: case 10:
            // Alternative AND: both operands must have status == 2
            if (status1 == 2 && status2 == 2) {
                return true;
            }
            break;

        case 0xB:
            // Single operand check: first operand must have status == 2
            return status1 == 2;

        case 0xC:
            // Always false
            break;

        default:
            break;
        }

        return false;
    }
};