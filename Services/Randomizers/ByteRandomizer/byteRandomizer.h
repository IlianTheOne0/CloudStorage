#ifndef SERVICES_RANDOMIZERS_BYTE_H
#define SERVICES_RANDOMIZERS_BYTE_H

#include "../../../Infrastructure/Config/servicesConfig.h"

class ByteRandomizer
{
public:
    static pair<array<uint8_t, 256>, array<uint8_t, 256>> generateSBox()
    {
        array<uint8_t, 256> sbox;
        array<uint8_t, 256> inverse_sbox;

        for (int i = 0; i < 256; i++) { sbox[i] = static_cast<uint8_t>(i); }

        random_device rd;
        mt19937 gen(rd());
        for (int i = 255; i > 0; i--)
        {
            uniform_int_distribution<int> dist(0, i);
            int j = dist(gen);
            swap(sbox[i], sbox[j]);
        }

        for (int i = 0; i < 256; i++) { inverse_sbox[sbox[i]] = static_cast<uint8_t>(i); }

        return { sbox, inverse_sbox };
    }
};

#endif