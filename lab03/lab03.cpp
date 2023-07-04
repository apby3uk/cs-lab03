
// Вариант 8

#include <iostream>
#include <vector> 
#include <algorithm>
using std::cout; using std::cin; using std::vector; using std::cerr;


int main() {

	// Ввод данных

	size_t number_count;

	cerr << "Enter number count: ";
	cin >> number_count;

	vector<double> numbers(number_count);

	cerr << "Enter numbers: \n";

	for (size_t i = 0; i < number_count; i++) {
		cin >> numbers[i];
	}

	size_t bin_count;

	cerr << "Enter bin count: ";
	cin >> bin_count;

	// Обработка данных

	vector<size_t> bins(bin_count);

	double min = numbers[0];
	double max = numbers[0];
	for (double x : numbers) {
		if (x < min) {
			min = x;
		}
		else if (x > max) {
			max = x;
		}
	}

	double bin_size = (max - min) / bin_count;

	for (size_t i = 0; i < number_count; i++) {
		bool found = false;
		for (size_t j = 0; (j < bin_count - 1) && !found; j++) {
			auto lo = min + j * bin_size;
			auto hi = min + (j + 1) * bin_size;
			if ((lo <= numbers[i]) && (numbers[i] < hi)) {
				bins[j]++;
				found = true;
			}
		}
		if (!found) {
			bins[bin_count - 1]++;
		}
	}

	/*	Вариант 8
		После подсчета количеств значений в столбцах,
		замените их нарастающим итогом, начиная с первого столбца. */

		//sort(bins.begin(), bins.end()); // Вариант 8

		// Вывод данных

	const size_t SCREEN_WIDTH = 80;
	const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;

	size_t max_count = 0;

	for (size_t bin : bins) {
		if (bin > max_count) {
			max_count = bin;
		}
	}

	for (size_t i = 0; i < bin_count; i++) {
		if (bins[i] < 10) {
			cout << "  ";
		}
		else if (bins[i] < 100) {
			cout << " ";
		}
		cout << bins[i] << '|';

		size_t height = bins[i];

		if (max_count > MAX_ASTERISK) {
			const double scaling_factor = static_cast<double>(MAX_ASTERISK) / max_count;
			height = static_cast<size_t>(bins[i] * scaling_factor);
		}

		for (size_t j = 0; j < height; j++) {
			cout << '*';
		}
		cout << '\n';
	}

	return 0;

}
