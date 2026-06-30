// FUNC_NAME: NodePair::connectNodes
void __thiscall NodePair::connectNodes(void* param2, int param3) {
    // param2 is another NodePair (or related object)
    // Call virtual method at vtable offset 0x94 on the sub-object at this+0x1c,
    // which is treated as an instance of param2's class.
    // param3 is passed as the argument.
    (*(void(__thiscall**)(int))(*(int*)param2 + 0x94))((int)this + 0x1c, param3);

    // Call virtual method at vtable offset 0x94 on the sub-object at this+0x1d,
    // which is treated as an instance of this's class.
    // param2 is passed as the argument.
    (*(void(__thiscall**)(void*))(*(int*)this + 0x94))((int)this + 0x1d, param2);

    // Call virtual method at vtable offset 0x80 on param2 (using param2's vtable? no, it uses this's vtable but param2 is the 'this')
    // Actually the third call uses (**(code **)(*param_1 + 0x80))(param_2, param_1 + 0x1c, param_1 + 0x1d, unaff_retaddr, param_2);
    // This is a virtual call on this-vtable with param2 as first argument (this) and then the two sub-objects and an unaff_retaddr.
    // The last argument is param2 again, likely a decompiler artifact.
    (*(void(__thiscall**)(void*, void*, void*, int))(*(int*)this + 0x80))(
        param2,                          // this pointer for the called method
        (void*)((int)this + 0x1c),      // sub-object A
        (void*)((int)this + 0x1d),      // sub-object B
        0,                               // placeholder for unaff_retaddr (likely bogus)
        param2                           // duplicate param2, may be ignored
    );
}