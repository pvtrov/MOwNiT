//
// Created by mirabelka on 06.03.23.
//
#include <iostream>
#include <vector>

std::vector<double> multiply(std::vector<double>& A, std::vector<double>& B) {
    int m = A.size();
    int n = B.size();
    std::vector<double> prod(m + n - 1, 0);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            prod[i + j] += A[i] * B[j];
        }
    }
    return prod;
}

std::vector<double> multiply_wilkilson(int poly_number) {
    std::vector<double> first_poly = {-1.0, 1.0};
    std::vector<double> second_poly = {-2.0, 1.0};
    std::vector<double> prod = multiply(first_poly, second_poly);

    if (poly_number == 2) {
        return prod;
    }

    for (int i = 3; i <= poly_number; i++) {
        std::vector<double> temp_poly = {static_cast<double>(-i), 1.0};
        std::vector<double> new_prod = multiply(prod, temp_poly);
        prod = new_prod;
    }
    return prod;
}

void print_polynomian(std::vector<double>& poly) {
    int n = poly.size();
    for (int i = n; i >= 0; i--) {
        std::cout << poly[i];
        if (i != 0)
            std::cout << "x^" << i;
        if (i != n - 1)
            std::cout << " + ";
    }
    std::cout << "\n\n";
}

double horner(std::vector<double>& poly, double x) {
    double result = poly[poly.size()-1];

    for (int i = poly.size()-2; i >= 0; i--) {
        result = result * x + poly[i];
    }

    return result;
}

double clenshaw(std::vector<double>& poly, double x) {
    int n = poly.size() - 1;
    double b_n = poly[n];
    double b_n_minus_1 = poly[n - 1] + b_n * x;

    for (int i = n - 2; i >= 0; i--) {
        double temp = poly[i] + b_n_minus_1 * 2 * x - b_n;
        b_n = b_n_minus_1;
        b_n_minus_1 = temp;
    }

    return b_n_minus_1;
}

int main() {
    int polys_number = 20;

    std::vector<double> result = multiply_wilkilson(polys_number);

    std::cout << "Polynomial: \n";
    print_polynomian(result);

    double x_1 = 1.0;
    double x_2 = 20.0;
    std::cout << "<Horner> Value of the polynomial at x=" << x_1 << " is " << horner(result, x_1) << std::endl;
    std::cout << "<Horner> Value of the polynomial at x=" << x_2 << " is " << horner(result, x_2) << std::endl;

    std::cout << "<Clenshaw> Value of the polynomial at x=" << x_1 << " is " << clenshaw(result, x_1) << std::endl;
    std::cout << "<Clenshaw> Value of the polynomial at x=" << x_2 << " is " << clenshaw(result, x_2) << std::endl;

    return 0;
}