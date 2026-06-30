// FUNC_NAME: getGlobalDword
// Function address: 0x0060d890
// Role: Simple accessor returning a global 32-bit value at address 0x012058ac.
// This global is used in various parts of the game (referenced from 0x009c3fb0 and 0x009c4620).
int getGlobalDword()
{
    return *reinterpret_cast<int*>(0x012058ac);
}