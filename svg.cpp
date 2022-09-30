#include <iostream>
#include <vector>
#include <string.h>
#include "svg.h"
#include <sstream>
#include <windows.h>
#include <cstdio>


void svg_begin(double width, double height) {
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void svg_text(double left, double baseline, string text) {
    cout << "<text x='" << left << "' y='"<< baseline<< "'>"<<text<<"</text>";
}

void svg_rect(double x, double y, double width, double height, string stroke, string fill){
    cout<< "<rect x= '" << x <<"' y='"<< y << "' width='"<<width<<"' height='" << height << "' stroke='"<< stroke<<"' fill='"<<fill<< "' />\n ";
}

void svg_line2(size_t X1,size_t Y1,size_t X2,size_t Y2,string stroke,size_t wid,ostream &stream)
{
stream<<"<line x1='"<<X1<<"' y1='"<<Y1<<"' x2='"<<X2<<"' y2='"<<Y2<<"' stroke='"<<stroke<<"' stroke-width='"<<wid<<"' stroke-dasharray = '10 10'/>";
}


void svg_end() {
    cout << "</svg>\n";
}

string make_info_text() {
    DWORD WINAPI GetVersion(void);
    stringstream buffer;
    const auto R = GetVersion();
    printf("n = %lu\n", R);
    printf("n = %lx\n", R);
    DWORD mask = 0b00000000'00000000'11111111'11111111;
    DWORD version = R & mask;
    printf("ver = %lu\n", version);
    DWORD platform = R >> 16;
    printf("ver2 = %lu\n", platform);
    DWORD mask2 = 0b00000000'11111111;
    DWORD version_major = version & mask2;
    printf("version_major = %lu\n", version_major);
    DWORD version_minor = version >> 8;
    printf("version_minor = %lu\n", version_minor);
    DWORD build;
    if ((R & 0x80000000) == 0)
    {
        build = platform;
        printf("build = %lu\n", build);

    }
    buffer << "Windows" << " " << "v" << " " << version_major << "." << version_minor << " " << "(build" << " " << build << ")" << '\n';
    TCHAR storage[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD  bufCharCount = MAX_COMPUTERNAME_LENGTH + 1;
    GetComputerNameA(LPSTR(storage), &bufCharCount);
    buffer << "Computer name:" << " " << storage;
    return buffer.str();
}

void svg_line2(size_t X1,size_t Y1,size_t X2,size_t Y2,string stroke,size_t wid,ostream &stream, size_t Z, size_t L){
stream<< "<line x1='"<<X1<<"' y1='"<<Y1<<"' x2='"<<X2<<"' y2='"<<Y2<<"' stroke='"<<stroke<<"' stroke-width='"<<wid<<"' stroke-dasharray = '" << Z << " " << L <<"' />";
}

void show_histogram_svg(const vector<size_t>& bins) {
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    double MAX_WIDTH = (IMAGE_WIDTH - TEXT_WIDTH);
    size_t max_bin = bins[0];
    for (size_t bin : bins)
    {
        if (bin > max_bin)
        {
            max_bin = bin;
        }
    }
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT + 30);
    double top = 0;
    double top2 =0;
    svg_line2(top, top, IMAGE_WIDTH, top , "black", 10, cout);
      for (size_t bin : bins) {
        top += BIN_HEIGHT;
        double bin_width = BLOCK_WIDTH * bin;
        if (max_bin > (MAX_WIDTH/BLOCK_WIDTH))
        {
            bin_width = (MAX_WIDTH-15) * (static_cast<double>(bin) / max_bin);
        }
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, "black", "black");
}
top += 2*BIN_HEIGHT;
svg_line2(10, top, IMAGE_WIDTH, top , "black", 10, cout);
svg_line2(top2, top2, top2, top , "black", 10, cout);
svg_line2(IMAGE_WIDTH, top2, IMAGE_WIDTH, top , "black", 10, cout);
    svg_text(TEXT_LEFT, IMAGE_HEIGHT - TEXT_BASELINE + 30, make_info_text());
    svg_end();
}
