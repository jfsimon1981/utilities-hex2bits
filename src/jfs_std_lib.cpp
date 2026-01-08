#include <string>
#include <vector>
#include "jfs.h"
using namespace std;
//using std::string;
//using std::vector;
// Retuns vector<string> arguments from main(int agc, char** argv)
vector<string> args_read(int argc, char **argv) {
	vector<string> args;
	for (int i{0}; i<argc; i++)
		args.push_back(string {argv[i]});
	return args;
}
