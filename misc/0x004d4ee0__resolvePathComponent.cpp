// FUNC_NAME: resolvePathComponent
// Reconstructed C++ for function at 0x004d4ee0
// This function appears to resolve a path component from an internal structure.
// It takes an output struct (param_1) and uses an input struct pointed by EAX.
// The struct has at least 4 fields: +0x00 (sourcePtr), +0x04 (flag), +0x08 (???), +0x0C (???)

struct PathComponent {
    uint32_t sourcePtr;    // +0x00: pointer to source string or buffer
    uint32_t flag;         // +0x04: non-zero indicates path resolution is needed
    uint32_t unknown1;     // +0x08
    uint32_t resultOffset; // +0x0C: maybe offset or size
};

// Forward declarations of internal functions
uint32_t internalHashFunc(uint32_t addr); // FUN_004d4e20
void memcpyInternal(uint32_t src, uint32_t size); // FUN_004d3c40

PathComponent* __fastcall resolvePathComponent(PathComponent* output) {
    // In the original assembly, the caller's struct pointer is in EAX.
    // We simulate that by using a global or passed pointer.
    // Actually, the decompiler shows in_EAX used, so we need it as a parameter.
    // But the signature has no parameters. We'll assume it's implicitly available.
    // For reconstruction, we'll add a second parameter to represent the input.
}

// However, to match the decompiled code accurately, we need to pass the input struct.
// Let's define the function as a method of a class that stores the input.
// But the decompiler shows only one parameter (param_1). So we'll treat it as a standalone function.

PathComponent* resolvePathComponent(PathComponent* output) {
    PathComponent* input; // assume this is available from some context; in assembly it's from EAX
    // To reproduce the exact logic, we'll use a global variable or register trick.
    // For clarity, we'll add it as a hidden parameter.
    return resolvePathComponentInternal(output, input);
}

// Actual implementation:
static PathComponent* resolvePathComponentInternal(PathComponent* output, PathComponent* input) {
    uint32_t uVar1;
    uint32_t uVar4;
    uint32_t uVar5;
    char* pcVar2;
    char* pcVar3;

    if (input->flag != 0) {
        pcVar2 = "\\";
        do {
            pcVar3 = pcVar2;
            pcVar2 = pcVar3 + 1;
        } while (*pcVar3 != '\0'); // pcVar3 points to the null terminator of "\\"

        uVar1 = input->sourcePtr;
        uVar4 = internalHashFunc(uVar1);
        if (uVar4 != 0) {
            do {
                uVar5 = uVar4;
                uVar4 = internalHashFunc(pcVar3 + (uVar5 - 0xe2f048));
            } while (uVar4 != 0);

            if ((uVar5 != 0) && (uVar1 < uVar5)) {
                output->resultOffset = 0;
                memcpyInternal(uVar1, uVar5 - uVar1);
                return output;
            }
        }
    }

    // If resolution fails, zero out the output struct
    output->sourcePtr = 0;
    output->flag = 0;
    output->unknown1 = 0;
    output->resultOffset = 0;
    return output;
}