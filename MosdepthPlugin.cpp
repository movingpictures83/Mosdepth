#include "PluginManager.h"
#include <stdio.h>
#include <stdlib.h>
#include "MosdepthPlugin.h"

void MosdepthPlugin::input(std::string file) {
  inputfile = file;
 std::ifstream ifile(inputfile.c_str(), std::ios::in);
 std::cout << file << std::endl;
 while (!ifile.eof()) {
   std::string key, value;
   ifile >> key;
   if (key.length() == 0) break;
   ifile >> value;
   if (value.length() == 0) break;
   parameters[key] = value;
 }


}

void MosdepthPlugin::run() {}

void MosdepthPlugin::output(std::string file) {
 std::string outputfile = file;
 std::string myCommand = "";
 myCommand += "mosdepth ";
 if (parameters.count("noperbase") != 0)
	 myCommand += " -n ";
 if (parameters.count("flag") != 0)
	 myCommand += " -F "+parameters["flag"];
 if (parameters.count("threads") != 0)
	 myCommand += " -t "+parameters["threads"];
 myCommand += " " + outputfile + " " + std::string(PluginManager::prefix())+"/"+parameters["bamfile"];
std::cout << myCommand << std::endl;
system(myCommand.c_str());
}

PluginProxy<MosdepthPlugin> MosdepthPluginProxy = PluginProxy<MosdepthPlugin>("Mosdepth", PluginManager::getInstance());

