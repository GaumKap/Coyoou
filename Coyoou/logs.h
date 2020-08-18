#pragma once
#include <iostream>

// Save Errors in Log File
void CYO_logging(std::string the_log) {
	FILE* f;
	errno_t err;
	err = fopen_s(&f, "coyoou.log", "a+"); // a+ (create + append) option will allow appending which is useful in a log file
	if (f == NULL) {
		std::cout << "[FATAL ERROR] LOG FILE : " << err << std::endl;
	}
	else {
		fprintf(f, the_log.c_str());
		fclose(f);
	}
}