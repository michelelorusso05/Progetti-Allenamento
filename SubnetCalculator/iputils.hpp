#include <string>
#include <iostream>

namespace IPUtils
{
    const uint8_t E_INVALID_OCTECTS = 0;
    const uint8_t E_INVALID_OCT_VAL = 1;
    const uint8_t E_INVALID_CIDR_VAL = 2;
    const uint8_t E_IP_NOT_NET = 3;
    const uint8_t E_INVALID_SUBNET = 4;

    uint32_t IPBitmaskFromString(std::string input) noexcept(false)
    {
        uint8_t foundDots = 0;

        uint8_t firstIndex = 0;

        uint32_t current;
        uint32_t bitmask = 0;

        // Final delimiter for last octect (to avoid 0-sized last substring)
        input.append(" ");
        for (uint8_t i = 0; i < input.length(); i++)
        {
            if ((input[i] == '.') ^ (i == (input.length() - 1)))
            {
                foundDots++;

                current = std::atoi(input.substr(firstIndex, i - firstIndex).c_str());

                if (current > 255)
                    throw E_INVALID_OCT_VAL;

                bitmask = bitmask << 8;
                bitmask |= current;

                firstIndex = i + 1;
            }
        }

        if (foundDots != 4)
            throw E_INVALID_OCTECTS;

        return bitmask;
    }
    std::string formattedIPFromBitmask(uint32_t ip)
    {
        std::string formattedIP;

        for (int i = 3; i >= 0; i--)
        {
            formattedIP.append(std::to_string((ip >> (8 * i)) & 255));
            if (i != 0)
                formattedIP.append(".");
        }

        return formattedIP;
    }
    // While /30 is technically valid, only 1 host per subnet is pretty useless.
    bool checkMask(uint8_t cidr)
    {
        return (cidr > 1 && cidr < 30);
    }
    // Masks are the opposite of what you'd expect: 0s are for net bits and 1s for host bits;
    // This is done to simplify bitwise operations.
    uint32_t maskFromCIDR(uint8_t cidr)
    {
        return (1 << (32 - cidr)) - 1;
    }
    bool checkIfNet(uint32_t ip, uint8_t cidrMask) noexcept(false)
    {
        if (!checkMask(cidrMask))
            throw E_INVALID_CIDR_VAL;

        uint32_t mask = maskFromCIDR(cidrMask);
        return (mask & ip) == 0;
    }
    uint32_t defaultGatewayFromIP(uint32_t bitmask)
    {
        return bitmask + 1;
    }
    uint32_t broadcastFromIP(uint32_t bitmask, uint8_t mask)
    {
        return bitmask | maskFromCIDR(mask);
    }
}