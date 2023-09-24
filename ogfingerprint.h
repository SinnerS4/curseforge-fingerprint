#include <iostream>
#include <vector>
#include <cstdint>
#include <fstream>
#include <filesystem>

namespace ogfingerprint {
    typedef std::vector<unsigned char> Buffer;
    void print_usage();
    Buffer get_jar_contents(const std::filesystem::path& jar_file_path);
    uint32_t compute_hash(Buffer& buffer);
    bool is_whitespace_character(char b);
    uint32_t compute_normalized_length(Buffer& buffer);
}
