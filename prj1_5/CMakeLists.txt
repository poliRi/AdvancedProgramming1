cmake_minimum_required(VERSION 3.12)
project(project1)

set(CMAKE_CXX_STANDARD 14)

add_executable(project1 main.cpp OpenServerCommand.cpp OpenServerCommand.h DataReaderServer.cpp DataReaderServer.h Utils.cpp Utils.h Interpreter.cpp Interpreter.h ConnectCommand.cpp ConnectCommand.h DefineVarCommand.cpp DefineVarCommand.h BinaryExpressions.cpp BinaryExpressions.h interface.h Number.cpp Number.h PrintCommand.cpp PrintCommand.h LoopCommand.cpp LoopCommand.h ConditionParser.cpp ConditionParser.h IfCommand.cpp IfCommand.h Queue.cpp Queue.h Readme.md ShuntingYard.cpp ShuntingYard.h Stack.cpp Stack.h StringTool.cpp StringTool.h Token.cpp Token.h)