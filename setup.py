import setuptools
from setuptools.command.build_ext import build_ext


MODULE = "fibonacci"
AUTHOR = "khanh"

class ClangBuildExt(build_ext):
    def build_extensions(self):
        # Set the compiler executables
        self.compiler.set_executable("compiler_so", "clang++")
        self.compiler.set_executable("compiler_cxx", "clang++")
        self.compiler.set_executable("linker_so", "clang++")
        super().build_extensions()


if __name__ == "__main__":
    setuptools.setup(
        install_requires=["cython", ],
        packages=[MODULE, ],
        zip_safe=False,
        name=MODULE,
        author=AUTHOR,
        cmdclass={"build_ext": ClangBuildExt},
        ext_modules=[
            setuptools.Extension(
                name=f"{MODULE}.wrapper",
                language="c++",
                sources=[
                    f"{MODULE}/src/fibonacci.cpp",
                    f"{MODULE}/wrapper.pyx",
                ],
                libraries=[
                    "stdc++", # for cpp compilation
                    "gmp",
                    "gmpxx",
                ],
                include_dirs=[
                    f"{MODULE}/inc",
                ],
                extra_compile_args=[
                    "-O4",
                    "-std=c++23",
                    "-march=native",
                    "-fno-math-errno",
                ],
            )
        ],

    )