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
    path = forceBackwards(projectDir + "\\" + path)

    if os.path.exists(path):
        return path

    os.mkdir(path)
    return path

def remove(path:str) -> bool:
    path = forceBackwards(projectDir + "\\" + path)

    if os.path.exists(path):
        shutil.rmtree(path)
        return True

    return False