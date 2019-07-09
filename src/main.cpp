#include "display.hpp"
#include "engine.hpp"
#include "class_loader.hpp"

int main(int argc, char* argv[]) {
    if(argc < 2) {
        printf("[FALHA] Formato invalido. Utilize o caminho do arquivo \".class\" como argumento.\n");
        exit(1);
    }

    char* file_name = argv[1];

    bool interpretador = false;
    bool exibidor = false;

    for (size_t optind = 2; optind < argc && argv[optind][0] == '-'; optind++) {
        switch (argv[optind][1]) {
            case 'i':
                interpretador = true;
            break;
        
            case 'e': 
                exibidor = true;
            break;
        }
    }

    ClassFile* class_file = build_class_file(string(file_name));

    // //botar isso aqui em outro lugar
    // {
    //     // Remove directory if present.
    //     // Do this before extension removal incase directory has a period character.
    //     std::string file_name_str(file_name);
    //     const size_t last_slash_idx = file_name_str.find_last_of("\\/");
    //     if (std::string::npos != last_slash_idx) {
    //         file_name_str.erase(0, last_slash_idx + 1);
    //     }
    //     // Remove extension if present.
    //     const size_t period_idx = file_name_str.rfind('.');
    //     if (std::string::npos != period_idx) {
    //         file_name_str.erase(period_idx);
    //     }   
    //     std::string class_file_name = get_constant_pool_element(class_file->constant_pool, class_file->this_class);
    //     if (file_name_str != class_file_name) {
    //         std::cerr << std::endl << "Nome do arquivo ( " << file_name_str << " ) diferente do nome da classe ( " << class_file_name << " )" << std::endl << std::endl;
    //         exit(1);
    //     }
    
    // }

    if(exibidor){
        display::class_file(*class_file);
    }

    if(interpretador) {
        Engine engine;
        engine.start(*class_file);
    }

}
