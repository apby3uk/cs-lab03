
#include "histogram.h"

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

void svg_text(double left, double baseline, string text, size_t font_size) {
    cout << "<text x='" << left << "' y='" << baseline << "' font-size='" << font_size << "'>" << text << "</text>";
}

void svg_rect(double x, double y, double width, double height, string stroke, string fill) {
    cout << "<rect x='" << x << "' y='" << y << "' width='" << width << "' height='" << height << "' stroke='" << stroke << "' fill='" << fill << "'/>";
}

void show_histogram_svg(const vector<size_t>& bins, string column_color, size_t font_size) {
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

    svg_header(IMAGE_WIDTH, top + TEXT_BASELINE, "Histogram", font_size);
    top += TEXT_BASELINE + 10;

    for (size_t bin : bins) {

        double bin_width = BLOCK_WIDTH * bin;

        if (max_count > MAX_ASTERISK) {
            const double scaling_factor = static_cast<double>(MAX_ASTERISK) / max_count;
            bin_width = BLOCK_WIDTH * bin * scaling_factor;
        }

        svg_text(TEXT_LEFT, top + TEXT_BASELINE, std::to_string(bin), font_size);
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, "red", column_color);
        top += BIN_HEIGHT;
    }
    svg_end();
}


bool check_color(string color) {
    if (color == "red") {
        return false;
    }
    else {
        return true;
    }
}

string input_color_svg() {
    string color;
    do {
        cerr << "Enter a column fill color: ";
        getline(cin >> std::ws, color);
        transform(color.begin(), color.end(), color.begin(), ::tolower);
        if (!check_color(color)) {
            cerr << "You entered red. Select another color.\n";
        }
    } while (!check_color(color));
    return color;
}

void svg_header(const size_t width, const size_t baseline, string text, size_t font_size) {
    const auto SYMBOL_WIDTH = 7.5;
    double word_width = text.length() * SYMBOL_WIDTH;
    double x = (width - word_width) / 2;
    svg_text(x, baseline, text, font_size);
}


size_t input_font_size_svg() {
    size_t font_size;
    do {
        cerr << "Enter font size (8-32): ";
        cin >> font_size;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            font_size = 12;
            break;
        }
        else if (int(font_size) <= 0) {
            cerr << "Invalid font size! Font size can't be less than or equal to 0!\n";
        }
        else if (font_size < 8) {
            cerr << "Invalid font size! Font size must be greater than or equal to 8!\n";
        }
        else if (font_size > 32) {
            cerr << "Invalid font size! Font size must be less than or equal to 32!\n";
        }
    } while (font_size < 8 || font_size > 32);
    return font_size;

}