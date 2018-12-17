cmake_minimum_required(VERSION 3.12)
project(project1)

set(CMAKE_CXX_STANDARD 14)

add_executable(project1 main.cpp IParser.cpp IParser.h Command.h CommandManager.cpp CommandManager.h OpenServerCommand.cpp OpenServerCommand.h DataReaderServer.cpp DataReaderServer.h Utils.cpp Utils.h Interpreter.cpp Interpreter.h ConnectCommand.cpp ConnectCommand.h DefineVarCommand.cpp DefineVarCommand.h)