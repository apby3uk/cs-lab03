
#pragma once

#include <iostream>
#include <vector> 
#include <algorithm>
#include <string> 

using std::cout; using std::cin; using std::vector; using std::cerr; using std::string;

void svg_begin(double width, double height);
void svg_end();
void svg_text(double left, double baseline, string text, size_t font_size);
void svg_rect(double x = 0, double y = 0, double width = 100, double height = 200, string stroke = "black", string fill = "black");
void show_histogram_svg(const vector<size_t>& bins, string column_color, size_t font_size);

bool check_color(string color);
string input_color_svg();
void svg_header(const size_t width, const size_t baseline, string text, size_t font_size);

size_t input_font_size_svg();