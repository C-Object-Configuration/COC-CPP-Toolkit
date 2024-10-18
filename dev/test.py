import subprocess

from util import path
from util import console
from build import build

def test() -> None:
    buildDir:str = build()
    tempDir:str = path.relative.make("dev/temp")
    staticDir:str = path.make(f"{tempDir}/static")
    dynamicDir:str = path.make(f"{tempDir}/dynamic")

    stdLib:str = "-fPIC -static -static-libgcc -static-libstdc++"
    console.command(f"g++ -c test/main.cpp -o {tempDir}/main.o -std=c++23")

    console.command(f"g++ {tempDir}/main.o {buildDir}/coc.lib -o {staticDir}/test.exe {stdLib}")
    path.relative.copy("test/main.coc", f"{staticDir}/main.coc")

    console.command(f"g++ {tempDir}/main.o {buildDir}/coc.dll -o {dynamicDir}/test.exe {stdLib}")
    path.copy(f"{buildDir}/coc.dll", f"{dynamicDir}/coc.dll")
    path.relative.copy("test/main.coc", f"{dynamicDir}/main.coc")

    console.clear()
    path.change("dev/temp/static")
    print("\nEnter to run static test")
    input()
    staticProcess = subprocess.Popen(["test.exe"])
    staticProcess.wait()

    console.clear()
    path.change("../dynamic")
    print("\nEnter to run dynamic test")
    input()
    dynamicProcess = subprocess.Popen(["test.exe"])
    dynamicProcess.wait()

    path.change(f"{path.projectDir}")
    path.remove(buildDir)
    path.remove(tempDir)
    if path.relative.isEmpty("out"):
        path.relative.remove("out")
    return