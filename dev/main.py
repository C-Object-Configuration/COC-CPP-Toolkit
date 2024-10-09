import sys
sys.dont_write_bytecode = True

from util import console
from test import test
from build import build
from util import path

def main() -> None:
    userInput:str = input (
        "\n- Select Script -\n"
        "\n0 | Exit"
        "\n1 | Test"
        "\n2 | Build"
        "\n3 | Clean"
        "\n\nInput: "
    )

    match userInput:
        case "0" | "Exit" | "exit":
            console.clear()

        case "1" | "Test" | "test":
            test()
            console.clear()

        case "2" | "Build" | "build":
            build()
            console.clear()

        case "3" | "Clean" | "clean":
            path.relative.remove("out")
            console.clear()

        case _:
            console.clear()
            print("--- Invalid Input ---")
            main()

    return

if __name__ == '__main__': main()