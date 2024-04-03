#include <string>
#ifndef MYSTRUCT_H
#define MYSTRUCT_H

using namespace std;

struct compiler_info {
        float compiler_version;
        string compiler_name;
        string make_dir;
        string make_file;
        string output_dir;
        string output_cpp;
    };

#endif
