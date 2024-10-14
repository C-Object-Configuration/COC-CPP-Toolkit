import os
import sys
import shutil

def forceForwards(path:str) -> str:
    new:str = ""

    for char in path:
        match char:
            case "\\": new += "/"
            case _: new += char

    return new

def forceBackwards(path:str) -> str:
    new:str = ""

    for char in path:
        match char:
            case "/": new += "\\"
            case _: new += char

    return new

def getUpper(source:str, index:int) -> str:
    source = forceBackwards(source)

    upper:str = ""
    forwards:int = 0

    for char in source:
        if char == "\\":
            forwards += 1

    for char in source:
        if char == "\\":
            if forwards == index:
                return upper
            forwards -= 1

        upper += char

    return upper

projectDir:str = forceForwards(getUpper(os.path.realpath(sys.argv[0]), 2))

def make(path:str) -> str:
    path = forceBackwards(path)

    if os.path.exists(path):
        return path

    os.mkdir(path)
    return path

def remove(path:str) -> bool:
    path = forceBackwards(path)

    if os.path.exists(path):
        shutil.rmtree(path)
        return True

    return False

def copy(src:str, dst:str) -> None:
    src = forceForwards(src)
    dst = forceForwards(dst)

    dst = dst[len(projectDir)+1:]
    shutil.copy(src, dst)

def isDir(path:str) -> bool:
    return os.path.isdir(forceBackwards(path))

def isFile(path:str) -> bool:
    return os.path.exists(path) and not isDir(path)

def isEmpty(path:str) -> bool:
    path = forceBackwards(path)

    if isFile(path):
        return True

    return len(os.listdir(path)) == 0

class relative:
    @staticmethod
    def make(path:str) -> str:
        return globals()["make"](f"{projectDir}/{path}")

    @staticmethod
    def remove(path:str) -> bool:
        return globals()["remove"](f"{projectDir}/{path}")

    @staticmethod
    def copy(src:str, dst:str) -> None:
        globals()["copy"](f"{projectDir}/{src}", f"{projectDir}/{dst}")

    @staticmethod
    def isDir(path:str) -> bool:
        return globals()["isDir"](f"{projectDir}/{path}")

    @staticmethod
    def isFile(path:str) -> bool:
        return globals()["isFile"](f"{projectDir}/{path}")

    @staticmethod
    def isEmpty(path:str) -> bool:
        return globals()["isEmpty"](f"{projectDir}/{path}")