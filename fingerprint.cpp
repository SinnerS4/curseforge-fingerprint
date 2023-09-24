#include <iostream>
#include <boost/iostreams/device/mapped_file.hpp>
#include <filesystem>
#include "fingerprint.h"

namespace fingerprint {

    MappedRange get_jar_contents(const std::filesystem::path& path) {
        boost::iostreams::mapped_file_source file(path.string());

        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file: " + path.string());
        }

        return {file.data(), file.data() + file.size(), file};
    }


    uint32_t compute_hash(const MappedRange& range) {
        uint32_t length = compute_normalized_length(range);
        uint32_t hash = 1U ^ length;
        uint32_t temp = 0;
        uint32_t bitCount = 0;

        for (const char* ptr = range.begin; ptr != range.end; ++ptr) {
            unsigned char byte = *ptr;
            if (!is_whitespace_character(byte)) {
                temp |= static_cast<uint32_t>(byte) << bitCount;
                bitCount += 8;
                if (bitCount == 32) {
                    uint32_t part = compute_part(temp);
                    hash = compute_hash_accumulation(hash, part);
                    temp = 0;
                    bitCount = 0;
                }
            }
        }

        if (bitCount) {
            hash = finalize_hash_with_remaining_bits(hash, temp);
        }

        return finalize_hash(hash);
    }

    uint32_t compute_part(uint32_t temp) {
        uint32_t part = temp * MULTIPLEX;
        return part ^ (part >> 24);
    }

    uint32_t compute_hash_accumulation(uint32_t hash, uint32_t part) {
        return (hash * MULTIPLEX) ^ (part * MULTIPLEX);
    }

    uint32_t finalize_hash_with_remaining_bits(uint32_t hash, uint32_t temp) {
        return (hash ^ temp) * MULTIPLEX;
    }

    uint32_t finalize_hash(uint32_t hash) {
        uint32_t finalHash = hash ^ (hash >> 13);
        finalHash *= MULTIPLEX;
        return finalHash ^ (finalHash >> 15);
    }

    uint32_t compute_normalized_length(const MappedRange& range) {
        return std::count_if(range.begin, range.end, [](unsigned char byte) {
            return !is_whitespace_character(byte);
        });
    }

    bool is_whitespace_character(unsigned char byte) {
        return std::find(WHITESPACE_CHARS.begin(), WHITESPACE_CHARS.end(), byte) != WHITESPACE_CHARS.end();
    }
}
