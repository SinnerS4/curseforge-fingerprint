#include <iostream>
#include <chrono>
#include <filesystem>
#include <stdexcept>
#include "fingerprint.h"
#include "ogfingerprint.h"

void compute_and_check_hash(const std::function<uint32_t()>& computeHash) {
    uint32_t hashValue = computeHash();
    if (hashValue != 304151306 && hashValue != 2063037149) {
        std::cout << "Hash value: " << hashValue << std::endl;
        throw std::runtime_error("Hash value is not correct.");
    }
}

void print_duration(const std::chrono::high_resolution_clock::time_point& start, size_t iterations, const std::string& type) {
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Average time for " << type << " compute_hash over " << iterations << " iterations: "
              << static_cast<double>(duration.count()) / static_cast<double>(iterations) << " ms" << std::endl;

}

void benchmark(size_t iterations, const std::function<uint32_t()> &computeHash, const std::string &type) {
    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < iterations; ++i) {
        compute_and_check_hash(computeHash);
    }
    print_duration(start, iterations, type);
}

template <typename F1, typename F2>
void benchmarkFile(size_t iterations, const std::filesystem::path& filePath, const std::string& type, F1 getContents, F2 computeHash) {
    benchmark(iterations, [&filePath, getContents, computeHash]() {
        auto content = getContents(filePath);
        return computeHash(content);
    }, type);
}

int main() {
    const auto bigFileIterations = 1;
    const auto smallFileIterations = 1000;

    const std::filesystem::path jarFilePath = "../etc/01Eyebrows - HQ.package";
    const std::filesystem::path smallJarFilePath = "../etc/Aveira_LipsN9.package";

    std::cout << "Benchmarking big file..." << std::endl;

    benchmarkFile(bigFileIterations, jarFilePath, "memory mapped", fingerprint::get_jar_contents, fingerprint::compute_hash);
    benchmarkFile(bigFileIterations, jarFilePath, "original", ogfingerprint::get_jar_contents, ogfingerprint::compute_hash);

    std::cout << std::endl;
    std::cout << "Benchmarking small file..." << std::endl;

    benchmarkFile(smallFileIterations, smallJarFilePath, "memory mapped", fingerprint::get_jar_contents, fingerprint::compute_hash);
    benchmarkFile(smallFileIterations, smallJarFilePath, "original", ogfingerprint::get_jar_contents, ogfingerprint::compute_hash);

    return 0;
}
