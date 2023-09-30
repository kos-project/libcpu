# libcpu

Freestanding cross-architecture API for managing CPUs.

This library can be compiled against a freestanding GCC/MinGW or Clang environment and aids the developer in things like fetching information about the system processor and its features, as well as initializing it accordingly.

### Compatibility

Currently, the following CPU architectures are planned/being worked on/supported:

| Architecture | Version | Status | Supported Extensions                                                       |
| ------------ | ------- | ------ | -------------------------------------------------------------------------- |
| x86          | 1.0.0   | 🚧     | x87, MMX, SSE, SSE2, POPCNT                                                |
| x86_64       | 1.0.0   | 🚧     | x97, MMX, SSE, SSE2, SSE3, SSSE3, SSE4.1, SSE4.2, SSE4a, AVX, AVX2, POPCNT |
| arm (sf/hf)  | n/a     | ⌛      | n/a                                                                        |
| arm64        | n/a     | ⌛      | n/a                                                                        |
| riscv        | n/a     | ⌛      | n/a                                                                        |
| riscv64      | n/a     | ⌛      | n/a                                                                        |

### Building

In order to build libcpu, you only need a compatible C compiler which supports C23. No standard library is required at all. When you have cloned the repository, you can configure the project by running the following command:

```shell
cmake -S . -B cmake-build-debug -DCMAKE_BUILD_TYPE=Debug -DCPU_BUILD_TESTS=ON
```

When the project is configured successfully, you can build the library and the associated unit tests by running the following command:

```shell
cmake --build cmake-build-debug [--target cpu-tests]
```

You can leave out the `--target` flag if you only need the library itself and not its test(s).
