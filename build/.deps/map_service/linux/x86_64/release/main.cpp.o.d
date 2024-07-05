{
    files = {
        "main.cpp"
    },
    depfiles_gcc = "main.o: main.cpp agv_map.pb.h\
",
    values = {
        "/opt/rh/devtoolset-10/root/usr/bin/gcc",
        {
            "-m64",
            "-fvisibility=hidden",
            "-fvisibility-inlines-hidden",
            "-O3",
            "-std=c++20",
            "-Iproto",
            "-I.",
            "-Ibuild/.gens/map_service/linux/x86_64/release/rules/protobuf/proto",
            "-Wreturn-type",
            "-Werror=return-type",
            "-fopenmp",
            "-DNDEBUG"
        }
    }
}