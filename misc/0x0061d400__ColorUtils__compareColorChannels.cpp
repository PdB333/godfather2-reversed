// FUNC_NAME: ColorUtils::compareColorChannels
// Function at 0x0061d400: Compares three 32-bit ARGB colors (param1, param2, param3) against a reference color (param4) and returns which one is closest.
// The comparison is done per-channel (alpha, red, green, blue) using absolute difference, then summed.
// Returns: 0 if param1 is closest, 1 if param2 is closest, 2 if param3 is closest.
// The return value is packed as: low byte = 2 (always), next byte = 0/1 for which is closer between param1 and param2, high byte = 0/1 for overall winner.

uint __cdecl compareColorChannels(uint color1, uint color2, uint color3, uint refColor)
{
    // Extract channels from reference color
    uint refBlue  = (refColor >> 16) & 0xFF;
    uint refGreen = (refColor >> 8)  & 0xFF;
    uint refRed   = refColor & 0xFF;
    
    // Extract channels from color1
    uint c1Red   = color1 & 0xFF;
    uint c1Green = (color1 >> 8) & 0xFF;
    uint c1Blue  = (color1 >> 16) & 0xFF;
    
    // Compute absolute differences for color1
    int diff1Red   = (int)(c1Red - refRed);
    int diff1Green = (int)(c1Green - refGreen);
    int diff1Blue  = (int)(c1Blue - refBlue);
    
    // Sign bits for absolute value calculation
    uint sign1Red   = diff1Red >> 31;
    uint sign1Green = diff1Green >> 31;
    uint sign1Blue  = diff1Blue >> 31;
    
    // Sum of absolute differences for color1
    int sum1 = ((sign1Red - refRed) + c1Red ^ sign1Red) +
               ((sign1Green - refGreen) + c1Green ^ sign1Green) +
               ((sign1Blue - refBlue) + c1Blue ^ sign1Blue);
    
    // Extract channels from color2
    uint c2Red   = color2 & 0xFF;
    uint c2Green = (color2 >> 8) & 0xFF;
    uint c2Blue  = (color2 >> 16) & 0xFF;
    
    // Compute absolute differences for color2
    int diff2Red   = (int)(c2Red - refRed);
    int diff2Green = (int)(c2Green - refGreen);
    int diff2Blue  = (int)(c2Blue - refBlue);
    
    uint sign2Red   = diff2Red >> 31;
    uint sign2Green = diff2Green >> 31;
    uint sign2Blue  = diff2Blue >> 31;
    
    // Sum of absolute differences for color2
    int sum2 = ((sign2Red - refRed) + c2Red ^ sign2Red) +
               ((sign2Green - refGreen) + c2Green ^ sign2Green) +
               ((sign2Blue - refBlue) + c2Blue ^ sign2Blue);
    
    // Determine which of color1 and color2 is closer
    int closer12 = sum1;
    if (sum2 < sum1) {
        closer12 = sum2;
    }
    
    // Extract channels from color3
    uint c3Red   = color3 & 0xFF;
    uint c3Green = (color3 >> 8) & 0xFF;
    uint c3Blue  = (color3 >> 16) & 0xFF;
    
    // Compute absolute differences for color3
    int diff3Red   = (int)(c3Red - refRed);
    int diff3Green = (int)(c3Green - refGreen);
    int diff3Blue  = (int)(c3Blue - refBlue);
    
    uint sign3Red   = diff3Red >> 31;
    uint sign3Green = diff3Green >> 31;
    uint sign3Blue  = diff3Blue >> 31;
    
    // Sum of absolute differences for color3
    int sum3 = ((sign3Red - refRed) + c3Red ^ sign3Red) +
               ((sign3Green - refGreen) + c3Green ^ sign3Green) +
               ((sign3Blue - refBlue) + c3Blue ^ sign3Blue);
    
    // Build return value
    // Low byte always 2 (constant)
    // Next byte: 0 if color1 is closer to ref than color2, 1 if color2 is closer
    // High byte: 0 if the closer of color1/color2 is closer than color3, 1 if color3 is closer
    uint result = 2; // Low byte = 2
    
    if (closer12 <= sum3) {
        // color1 or color2 is closer than color3
        result |= (sum2 < sum1) ? 0x100 : 0x000; // Bit 8: 0 if color1 wins, 1 if color2 wins
    } else {
        // color3 is closest
        result |= 0x200; // Bit 9 set
    }
    
    return result;
}