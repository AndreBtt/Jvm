#include "class_file.hpp"
#include "display.hpp"

int main(int argc, char* argv[]) {
    if(argc < 2) {
        printf("[FALHA] Formato invalido. Utilize o caminho do arquivo \".class\" como argumento.\n");
        exit(1);
    }

    char* file_name = argv[1];
    FILE* file_pointer = fopen(file_name, "rb");
    if(file_pointer == NULL) {
        perror("[FALHA] O seguinte erro ocorreu ao tentar abrir o arquivo");
        exit(1);
    }

    // this variable holds all the information about .class file
    ClassFile class_file;

    // set magic number and check if it is 0xcafebabe
    class_file.set_magic_number(file_pointer);

    // set versions
    class_file.set_version(file_pointer);

    // set constant pool length and create it
    class_file.set_constant_pool(file_pointer);

    // set access flags
    class_file.set_access_flags(file_pointer);

    // set this class
    class_file.set_this_class(file_pointer);

    // set super class
    class_file.set_super_class(file_pointer);

    // set interface size and create it
    class_file.set_interfaces(file_pointer);

    // set fields size and create it
    class_file.set_fields(file_pointer);

    // set methods size and create it
    class_file.set_methods(file_pointer);

    // set attributes size and create it
    class_file.set_attributes(file_pointer);

    display::class_file(class_file);

    fclose(file_pointer);
}
