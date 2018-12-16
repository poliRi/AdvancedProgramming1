cmake_minimum_required(VERSION 3.12)
project(project1)

set(CMAKE_CXX_STANDARD 14)

add_executable(project1 main.cpp Lexer.cpp Lexer.h ILexer.cpp ILexer.h Parser.cpp Parser.h IParser.cpp IParser.h Command.cpp Command.h CommandManager.cpp CommandManager.h OpenServerCommand.cpp OpenServerCommand.h ConnectCommand.cpp ConnectCommand.h DefineVarCommand.cpp DefineVarCommand.h DataReaderServer.cpp DataReaderServer.h Utils.cpp Utils.h)