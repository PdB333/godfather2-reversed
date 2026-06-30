// FUNC_NAME: ScriptVM::dispatchInstruction
// Address: 0x00633640
// Role: Advanced opcode handler for bytecode interpreter (EARS script VM)
// Offsets: this+8 = flags (bit0 = halted?), this+0x14 = instructionCount (?), this-0x10 = contextFlags, this-0x18 = codeSegment ptr

int __thiscall ScriptVM::dispatchInstruction(uint param_1)
{
    uint uVar1;
    int *piVar2;
    int iVar4;
    uint uVar5;

    // Check if halted or instruction count <= 0, and context not in special state
    if ((((*(byte *)(this + 8) & 1) != 0) || (*(int *)(this + 0x14) < 1)) &&
       ((*(byte *)(this - 0x10) & 1) == 0)) {
        piVar2 = (int *)(this - 0x18);
        if ((*(uint *)(this - 0x10) & 1) == 0) {
            if ((*(uint *)(this - 0x10) & 2) != 0) {
                *(undefined4 *)(this - 0xc) = **(undefined4 **)(this - 8);
            }
            // Compute instruction index from code segment
            iVar4 = (*(int *)(this - 0xc) - *(int *)(*(int *)(*(int *)(*piVar2 + -4) + 0xc) + 0xc) >> 2) + -1;
        } else {
            iVar4 = -1;
        }
        // Fetch instruction word from code array
        uVar1 = *(uint *)(*(int *)(*(int *)(*(int *)(*piVar2 + -4) + 0xc) + 0xc) + iVar4 * 4);
        uVar5 = uVar1 & 0x3f;
        // Opcodes 0x19 and 0x1a are special (e.g., call/branch)
        if ((uVar5 == 0x19) || (uVar5 == 0x1a)) {
            return executeSpecialOpcode(piVar2, (int)uVar1 >> 0x18, param_1);
        }
    }
    return 0;
}