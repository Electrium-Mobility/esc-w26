#include "sample_file.h"

bool bitstream_parity_valid(uint8_t *bitstream, uint32_t length,
                            bool parity_bit, bitstream_parity_E scheme) {
    // Guard against NULL bitstream
    if (bitstream == NULL) {
        return false;
    }

    uint32_t total_ones = 0;

    // Outer Loop: Accumulate the number of bits in each byte in the bitstream
    for (size_t i = 0; i < length; ++i) {
        uint8_t ones = 0;
        // Inner Loop: Count the number of bits in a byte
        for (size_t j = 0; j < 8; ++j) {  // byte & j = bit at byte[j] 
            ones += (bitstream[i] & (1 << j)) >> j;
        }

        total_ones += ones;
    }

    // Correct 
    uint8_t total_ones_is_even = (total_ones % 2 == 0);

    // Handle the given scheme and Compare the calculated parity bit to the given parity_bit 
    if (scheme == BITSTREAM_PARITY_EVEN) {
        return (total_ones_is_even ? (parity_bit == 0) : (parity_bit == 1));
    } else if (scheme == BITSTREAM_PARITY_ODD) {
        return (total_ones_is_even ? (parity_bit == 1) : (parity_bit == 0));
    }

    return false;
}