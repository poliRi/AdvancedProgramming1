cmake_minimum_required(VERSION 3.12)
project(project1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)
add_executable(project1 main.cpp BindCommand.h BindCommand.cpp OpenServerCommand.cpp OpenServerCommand.h Utils.cpp Utils.h Interpreter.cpp Interpreter.h ConnectCommand.cpp ConnectCommand.h DefineVarCommand.cpp DefineVarCommand.h BinaryExpressions.cpp BinaryExpressions.h interface.h Number.cpp Number.h PrintCommand.cpp PrintCommand.h WhileCommand.cpp WhileCommand.h ConditionParser.cpp ConditionParser.h IfCommand.cpp IfCommand.h Client.cpp Client.h AssignmentCommand.h AssignmentCommand.cpp FormExpressionCommand.cpp FormExpressionCommand.h SleepCommand.cpp SleepCommand.h)
