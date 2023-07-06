
// Вариант 8

#include "histogram.h"
#include <curl/curl.h>

vector<double> input_numbers(istream& in, size_t number_count, bool prompt);
vector<size_t> make_histogram(const Input& input);
void find_minmax(const vector<double>& numbers, double& min, double& max);

Input read_input(istream& in, bool prompt);

int main(int argc, char* argv[]) {

    curl_global_init(CURL_GLOBAL_ALL);

    if (argc > 1) {
        for (int i = 0; i < argc; i++) {
            cout << "argv[" << i << "] = " << argv[i] << '\n';
        }
        return 0;
    }

    // Ввод данных

    const auto input = read_input(cin, true);

    // Обработка данных

    const auto bins = make_histogram(input);

    // Вывод данных

    show_histogram_svg(bins, input.column_color);

    return 0;

}

vector<double> input_numbers(istream& in, size_t number_count, bool prompt) {
    vector<double> result(number_count);
    for (size_t i = 0; i < number_count; i++) {
        if (prompt) {
            cerr << i + 1 << ": ";
        }
        in >> result[i];
    }
    return result;
}

vector<size_t> make_histogram(const Input& input) {

    const vector<double>& numbers = input.numbers;
    size_t bin_count = input.bin_count;

    vector<size_t> result(bin_count);

    double min, max;
    find_minmax(numbers, min, max);

    double bin_size = (max - min) / bin_count;

    for (size_t i = 0; i < numbers.size(); i++) {
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

void find_minmax(const vector<double>& numbers, double& min, double& max) {
    if (numbers.size() != 0) {
        min = numbers[0];
        max = numbers[0];
        for (double x : numbers) {
            if (x < min) {
                min = x;
            }
            else if (x > max) {
                max = x;
            }
        }
    }
}

Input read_input(istream& in, bool prompt) {

    Input data;

    if (prompt) {
        cerr << "Enter number count: ";
    }
    size_t number_count;
    in >> number_count;

    if (prompt) {
        cerr << "Enter numbers: \n";
    }

    data.numbers = input_numbers(in, number_count, prompt);

    if (prompt) {
        cerr << "Enter bin count: ";
    }
    in >> data.bin_count;

    data.column_color = input_color_svg(prompt);

    return data;
}

