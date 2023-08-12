import subprocess, sys
from pathlib import Path

DIR = Path(__file__).parent.absolute()

def build():
    # cmd = "cmake -B build ; cmake --build build --config=Release"
    cmake_config = ["cmake", "-B", "build"]
    cmake_build = ["cmake", "--build", "build", "--config=Release"]
    subprocess.run(cmake_config, check=True, cwd=DIR, stdout=sys.stdout, stderr=sys.stderr)
    subprocess.run(cmake_build, check=True, cwd=DIR, stdout=sys.stdout, stderr=sys.stderr)

def setup():
    subprocess.run(["python","setup.py","bdist_wheel","sdist"], check=True, cwd=DIR, stdout=sys.stdout, stderr=sys.stderr)
    subprocess.run(["pip","install","--force-reinstall","dist/mymod-0.0.0-cp310-cp310-win_amd64.whl"], check=True, cwd=DIR, stdout=sys.stdout, stderr=sys.stderr)

def run():
    subprocess.run(["python","./python/test_mymod.py"], check=True, cwd=DIR, stdout=sys.stdout, stderr=sys.stderr)


if __name__ == "__main__":
    build()
    run()
    if len(sys.argv) > 1 and sys.argv[1] == "setup":
        setup()