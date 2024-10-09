import subprocess

def command(cmd:str) -> bool:
    try:
        result = subprocess.run(cmd, shell=True, check=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        print(f"Command: ({cmd}) ->\n{result.stdout.decode()}")
        return True

    except subprocess.CalledProcessError as e:
        print(f"Command: ({cmd}) ->\n{e.stderr.decode()}")
        return False