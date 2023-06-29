//
// Created by mirabelka on 06.03.23.
//
#include <iostream>
#include <vector>

std::vector<long double> multiply(std::vector<long double>& A, std::vector<long double>& B) {
    int m = A.size();
    int n = B.size();
    std::vector<long double> prod(m + n - 1, 0);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            prod[i + j] += A[i] * B[j];
        }
    }
    return prod;
}

std::vector<long double> multiply_wilkilson(int poly_number) {
    std::vector<long double> first_poly = {-1.0L, 1.0L};
    std::vector<long double> second_poly = {-2.0L, 1.0L};
    std::vector<long double> prod = multiply(first_poly, second_poly);

    if (poly_number == 2) {
        return prod;
    }

    for (int i = 3; i <= poly_number; i++) {
        std::vector<long double> temp_poly = {static_cast<long double>(-i), 1.0L};
        std::vector<long double> new_prod = multiply(prod, temp_poly);
        prod = new_prod;
    }
    return prod;
}

void print_polynomian(std::vector<long double>& poly) {
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

long double horner(std::vector<long double>& poly, long double x) {
    long double result = poly[poly.size()-1];

    for (int i = poly.size()-2; i >= 0; i--) {
        result = result * x + poly[i];
    }

    return result;
}

long double clenshaw(std::vector<long double>& poly, long double x) {
    int n = poly.size() - 1;
    long double b_n = poly[n];
    long double b_n_minus_1 = poly[n - 1] + b_n * x;

    for (int i = n - 2; i >= 0; i--) {
        long double temp = poly[i] + b_n_minus_1 * 2 * x - b_n;
        b_n = b_n_minus_1;
        b_n_minus_1 = temp;
    }

    return b_n_minus_1;
}

int main() {
    int polys_number = 20;

    std::vector<long double> result = multiply_wilkilson(polys_number);

    std::cout << "Polynomial: \n";
    print_polynomian(result);

    double x_1 = 1.0L;
    double x_2 = 20.0L;
    std::cout << "<Horner> Value of the polynomial at x=" << x_1 << " is " << horner(result, x_1) << std::endl;
    std::cout << "<Horner> Value of the polynomial at x=" << x_2 << " is " << horner(result, x_2) << std::endl;

    std::cout << "<Clenshaw> Value of the polynomial at x=" << x_1 << " is " << clenshaw(result, x_1) << std::endl;
    std::cout << "<Clenshaw> Value of the polynomial at x=" << x_2 << " is " << clenshaw(result, x_2) << std::endl;

    return 0;
}