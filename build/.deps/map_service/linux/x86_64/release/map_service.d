{
    files = {
        "build/.objs/map_service/linux/x86_64/release/main.cpp.o",
        "build/.objs/map_service/linux/x86_64/release/gens/rules/protobuf/proto/agv_map.pb.cc.o"
    },
    values = {
        "/opt/rh/devtoolset-10/root/usr/bin/g++",
        {
            "-m64",
            "-s",
            "-lprotobuf",
            "-lpthread"
        }
    }
}