import sys
sys.dont_write_bytecode = True

import util.directory as dir
from util.command import command as cmd

def buildTest() -> None:
    dir.make("build/temp")
    dir.make("build/out")

    proj:str = dir.projectDir

    stdVersion:str = "-std=c++23"
    stdLib:str = "-fPIC -static -static-libgcc -static-libstdc++"

    cmd(f"g++ -c src/etcl.cpp -o build/temp/etcl.o {stdVersion}")
    cmd(f"ar rvs build/temp/etcl.lib build/temp/etcl.o")

    cmd(f"g++ -c test/main.cpp -o build/temp/main.o {stdVersion}")
    cmd(f"g++ build/temp/main.o build/temp/etcl.lib -o build/out/test.exe {stdLib}")

    dir.remove("build/temp")
    return

def main() -> None:
    return

if __name__ == '__main__': main()