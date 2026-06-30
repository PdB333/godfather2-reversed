// FUNC_NAME: throwException
// Function at 0x0043df40: Simple helper that invokes std::_Throw to throw a C++ exception.
// Used as a generic throw wrapper by multiple call points (e.g., 0x008ea8c0, 0x0043fc60, etc.)

void __fastcall throwException(exception* ex)
{
    std::_Throw(ex);
}