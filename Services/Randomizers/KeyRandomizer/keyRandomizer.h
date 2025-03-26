#ifndef SERVICES_RANDOMIZER_KEY_H
#define SERVICES_RANDOMIZER_KEY_H

#include "../../../Infrastructure/Config/servicesConfig.h"

class KeyRandomizer
{
public:
    static string generateRandomKey(size_t length = 512)
    {
        const string charset =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz"
            "!@#$%^&*()_+-=[]{}|;:,.<>?~";

        random_device rd;
        mt19937 generator(rd());
        uniform_int_distribution<size_t> distribution(0, charset.size() - 1);

        string key;
        key.reserve(length);

        for (size_t i = 0; i < length; i++) { key += charset[distribution(generator)]; }

        return key;
    }
};

#endif