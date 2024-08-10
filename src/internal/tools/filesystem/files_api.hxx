#include <fstream>
#include <ios>
#include <vector>

namespace yg::files_api
{
std::string read_file(const char* path);

void get_pixels_from_png(const char*             path,
                         std::vector<std::byte>& image,
                         unsigned long&          w,
                         unsigned long&          h);
} // namespace yg::files_api