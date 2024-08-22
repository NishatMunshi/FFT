#include <SFML/Graphics.hpp>
#include <chrono>
#include <iomanip>
#include <iostream>

#include "../include/FFT.hpp"

constexpr double rect(double i, double L) {
    if (std::abs(i) < std::abs(L)) {
        return 1;
    }
    return 0;
}

#define WIN_DIM_VER 800
#define WIN_DIM_HOR (2 * WIN_DIM_VER)

void draw_fft_mag(std::vector<std::complex<double>> const &fft, sf::RenderWindow &window) {
    sf::Vertex point{{0, 0}, sf::Color::Yellow};
    float x_step = (float)WIN_DIM_HOR / 2 / fft.size();
    auto largest_mag = std::abs(*std::max_element(fft.cbegin(),
                                                  fft.cend(),
                                                  [](std::complex<double> w, std::complex<double> z) { return std::abs(w) < std::abs(z); }));
    float y_scalar = WIN_DIM_VER / largest_mag;

    for (std::size_t index = fft.size() / 2; const auto &value : fft) {
        if (index > fft.size()) index = 0;
        auto mag = std::abs(value);

        point.position = {(index++) * x_step,
                          WIN_DIM_VER - y_scalar * (float)mag};

        window.draw(&point, 1, sf::Points);
    }
}

void draw_fft_phase(std::vector<std::complex<double>> const &fft, sf::RenderWindow &window) {
    sf::Vertex point{{0, 0}, sf::Color::Green};
    float x_step = (float)WIN_DIM_HOR / 2 / fft.size();
    auto largest_arg = std::arg(*std::max_element(fft.cbegin(),
                                                  fft.cend(),
                                                  [](std::complex<double> w, std::complex<double> z) { return std::arg(w) < std::arg(z); }));
    float y_scalar = WIN_DIM_VER / 4 / largest_arg;

    for (std::size_t index = fft.size() / 2; const auto &value : fft) {
        if (index > fft.size()) index = 0;
        auto argument = std::arg(value);

        point.position = {(index++) * x_step + WIN_DIM_HOR / 2,
                          WIN_DIM_VER / 2 - y_scalar * (float)argument};

        window.draw(&point, 1, sf::Points);
    }
}

void draw_divider(sf::RenderWindow &window) {
    sf::VertexArray lines(sf::LinesStrip, 2);
    lines[0].position = sf::Vector2f(WIN_DIM_HOR / 2, 0);
    lines[1].position = sf::Vector2f(WIN_DIM_HOR / 2, WIN_DIM_VER);

    window.draw(lines);
}

int main() {
    std::vector<std::complex<double>> samples;
    for (int32_t i = INT16_MIN; i <= INT16_MAX; ++i) {
        samples.push_back(rect(i, 10));
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
        draw_fft_mag(fft, window);
        draw_divider(window);
        draw_fft_phase(fft, window);
        window.display();
    }
    return 0;
}
