#include <bitset>
#include <cmath>
#include <err.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "jfs.h"

#ifdef __OpenBSD__
#include <unistd.h>
#include <err.h>
#endif

using namespace std;

// Converts hexa-decimal to bitmask

void bits_16(unsigned int vin) {
	static bool display_title {1};
	if (display_title) {
		cout << setw(16) << "Bits      " << setw(9) << "Bit" << setw(7) << "Hex" << endl;
		display_title = 0;
	}
	stringstream cout_strm;
	cout_strm << setw(16) << bitset<16>(vin);
	string cout_s {cout_strm.str()};
	cout_s.insert(12, 1, ' '); // 4 bits separators.
	cout_s.insert(8, 1, ' '); //  4 bits separators.
	cout_s.insert(4, 1, ' '); // 4 bits separators.
	cout << cout_s << setw(7) << log2(vin+1) << setw(5) << "(0x" << std::hex << vin << ")" << endl;
}

void bits_32(unsigned int vin) {
	static bool display_title {1};
	if (display_title) {
		cout << setw(32) << "Bits                      " << setw(9) << "Bit" << setw(7) << "Hex" << endl;
		display_title = 0;
	}
	stringstream cout_strm;
	cout_strm << setw(32) << bitset<32>(vin);
	string cout_s {cout_strm.str()};
	cout_s.insert(24, 1, ' '); // 8 bits separators.
	cout_s.insert(16, 1, ' '); // 8 bits separators.
	cout_s.insert(8, 1, ' '); // 8 bits separators.
	cout << cout_s << setw(7) << log2(vin) << setw(5) << "(0x" << std::hex << vin << ")" << endl;
}

void example() {
		bits_16(0x0001U);
		bits_16(0x0002U);
		bits_16(0x0004U);
		bits_16(0x0008U);
		bits_16(0x0010U);
		bits_16(0x0020U);
		bits_16(0x0040U);
		bits_16(0x0080U);
		bits_16(0x0100U);
		bits_16(0x0400U);
		bits_16(0x1000U);
		bits_16(0x4000U);
		bits_32(0x10C3FF25U);
		bits_32(0x1F86FCDFU);
		bits_32(0x1D9CFA9CU);
		cout << endl;
}

void usage() {
	cout << endl;
	cout << "Usage: ./hex2bits 0x... or ./hex2bits file" << endl;
	cout << "./hex2bits 0xff 0x3c3d 0xff35" << endl;
	cout << "./hex2bits list.txt" << endl;
	cout << endl;
}

int print_help_on_exit {0};

void parse_and_display(string i) {
	if ((i[0] == '0') && (i[1] == 'x' || i[1] == 'X')) {
		i.erase(0,2);
		unsigned dec {0};
		stringstream hex_to_dec_strm;
		hex_to_dec_strm << i;
		hex_to_dec_strm >> std::hex >> dec;
		if (dec <= 0xffff)
			bits_16(dec);
		else
			bits_32(dec);
	} else {
		cout << i << " -> Format error (missing 0x or typo eg s/Ox/0x/)" << endl;
		print_help_on_exit = 1;
	}

}

int main(int argc, char** argv) {
#ifdef __OpenBSD__
	if (pledge("stdio rpath", NULL) == -1)
		err(1, "pledge");
#endif
	vector<string> args {args_read(argc, argv)};
	
	// Setup cout floating point decimal printout
	std::cout << std::fixed;
	std::cout << std::setprecision(2);
	
	// Read if we have received a file, otherwise we'll
	// just parse args list of list which should be of
	// the form 0x1f 0x3c, ...

	if (args.size() > 1) {
		ifstream ifs (args[1]);
		if (ifs.is_open()) {
			cout << "Parsing file " << args[1] << " ..." << endl;
			string s;
			while (getline(ifs, s)) {
				parse_and_display(s);
			}
		} else {
			for (auto i:args) {
				static int first_arg {0};
				if (!first_arg++) continue; // Passing the exec name
				parse_and_display(i);
			}
		}
	}
	else {
		usage();
		example();
	}
	if (print_help_on_exit) {
		cout << endl;
		cout << "Please provide hexadecimal number(s)." << endl;
		cout << "Format is 0x... or 0X..." << endl;
		cout << "./hex2bits for usage infos." << endl;
		cout << endl;
	}
}
