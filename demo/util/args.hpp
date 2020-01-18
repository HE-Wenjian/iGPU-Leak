#pragma once
#include "args.hxx"

#define ArgsMention(args_opt) ( bool(CommandLineParser::getInstance().args_opt) )
#define ArgsGet(args_opt) ( CommandLineParser::getInstance().args_opt.Get() )

class CommandLineParser{
private:
    CommandLineParser() {};
    args::ArgumentParser parser{
R"(This program can
*. run kernel in .cl : ./ocl_run --cl  <.cl>  -n kernel [OPTION]
*. run kernel in .bin: ./ocl_run --bin <.bin> -n kernel [OPTION]
)"};

public:
    CommandLineParser(CommandLineParser const&)  = delete;
    void operator=(CommandLineParser const&)     = delete;

    static CommandLineParser& getInstance(){
        static CommandLineParser instance; // Guaranteed to be destroyed.
        return instance;
    }

    // CommandLine Arguments:
    args::Group base_file{parser, "Supply .cl/.bin file as  :", args::Group::Validators::Xor};
        args::ValueFlag<std::string> ocl_c{base_file, ".cl", "Pick a .cl file.",{'c',"cl"}};
        args::ValueFlag<std::string> ocl_bin{base_file, ".bin", "Pick a OpenCL .bin file.",{'b',"bin"}};
    args::ValueFlag<std::string> kernel_name{parser, "Name", "The name of the kernel function.",{'n'},args::Options::Required};
    args::NargsValueFlag<int> g_wsize{parser, "Global X [Y [Z]]", "Global work sizes.", {'g'}, {1,3}};
    args::NargsValueFlag<int> l_wsize{parser, "LocalX[Y [Z]]]", "Local work sizes.", {'l'}, {1,3}};
    args::NargsValueFlag<int> surf_sizes{parser, "surf0 surf1 ...", "List of SVM buffer sizes in num of int32.", {'s',"surf"}, {1,1024}, {1}};

    args::ValueFlag<int> NumElemPerLine{parser, "NumElemPerLine", "Print surf output with Num elements per line.",{'E'},20};
    args::ValueFlag<int> NumEnqueue{parser, "NumEnqueue", "Num of times to enqueue the kernel in each run.",{"enqueue"},1};
    args::ValueFlag<int> NumBatch{parser, "NumBatch", "Num of times to run this program.",{"batch"},1};

    args::Flag  verbose{parser, "verbose", "verbose.",{'v'}};
    args::HelpFlag help{parser, "help", "Display this help menu", {'?','h', "help"}};
    // --------------------

    int parse(int argc, char **argv){
        try{
            parser.ParseCLI(argc, argv);
            if( ArgsGet(g_wsize).size()==0){
                g_wsize.ParseValue({std::string{"1"}});
            }
            if( ArgsGet(l_wsize).size()==0 ){
                l_wsize.ParseValue({std::string{"1"}});
            }
            if( ArgsGet(l_wsize).size()!=g_wsize.Get().size() ){
                throw args::Error("Global work dim != Local work dim");
            }
        }
        catch (args::Help){
            printf("%s",parser.Help().c_str());
            exit(0);
        }
        catch (args::Error e)
        {
            printf("[ERROR] %s\n",e.what());
            fprintf(stderr,"%s",parser.Help().c_str());     
            exit(1);
        }
    }
};
