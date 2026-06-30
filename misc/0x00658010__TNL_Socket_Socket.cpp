// Xbox PDB: TNL::Socket::Socket
// FUNC_NAME: Socket::Socket
// Address: 0x00658010
// Role: Socket constructor/initializer from address structure. Handles allocation and initialization based on global mode flags.

#include <cstdint>

// Forward declarations (assumed from game engine)
extern int DAT_01205a68;        // Global mode: 2 = allocate new, 1 = set from existing
extern char DAT_0120589a;       // Flag for debug logging
extern int DAT_01205a84;        // Head of debug log chain
extern int DAT_01205a80;        // Count of allocated sockets
extern int DAT_01205a7c;        // Max allowed sockets
extern int DAT_01127d38;        // Some counter
extern char DAT_01127d3c;       // Overload flag
extern int DAT_01205a30;        // Another counter

// Debug log static buffers (as used in original)
int _DAT_0122668c;              // Flags for debug log usage
char _DAT_01226680[16];         // Buffer for "Socket::Socket" (mode 2)
char _DAT_01226674[16];         // Buffer for "Socket::Socket" (mode 1)
int _DAT_01226684;              // Line number placeholder
int _DAT_01226678;              // Line number placeholder
int _DAT_01226688;              // Previous log node
int _DAT_0122667c;              // Previous log node

// External functions
void FUN_0065f6b0(void* logNode);  // Debug logging output
void FUN_0064b9e0(int size, void** outPtr);  // Memory allocation
void FUN_0064b810(int size, void** outPtr);  // Memory deallocation (free)
void FUN_0065fab0();             // Additional cleanup/update

void __fastcall Socket::Socket(uint16_t* address)  // Address structure: [port(2), ip(4)] or sockaddr_in variant
{
    char cVar2 = DAT_0120589a;
    uint16_t* local_4 = address;

    if (DAT_01205a68 == 2 && DAT_0120589a != 0) {
        // Mode 2: allocate new socket object
        if ((_DAT_0122668c & 1) == 0) {
            _DAT_0122668c |= 1;
            _DAT_01226680 = "Socket::Socket";
            _DAT_01226684 = 0xFFFFFFFF;
            _DAT_01226688 = DAT_01205a84;
            DAT_01205a84 = (int)&_DAT_01226680;
        }
        FUN_0065f6b0(&_DAT_01226680);
        DAT_01205a80++;
        if (DAT_01205a7c != 0 && DAT_01205a7c <= DAT_01205a80) {
            // Exceeded max sockets – force breakpoint
            ((void(*)())swi(3))();
            return;
        }
        // Allocate 0x20 bytes for socket object
        FUN_0064b9e0(0x20, &local_4);
        *this = (uint16_t*)local_4;  // Store allocated pointer into the this pointer (class member)
        if (DAT_01127d3c != 0 || DAT_01205a6c <= DAT_01127d38) {
            ((void(*)())swi(3))();
            return;
        }
    } else {
        // Non-allocate mode: initialize existing socket from address
        DAT_01205a30++;
        bool bVar3 = (DAT_01205a68 == 1) ? true : false;
        // Copy IP/handle from address[2] (4 bytes)
        *((uint32_t*)this) = *((uint32_t*)(address + 2));
        // Copy port from address[0] (2 bytes, extended to 32 bits)
        *((uint32_t*)this + 1) = (uint32_t)(*address);
        if (bVar3 && cVar2 != 0) {
            // Debug log for mode 1
            if ((_DAT_0122668c & 2) == 0) {
                _DAT_0122668c |= 2;
                _DAT_01226674 = "Socket::Socket";
                _DAT_01226678 = 0xFFFFFFFF;
                _DAT_0122667c = DAT_01205a84;
                DAT_01205a84 = (int)&_DAT_01226674;
            }
            FUN_0065f6b0(&_DAT_01226674);
            local_4 = (uint16_t*)*((uint32_t*)this);
            FUN_0064b810(0x20, &local_4);
            FUN_0065fab0();
        }
    }
    return;
}