import subprocess

from util import path
from util import console
from build import build

def test() -> None:
    libDir:str = build()
    tempDir:str = path.relative.make("dev/temp")

    stdLib:str = "-fPIC -static -static-libgcc -static-libstdc++"
    console.command(f"g++ -c test/main.cpp -o {tempDir}/main.o -std=c++23")
    console.command(f"g++ {tempDir}/main.o {libDir}/etcl.lib -o {tempDir}/test.exe {stdLib}")
    console.clear()

    process = subprocess.Popen([f"{tempDir}/test.exe"])
    process.wait()

    path.remove(libDir)
    path.remove(tempDir)
    if path.relative.isEmpty("out"):
        path.relative.remove("out")
    return