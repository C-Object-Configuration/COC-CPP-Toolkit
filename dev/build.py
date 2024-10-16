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

    cmd(f"g++ -c src/coc_getters.cpp -o {tempDir}/coc_getters.o -std=c++23")
    cmd(f"g++ -c src/coc_load.cpp -o {tempDir}/coc_load.o -std=c++23")
    cmd(f"g++ -c src/coc_tokenize.cpp -o {tempDir}/coc_tokenize.o -std=c++23")
    cmd(f"ar rvs {outDir}/coc.lib {tempDir}/coc_getters.o {tempDir}/coc_load.o {tempDir}/coc_tokenize.o")

    path.remove(tempDir)
    return outDir