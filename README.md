# Curseforge Fingerprint

Curseforge Fingerprint is a PoC of using memory mapped files to improve performance of fingerprint library

## Prerequisites

- CMake (Version 3.26 or higher)
- C++ Compiler supporting C++17 standard
- Boost library with `iostreams` component (Version 1.83.0 or higher)

## Setting Up the Project

1. **Cloning the Repository:**

   If you have the source in a Git repository, start by cloning the repository. If not, just navigate to the project directory.

    ```bash
    git clone git@github.com:SinnerS4/curseforge-fingerprint.git
    cd curseforge_fingerprint
    ```

2. **Installing Dependencies:**

   You will need to have the Boost library installed. Depending on your system, you can use a package manager or manually download and install it.

    - For **Ubuntu/Debian**:

        ```bash
        sudo apt-get install libboost-iostreams-dev
        ```

    - For **Fedora**:

        ```bash
        sudo dnf install boost-iostreams
        ```

    - For **Mac** using **Homebrew**:

        ```bash
        brew install boost
        ```

    - For **Windows**, you might want to consider using [vcpkg](https://github.com/microsoft/vcpkg) or downloading Boost directly from the [official website](https://www.boost.org/users/download/).

3. **Configuring and Building with CMake:**

   Create a new directory for the build and navigate into it:

    ```bash
    mkdir build
    cd build
    ```

   Now configure the project with CMake. For a **Debug build**, use:

    ```bash
    cmake -DCMAKE_BUILD_TYPE=Debug ..
    ```

   And for a **Release build**, use:

    ```bash
    cmake -DCMAKE_BUILD_TYPE=Release ..
    ```

   Now build the project:

    ```bash
    cmake --build .
    ```

   This will create an executable named `curseforge_fingerprint` in the `build` directory.

4. **Running the Project:**

    ```bash
    ./curseforge_fingerprint
    ```

## Contributing

If you wish to contribute to this project, kindly refer to the contribution guidelines (if any) or contact the maintainer.
