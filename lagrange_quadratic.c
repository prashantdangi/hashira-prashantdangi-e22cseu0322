#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define MAX_LINE 1024
#define MAX_VALUE 1000

// Function to convert base-n string to decimal
long long baseToDecimal(const char* value, int base) {
    long long result = 0;
    int len = strlen(value);
    
    for (int i = 0; i < len; i++) {
        char c = value[i];
        int digit;
        
        if (isdigit(c)) {
            digit = c - '0';
        } else if (isalpha(c)) {
            digit = tolower(c) - 'a' + 10;
        } else {
            continue; // Skip invalid characters
        }
        
        if (digit >= base) {
            printf("Warning: Invalid digit %d for base %d\n", digit, base);
            return -1;
        }
        
        result = result * base + digit;
    }
    
    return result;
}

// Function to solve system of equations for quadratic coefficients
void solveQuadratic(double x1, double y1, double x2, double y2, double x3, double y3, 
                    double* a, double* b, double* c) {
    // Using Cramer's rule to solve the system:
    // ax1² + bx1 + c = y1
    // ax2² + bx2 + c = y2  
    // ax3² + bx3 + c = y3
    
    double det = x1*x1*(x2 - x3) + x2*x2*(x3 - x1) + x3*x3*(x1 - x2);
    
    if (fabs(det) < 1e-10) {
        printf("Error: Points are collinear or coincident\n");
        return;
    }
    
    double detA = y1*(x2 - x3) + y2*(x3 - x1) + y3*(x1 - x2);
    double detB = x1*x1*(y2 - y3) + x2*x2*(y3 - y1) + x3*x3*(y1 - y2);
    double detC = x1*x1*(x2*y3 - x3*y2) + x2*x2*(x3*y1 - x1*y3) + x3*x3*(x1*y2 - x2*y1);
    
    *a = detA / det;
    *b = detB / det;
    *c = detC / det;
}

// Function to parse JSON and extract data
int parseTestCase(const char* filename, int* n, int* k, double* x_coords, double* y_coords) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error: Cannot open file %s\n", filename);
        return 0;
    }
    
    char line[MAX_LINE];
    int point_count = 0;
    
    while (fgets(line, MAX_LINE, file)) {
        line[strcspn(line, "\n")] = 0; // Remove newline
        
        // Parse keys section
        if (strstr(line, "\"n\":")) {
            sscanf(line, "%*[^0-9]%d", n);
        } else if (strstr(line, "\"k\":")) {
            sscanf(line, "%*[^0-9]%d", k);
        }
        
        // Parse point data (x: {base, value})
        if (strstr(line, "\"base\":")) {
            int base;
            sscanf(line, "%*[^0-9]%d", &base);
            
            // Get next line for value
            if (fgets(line, MAX_LINE, file)) {
                line[strcspn(line, "\n")] = 0;
                char value[MAX_VALUE];
                sscanf(line, "%*[^:]: \"%[^\"]\"", value);
                
                // Convert base-n to decimal
                long long decimal_value = baseToDecimal(value, base);
                if (decimal_value != -1) {
                    x_coords[point_count] = point_count + 1; // x coordinate
                    y_coords[point_count] = (double)decimal_value; // y coordinate
                    point_count++;
                }
            }
        }
    }
    
    fclose(file);
    return point_count;
}

int main() {
    printf("=== Lagrange Quadratic Equation Solver ===\n\n");
    
    // Test Case 1
    printf("--- Test Case 1 ---\n");
    int n1, k1;
    double x1[10], y1[10];
    
    int count1 = parseTestCase("testcase1.json", &n1, &k1, x1, y1);
    
    if (count1 >= 3) {
        printf("n = %d, k = %d\n", n1, k1);
        printf("Points:\n");
        for (int i = 0; i < count1; i++) {
            printf("(%d, %.0f) ", (int)x1[i], y1[i]);
        }
        printf("\n");
        
        // Find quadratic coefficients using first 3 points
        double a1, b1, c1;
        solveQuadratic(x1[0], y1[0], x1[1], y1[1], x1[2], y1[2], &a1, &b1, &c1);
        
        printf("Quadratic equation: %.2fx² + %.2fx + %.2f\n", a1, b1, c1);
        printf("c value: %.2f\n\n", c1);
    }
    
    // Test Case 2
    printf("--- Test Case 2 ---\n");
    int n2, k2;
    double x2[10], y2[10];
    
    int count2 = parseTestCase("testcase2.json", &n2, &k2, x2, y2);
    
    if (count2 >= 3) {
        printf("n = %d, k = %d\n", n2, k2);
        printf("Points:\n");
        for (int i = 0; i < count2; i++) {
            printf("(%d, %.0f) ", (int)x2[i], y2[i]);
        }
        printf("\n");
        
        // Find quadratic coefficients using first 3 points
        double a2, b2, c2;
        solveQuadratic(x2[0], y2[0], x2[1], y2[1], x2[2], y2[2], &a2, &b2, &c2);
        
        printf("Quadratic equation: %.2fx² + %.2fx + %.2f\n", a2, b2, c2);
        printf("c value: %.2f\n\n", c2);
    }
    
    return 0;
}
