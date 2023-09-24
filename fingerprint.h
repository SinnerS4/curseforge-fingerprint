#pragma once

#include <vector>
#include <filesystem>
#include <boost/iostreams/device/mapped_file.hpp>

namespace fingerprint {

    constexpr uint32_t MULTIPLEX = 1540483477;
    constexpr std::array<char, 4> WHITESPACE_CHARS = {9, 10, 13, 32};

    // Define the MappedRange struct to hold the memory-mapped file and its range.
    struct MappedRange {
        const char* begin;
        const char* end;
        boost::iostreams::mapped_file_source file; // hold the file object to ensure it's kept alive
    };

    // Function to get the contents of a jar file.
    MappedRange get_jar_contents(const std::filesystem::path& jar_file_path);

    // Function to compute the hash of a given buffer.
    uint32_t compute_hash(const MappedRange& range);

    // Function to compute the normalized length of a buffer (i.e., excluding whitespace characters).
    uint32_t compute_normalized_length(const MappedRange& range);

    // Check if a character is a whitespace character.
    bool is_whitespace_character(unsigned char b);

    // Compute a part of the hash with the provided temporary value.
    uint32_t compute_part(uint32_t temp);

    // Accumulate the hash value with the provided hash and part values.
    uint32_t compute_hash_accumulation(uint32_t hash, uint32_t part);

    // Finalize the hash value with any remaining bits in the temporary value.
    uint32_t finalize_hash_with_remaining_bits(uint32_t hash, uint32_t temp);

    // Finalize the overall hash computation.
    uint32_t finalize_hash(uint32_t hash);

}