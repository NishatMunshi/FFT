#include <SFML/Graphics.hpp>
#include <chrono>
#include <iomanip>
#include <iostream>

#include "../include/FFT.hpp"

constexpr double
rect(double t, double T) {
    if (std::abs(t) <= std::abs(T)) {
        return 1;
    }
    return 0;
}

constexpr double
h(double t) {
    return rect(t, 50) * (3 * std::cos(t) + std::sin(2 * t));
}

#define WIN_DIM_VER 800
#define WIN_DIM_HOR (WIN_DIM_VER)

void draw_mag(std::vector<std::complex<double>> const &values,
              sf::RenderWindow &window) {
    sf::Vertex point{{0, 0}, sf::Color::Yellow};
    float x_step = float(WIN_DIM_HOR) / values.size();
    auto largest_mag = std::abs(*std::max_element(values.cbegin(),
                                                  values.cend(),
                                                  [](std::complex<double> w, std::complex<double> z) { return std::abs(w) < std::abs(z); }));
    float y_scalar = 3 * WIN_DIM_VER / 4 / largest_mag;

    for (std::size_t index = values.size() / 2; const auto &value : values) {
        if(index > values.size()) index = 0;
        auto mag = std::abs(value);

        point.position = {(index++) * x_step,
                          WIN_DIM_VER - y_scalar * float(mag)};

        window.draw(&point, 1, sf::Points);
    }
}

int main() {
    std::vector<std::complex<double>> samples;
    for (int32_t i = INT16_MIN; i <= INT16_MAX; ++i) {
        samples.push_back(h(i));
    }

    auto const fft = FFT(samples);

    sf::RenderWindow window{sf::VideoMode{WIN_DIM_HOR, WIN_DIM_VER}, "FFT"};

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        draw_mag(fft, window);
        window.display();
    }
    return 0;
}
