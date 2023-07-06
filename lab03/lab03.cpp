
// Вариант 8

#include "histogram.h"
#include <curl/curl.h>
#include <sstream>

using std::stringstream;

vector<double> input_numbers(istream& in, size_t number_count, bool prompt);
vector<size_t> make_histogram(Input input);
void find_minmax(const vector<double>& numbers, double& min, double& max);

Input read_input(istream& in, bool prompt);
Input download(const string& address);
size_t write_data(void* items, size_t item_size, size_t item_count, void* ctx);


int main(int argc, char* argv[]) {

    // Ввод данных

    Input input;

    if (argc > 1) {
        input = download(argv[1]);
    }
    else {
        input = read_input(cin, true);
    }

    // Обработка данных

    const auto bins = make_histogram(input);

    // Вывод данных

    show_histogram_svg(bins, input);

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

vector<size_t> make_histogram(Input input) {

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
    sort(result.begin(), result.end()); // Вариант 8
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

    data.font_size = input_font_size_svg(in, prompt);

    data.column_color = input_color_svg(in, prompt);

    return data;
}

Input download(const string& address) {
    stringstream buffer;

    CURL* curl = curl_easy_init();
    if (curl) {
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); // error 60
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
        res = curl_easy_perform(curl);

        if (res != CURLE_OK) { // CURLE_OK = 0
            cout << curl_easy_strerror(res);
            exit(1);
        }
        //cout << res;

        curl_easy_cleanup(curl);
    }
    return read_input(buffer, false);
}

size_t write_data(void* items, size_t item_size, size_t item_count, void* ctx) {
    size_t data_size = item_size * item_count;
    stringstream* buffer = reinterpret_cast<stringstream*>(ctx);
    const char* accepted = reinterpret_cast<const char*>(items);
    //(*buffer).write(accepted, data_size);
    buffer->write(accepted, data_size);
    return data_size;
}