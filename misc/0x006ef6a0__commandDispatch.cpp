// FUNC_NAME: commandDispatch
// Address: 0x006ef6a0
// Dispatches a command based on type field.
// The command structure is at least 4 ints: type (0,1,2), param1, param2, param3.
// param2 is an additional argument passed to all handlers.

typedef struct {
    int type;      // +0x00: command type (0,1,2)
    int param1;    // +0x04
    int param2;    // +0x08
    int param3;    // +0x0C
} Command;

extern void handleCommandType0(int param1, int param2, int extraParam, char flag);
extern void handleCommandType1(int param1, int param2, int extraParam, int param3);
extern void handleCommandType2(int param1, int param2, int extraParam, int param3);

__declspec(naked) void commandDispatch(Command* cmd, int extraParam) {
    _asm {
        push ebp
        mov ebp, esp
        push ecx
        push edx
        mov eax, [ebp+8]      // cmd
        mov ecx, [eax]        // cmd->type
        cmp ecx, 0
        je case0
        cmp ecx, 1
        je case1
        cmp ecx, 2
        je case2
        jmp done
    case0:
        // type 0: param3 cast to char
        mov eax, [ebp+8]
        mov edx, [eax+4]      // param1
        push edx
        mov edx, [eax+8]      // param2
        push edx
        mov edx, [ebp+0xC]    // extraParam
        push edx
        movsx eax, byte ptr [eax+0xC] // param3 as char
        push eax
        call handleCommandType0
        add esp, 16
        jmp done
    case1:
        // type 1
        mov eax, [ebp+8]
        mov edx, [eax+4]
        push edx
        mov edx, [eax+8]
        push edx
        mov edx, [ebp+0xC]
        push edx
        mov edx, [eax+0xC]
        push edx
        call handleCommandType1
        add esp, 16
        jmp done
    case2:
        // type 2
        mov eax, [ebp+8]
        mov edx, [eax+4]
        push edx
        mov edx, [eax+8]
        push edx
        mov edx, [ebp+0xC]
        push edx
        mov edx, [eax+0xC]
        push edx
        call handleCommandType2
        add esp, 16
        // fall through to done
    done:
        xor eax, eax          // return 0
        pop edx
        pop ecx
        pop ebp
        ret
    }
}