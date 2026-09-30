// Source - https://stackoverflow.com/a/116220
// Posted by Konrad Rudolph, modified by community. See post 'Timeline' for change history
// Retrieved 2026-09-30, License - CC BY-SA 4.0

#include <filesystem>
#include <fstream>
#include <string>
namespace fs = std::filesystem;

auto read_file(fs::path const& path) -> std::string {
    constexpr auto read_size = std::size_t(4096);
    auto stream = std::ifstream(path);
    stream.exceptions(std::ios_base::badbit);

    if (not stream) {
        throw std::ios_base::failure("file does not exist");
    }

    auto out = std::string();
    auto buf = std::string(read_size, '\0');
    while (stream.read(& buf[0], read_size)) {
        out.append(buf, 0, stream.gcount());
    }
    out.append(buf, 0, stream.gcount());
    return out;
}
