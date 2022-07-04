from asyncio.windows_events import NULL
import os
import shutil
import sys


def clearDir(buildPath):
    """
    清空文件夹
    :param buildPath: 文件地址
    :return: void
    """
    for i in os.listdir(buildPath):
        if os.path.isdir(os.path.join(buildPath, i)):
            shutil.rmtree(os.path.join(buildPath, i))
        else:
            os.remove(os.path.join(buildPath, i))


def cmakeBuild(buildPath):
    """
    Cmake编译
    :param buildPath: 文件地址
    :return: void
    """
    os.chdir(buildPath)
    os.system("cmake .. -G \"Unix Makefiles\"")
    os.system("make")


if __name__ == "__main__":
    buildPath = "D:\\Server\\CmakeProj\\build"
    param = sys.argv[1]
    if param == "clear":
        clearDir(buildPath)
    elif param == "build":
        cmakeBuild(buildPath)