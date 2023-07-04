
// Вариант 8

#include <iostream>
#include <vector> 
#include <algorithm>
#include <string> 

#include "histogram.h"

using std::cout; using std::cin; using std::vector; using std::cerr; using std::string;

vector<double> input_numbers(size_t number_count);
vector<size_t> make_histogram(const vector<double>& numbers, size_t bin_count, size_t number_count);

void svg_begin(double width, double height);
void svg_end();
void svg_text(double left, double baseline, string text);
void svg_rect(double x = 0, double y = 0, double width = 100, double height = 200, string stroke = "black", string fill = "black");
void show_histogram_svg(const vector<size_t>& bins);

int main() {

    // Ввод данных

    size_t number_count;

    cerr << "Enter number count: ";
    cin >> number_count;

    cerr << "Enter numbers: \n";
    const auto numbers = input_numbers(number_count);

    size_t bin_count;

    cerr << "Enter bin count: ";
    cin >> bin_count;

    // Обработка данных

    const auto bins = make_histogram(numbers, bin_count, number_count);

    // Вывод данных

    show_histogram_svg(bins);

    return 0;

}

vector<double> input_numbers(size_t number_count) {
    vector<double> result(number_count);
    for (size_t i = 0; i < number_count; i++) {
        cerr << i + 1 << ": ";
        cin >> result[i];
    }
    return result;
}

vector<size_t> make_histogram(const vector<double>& numbers, size_t bin_count, size_t number_count) {
    vector<size_t> result(bin_count);

    double min, max;
    find_minmax(numbers, min, max);

    double bin_size = (max - min) / bin_count;

    for (size_t i = 0; i < number_count; i++) {
        bool found = false;
        for (size_t j = 0; (j < bin_count - 1) && !found; j++) {
            auto lo = min + j * bin_size;
            auto hi = min + (j + 1) * bin_size;
            if ((lo <= numbers[i]) && (numbers[i] < hi)) {
                result[j]++;
                found = true;
            }
        }
        if (!found) {
            result[bin_count - 1]++;
        }
    }
    //sort(result.begin(), result.end()); // Вариант 8
    return result;
}


void svg_begin(double width, double height) {
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void svg_end() {
    cout << "</svg>\n";
}

void svg_text(double left, double baseline, string text) {
    cout << "<text x='" << left << "' y='" << baseline << "'>" << text << "</text>";
}

void svg_rect(double x, double y, double width, double height, string stroke, string fill) {
    cout << "<rect x='" << x << "' y='" << y << "' width='" << width << "' height='" << height << "' stroke='" << stroke << "' fill='" << fill << "'/>";
}

void show_histogram_svg(const vector<size_t>& bins) {
    const size_t SCREEN_WIDTH = 40;
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 5;

    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;

    size_t max_count = 0;

    for (size_t bin : bins) {
        if (bin > max_count) {
            max_count = bin;
        }
    }

    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);

    double top = 0;
    for (size_t bin : bins) {

        double bin_width = BLOCK_WIDTH * bin;

        if (max_count > MAX_ASTERISK) {
            const double scaling_factor = static_cast<double>(MAX_ASTERISK) / max_count;
            bin_width = BLOCK_WIDTH * bin * scaling_factor;
        }

        svg_text(TEXT_LEFT, top + TEXT_BASELINE, std::to_string(bin));
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, "red", "#ffeeee");
        top += BIN_HEIGHT;
    }
    svg_end();
}
