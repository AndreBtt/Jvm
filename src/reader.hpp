#ifndef READER_H_
#define READER_H_

#include <iostream>
#include "base_types.hpp"

class Reader{
  public:

    FILE *fp;

    u4 magic_number;

    u2 min_version;
    u2 max_version;
    u2 cp_length;
    u2 access_flags;
    u2 this_class;
    u2 super_class;
    u2 interfaces_count;
    u2 fields_count;
    u2 methods_count;
    u2 attributes_count;

    u1 read_u1(FILE *fp);
    u2 read_u2(FILE *fp);
    u4 read_u4(FILE *fp);

};
#endif