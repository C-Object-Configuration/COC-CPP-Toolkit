from util import path
from util.console import command as cmd
from datetime import datetime

def build() -> str:
    time:str = ""

    for c in str(datetime.now()):
        if c.isnumeric():
            time += c
        else:
            time += "-"

    path.relative.make("out")
    outDir:str = path.relative.make(f"out/{time}")

    tempDir:str = path.relative.make("dev/temp")
    proj:str = path.projectDir

    cmd(f"g++ -c src/etcl.cpp -o {tempDir}/etcl.o -std=c++23")
    cmd(f"ar rvs {outDir}/etcl.lib {tempDir}/etcl.o")

    path.remove(tempDir)
    return outDir