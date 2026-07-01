// FUNC_NAME: AICondition::evaluate
// Function at 0x00777a20: Dispatcher for AI condition evaluation based on opcode.
// Evaluates various conditions using member fields and external functions.
// param_2, param_3, param_5 are additional parameters depending on opcode.
// Returns 0 (false) or 1 (true) or result of sub-condition.

#include <cstdint>

class AICondition {
public:
    // Offsets:
    // +0x30: float m_healthOrTimer? (compared in cases 7,9)
    // +0x38: uint32_t m_flags (bitmask, manipulated in case 0xf)
    // +0x50: int m_somePtr? (dereferenced +0x860 in case 0x11)
    // +0x5c: int* m_anotherPtr? (dereferenced +0x1f58 in case 0xe)
    // +0x70: int m_stateId? (checked in case 0xd)
    // +0xa4: float m_threshold? (used in cases 1-3)
    // +0xac: uint32_t m_conditionFlags (bitfield, checked in cases 5,0xf,0x11)

    uint8_t evaluate(int param2, uint32_t param3, int opcode, uint32_t param5) {
        uint8_t result = 0;
        switch (opcode - 0x12) {
        case 0: // opcode 0x12
            result = checkConditionType0();
            return result;
        case 1:
        case 2:
        case 3: { // opcodes 0x13-0x15: distance/threshold check
            float f = static_cast<float>(param2);
            if (param2 < 0) {
                f += DAT_00e44578; // global adjustment
            }
            if (*(float*)(this + 0xa4) < f * DAT_00d5efb8) {
                return true;
            }
            break;
        }
        case 4: // opcode 0x16
            result = checkConditionType4(param2);
            return result;
        case 5: { // opcode 0x17: complex flag check
            if ((*(uint32_t*)(this + 0xac) >> 5 & 1) == 0) {
                return true;
            }
            int state = checkSomeState();
            if (state == 0) {
                return false;
            }
            uint8_t alt = checkAnotherState();
            goto LAB_00777b25;
        }
        case 6: // opcode 0x18
            result = checkConditionType6();
            return result;
        case 7: // opcode 0x19: compare float at +0x30 with global
            if (*(float*)(this + 0x30) <= DAT_00d6826c) {
                return false;
            }
            return true;
        case 8: // opcode 0x1a
            result = checkConditionType8(param2);
            return result;
        case 9: // opcode 0x1b: compare float at +0x30 with another global
            if (*(float*)(this + 0x30) <= DAT_00d577a0) {
                return false;
            }
            return true;
        case 10: { // opcode 0x1c
            uint8_t globalCond = checkGlobalCondition();
LAB_00777b25:
            if (globalCond == 0) {
                result = evaluateAlternateCondition();
                return result;
            }
            break;
        }
        case 0xb: { // opcode 0x1d
            uint8_t globalCond = checkGlobalCondition();
            if (globalCond != 0) {
                result = evaluateAlternateCondition();
                return result;
            }
            break;
        }
        case 0xc: // opcode 0x1e
        case 0x10: // opcode 0x22
            result = checkGlobalCondition();
            return result;
        case 0xd: { // opcode 0x1f: state ID check
            if (*(int*)(this + 0x70) != 0) {
                return *(int*)(this + 0x70) == 0x48;
            }
            return true;
        }
        case 0xe: // opcode 0x20: bit test from indirect pointer
            return (uint8_t)((*(uint32_t*)(*(int*)(this + 0x5c) + 0x1f58) >> 13) & 1);
        case 0xf: { // opcode 0x21: flag manipulation
            uint32_t mask = getFlagMask();
            if ((*(uint32_t*)(this + 0xac) >> 10 & 1) != 0) {
                *(uint32_t*)(this + 0x38) &= ~mask;
                return false;
            }
            uint8_t hasFlag = (mask & *(uint32_t*)(this + 0x38)) != 0;
            if (hasFlag) {
                *(uint32_t*)(this + 0x38) &= ~mask;
                return true;
            }
            break;
        }
        case 0x11: { // opcode 0x23: compare bit with function result
            uint8_t bitVal = (uint8_t)((*(uint32_t*)(this + 0xac) >> 1) & 1);
            int ptr = *(int*)(this + 0x50) + 0x860;
            uint8_t funcResult;
            if (*(int*)(this + 0x70) != 0) {
                funcResult = checkBitFunction(ptr);
            } else {
                funcResult = checkBitFunction(ptr);
            }
            return bitVal != funcResult;
        }
        default:
            result = defaultConditionEvaluator(param2, param3, opcode, param5);
        }
        return result;
    }

private:
    // External functions (stubs - actual implementations elsewhere)
    uint8_t checkConditionType0();
    uint8_t checkConditionType4(int param);
    uint8_t checkConditionType6();
    uint8_t checkConditionType8(int param);
    uint8_t checkGlobalCondition();
    uint8_t evaluateAlternateCondition();
    uint32_t getFlagMask();
    int checkSomeState();
    uint8_t checkAnotherState();
    uint8_t checkBitFunction(int ptr);
    uint8_t defaultConditionEvaluator(int p2, uint32_t p3, int op, uint32_t p5);

    // Global constants (from data)
    static constexpr float DAT_00e44578 = 0.0f; // placeholder
    static constexpr float DAT_00d5efb8 = 1.0f; // placeholder
    static constexpr float DAT_00d6826c = 0.0f; // placeholder
    static constexpr float DAT_00d577a0 = 0.0f; // placeholder
};