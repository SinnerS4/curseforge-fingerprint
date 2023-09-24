#include <iostream>
#include <vector>
#include "ogfingerprint.h"

namespace ogfingerprint {

    Buffer get_jar_contents(const std::filesystem::path& jar_file_path) {
        std::ifstream jar_file(jar_file_path, std::ios::binary | std::ios::ate);

        if (!jar_file.is_open()) {
            return Buffer();
        }

        std::streamsize size = jar_file.tellg();
        jar_file.seekg(0, std::ios::beg);

        Buffer buffer(size);
        if (!jar_file.read(reinterpret_cast<char*>(buffer.data()), size)) {
            std::cerr << "Failed to load " << jar_file_path << std::endl;
        }

        return buffer;
    }

    uint32_t compute_hash(Buffer& buffer) {
        const uint32_t multiplex = 1540483477;
        const uint32_t length = buffer.size();
        uint32_t num1 = length;

        num1 = compute_normalized_length(buffer);

        uint32_t num2 = (uint32_t)1 ^ num1;
        uint32_t num3 = 0;
        uint32_t num4 = 0;

        for (uint32_t index = 0; index < length; ++index) {

            unsigned char b = buffer[index];

            if (!is_whitespace_character(b)) {
                num3 |= (uint32_t)b << num4;
                num4 += 8;
                if (num4 == 32) {
                    uint32_t num6 = num3 * multiplex;

                    uint32_t num7 = (num6 ^ num6 >> 24) * multiplex;

                    num2 = num2 * multiplex ^ num7;
                    num3 = 0;
                    num4 = 0;
                }
            }
        }

        if (num4 > 0) {
            num2 = (num2 ^ num3) * multiplex;
        }

        uint32_t num6 = (num2 ^ num2 >> 13) * multiplex;

        return num6 ^ num6 >> 15;
    }

    uint32_t compute_normalized_length(Buffer& buffer) {
        int32_t num1 = 0;
        const uint32_t length = buffer.size();

        for (uint32_t index = 0; index < length; ++index) {
            if (!is_whitespace_character(buffer[index])) {
                ++num1;
            }
        }

        return num1;
    }

    bool is_whitespace_character(char b) {
        return b == 9 || b == 10 || b == 13 || b == 32;
    }

}