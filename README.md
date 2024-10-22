# Minisys-RV C compiler

## About

Minisys-RV C compiler is a C compiler that generates Minisys-RV assembly.

## Build

To build this repository, please follow instructions in [FeignClaims/cmake_starter_template](https://github.com/FeignClaims/cmake_starter_template) and [FeignClaims/customized_conan_recipes](https://github.com/FeignClaims/customized_conan_recipes).

In a nutshell, you should clone [FeignClaims/customized_conan_recipes](https://github.com/FeignClaims/customized_conan_recipes) and add the repository to the conan remote:

```bash
git clone https://github.com/FeignClaims/customized_conan_recipes.git
conan remote add <remote_name> <remote_path>
```

After that, install llvm and conan, and then run conan and cmake as normal:

```bash
# In the repository folder
conan install . [your_args..]
cmake --preset <preset_generated_by_conan>
```

See more build details in [FeignClaims/cmake_starter_template/README_Usage](https://github.com/FeignClaims/cpp_conan_template/blob/main/README_usage.md).

## LICENSE

[UNLICENSED](LICENSE)
