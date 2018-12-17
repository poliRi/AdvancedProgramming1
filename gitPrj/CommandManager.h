////
//// Created by Polina Rabinovich on 10/12/2018.
////
//
//#ifndef PROJECT1_COMMANDMANAGER_H
//#define PROJECT1_COMMANDMANAGER_H
//
//#include <string>
//#include <map>
//#include "Command.h"
//#include "OpenServerCommand.h"
//
//
//
//using namespace std;
//
//class CommandManager {
//private:
//    map<string, Command *> commands;
//
//public :
//    CommandManager() {
////        commands["openDataServer"] = new OpenServerCommand();
////        commands["connect"] = new ConnectCommand();
////        commands["var"] = new DefineVarCommand();
//
//
//        //TODO only add here commands, rest is finished
//    }
//
//    string *getArgs(string str) {
//        In lexer;
//        lexer.Lexer(str);
//        vector<string> result;
//
//    }
//
//    /**
//     * checks if command exists in the map, and if it does executes it.
//     * @param command command to execute, for example "openDataServer", "var", "connect"...
//     * @param args args to execute with command, for example "172.0.0.1 5402", "5400 10"...
//     * @return 1 if succeed 0 otherwise
//     */
//    int execute(string command, vector<string> args) {
//        if (isLegal(command)) {
//            return commands[command]->doCommand(args);
//        }
//        return 0;
//    }
//
//
//    bool isLegal(string command) {
//        if (commands.find(command) == commands.end()) {
//            return true;
//        } else {
//            //maybe thrpw exeception here
//            return false;
//        }
//    }
//
//    ~CommandManager() {
//        for (auto s : commands) {
//            delete (s.second);
//        }
//    }
//
//
//};
//
//
//#endif //PROJECT1_COMMANDMANAGER_H
