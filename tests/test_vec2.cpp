#include "../include/math/vec2.hpp"
#include <cassert>
#include <cmath>
#include <iostream>

using namespace sim;

void test_vec2_construction() {
  std::cout << "Testing Vec2 construction...\n";
  
  Vec2 v1;
  assert(v1.x == 0.0 && v1.y == 0.0);
  
  Vec2 v2{3.0, 4.0};
  assert(v2.x == 3.0 && v2.y == 4.0);
  
  std::cout << "  ✓ Construction tests passed\n";
}

void test_vec2_arithmetic() {
  std::cout << "Testing Vec2 arithmetic...\n";
  
  Vec2 v1{3.0, 4.0};
  Vec2 v2{1.0, 2.0};
  
  // Addition
  Vec2 v3 = v1 + v2;
  assert(v3.x == 4.0 && v3.y == 6.0);
  
  // Subtraction
  Vec2 v4 = v1 - v2;
  assert(v4.x == 2.0 && v4.y == 2.0);
  
  // Scalar multiplication
  Vec2 v5 = v1 * 2.0;
  assert(v5.x == 6.0 && v5.y == 8.0);
  
  Vec2 v6 = 2.0 * v1;  // Free function
  assert(v6.x == 6.0 && v6.y == 8.0);
  
  // Scalar division
  Vec2 v7 = v1 / 2.0;
  assert(v7.x == 1.5 && v7.y == 2.0);
  
  // Negation
  Vec2 v8 = -v1;
  assert(v8.x == -3.0 && v8.y == -4.0);
  
  std::cout << "  ✓ Arithmetic tests passed\n";
}

void test_vec2_compound_assignment() {
  std::cout << "Testing Vec2 compound assignment...\n";
  
  Vec2 v{1.0, 2.0};
  
  v += Vec2{2.0, 3.0};
  assert(v.x == 3.0 && v.y == 5.0);
  
  v -= Vec2{1.0, 1.0};
  assert(v.x == 2.0 && v.y == 4.0);
  
  v *= 2.0;
  assert(v.x == 4.0 && v.y == 8.0);
  
  v /= 2.0;
  assert(v.x == 2.0 && v.y == 4.0);
  
  std::cout << "  ✓ Compound assignment tests passed\n";
}

void test_vec2_comparison() {
  std::cout << "Testing Vec2 comparison...\n";
  
  Vec2 v1{1.0, 2.0};
  Vec2 v2{1.0, 2.0};
  Vec2 v3{2.0, 3.0};
  
  assert(v1 == v2);
  assert(v1 != v3);
  assert(v1 < v3);  // Lexicographic comparison
  assert(v3 > v1);
  
  std::cout << "  ✓ Comparison tests passed\n";
}

void test_vec2_dot_product() {
  std::cout << "Testing Vec2 dot product...\n";
  
  Vec2 v1{3.0, 4.0};
  Vec2 v2{1.0, 0.0};
  
  double dot = v1.dot(v2);
  assert(dot == 3.0);
  
  // Perpendicular vectors
  Vec2 v3{1.0, 0.0};
  Vec2 v4{0.0, 1.0};
  assert(v3.dot(v4) == 0.0);
  
  // Parallel vectors
  Vec2 v5{2.0, 2.0};
  Vec2 v6{1.0, 1.0};
  assert(v5.dot(v6) == 4.0);  // 2*1 + 2*1
  
  std::cout << "  ✓ Dot product tests passed\n";
}

void test_vec2_cross_product() {
  std::cout << "Testing Vec2 cross product...\n";
  
  Vec2 v1{1.0, 0.0};
  Vec2 v2{0.0, 1.0};
  
  // Cross product (2D returns scalar z-component)
  double cross = v1.cross(v2);
  assert(cross == 1.0);  // Counter-clockwise
  
  double cross2 = v2.cross(v1);
  assert(cross2 == -1.0);  // Clockwise
  
  // Parallel vectors
  Vec2 v3{2.0, 0.0};
  assert(v1.cross(v3) == 0.0);
  
  std::cout << "  ✓ Cross product tests passed\n";
}

void test_vec2_length() {
  std::cout << "Testing Vec2 length...\n";
  
  Vec2 v1{3.0, 4.0};
  assert(v1.length() == 5.0);  // 3-4-5 triangle
  assert(v1.length_sq() == 25.0);
  
  Vec2 v2{1.0, 0.0};
  assert(v2.length() == 1.0);
  assert(v2.length_sq() == 1.0);
  
  Vec2 v3;
  assert(v3.length() == 0.0);
  assert(v3.length_sq() == 0.0);
  
  std::cout << "  ✓ Length tests passed\n";
}

void test_vec2_normalized() {
  std::cout << "Testing Vec2 normalization...\n";
  
  Vec2 v1{3.0, 4.0};
  Vec2 normalized = v1.normalized();
  assert(std::abs(normalized.length() - 1.0) < 1e-9);
  assert(std::abs(normalized.x - 0.6) < 1e-9);
  assert(std::abs(normalized.y - 0.8) < 1e-9);
  
  // Zero vector should remain zero
  Vec2 v2;
  Vec2 normalized_zero = v2.normalized();
  assert(normalized_zero.x == 0.0 && normalized_zero.y == 0.0);
  
  std::cout << "  ✓ Normalization tests passed\n";
}

void test_vec2_distance() {
  std::cout << "Testing Vec2 distance...\n";
  
  Vec2 v1{0.0, 0.0};
  Vec2 v2{3.0, 4.0};
  
  assert(v1.distance_to(v2) == 5.0);
  assert(v1.distance_sq_to(v2) == 25.0);
  assert(v2.distance_to(v1) == 5.0);  // Symmetric
  
  Vec2 v3{1.0, 1.0};
  assert(v3.distance_to(v3) == 0.0);
  
  std::cout << "  ✓ Distance tests passed\n";
}

void test_vec2_perpendicular() {
  std::cout << "Testing Vec2 perpendicular...\n";
  
  Vec2 v1{1.0, 0.0};
  Vec2 perp = v1.perpendicular();
  assert(perp.x == 0.0 && perp.y == 1.0);
  
  // Perpendicular should be perpendicular (dot product = 0)
  assert(v1.dot(perp) == 0.0);
  
  // Length should be preserved
  Vec2 v2{3.0, 4.0};
  Vec2 perp2 = v2.perpendicular();
  assert(std::abs(v2.length() - perp2.length()) < 1e-9);
  
  std::cout << "  ✓ Perpendicular tests passed\n";
}

void test_vec2_lerp() {
  std::cout << "Testing Vec2 lerp...\n";
  
  Vec2 v1{0.0, 0.0};
  Vec2 v2{10.0, 20.0};
  
  Vec2 lerp0 = v1.lerp(v2, 0.0);
  assert(lerp0 == v1);
  
  Vec2 lerp1 = v1.lerp(v2, 1.0);
  assert(lerp1 == v2);
  
  Vec2 lerp_mid = v1.lerp(v2, 0.5);
  assert(lerp_mid.x == 5.0 && lerp_mid.y == 10.0);
  
  std::cout << "  ✓ Lerp tests passed\n";
}

int main() {
  std::cout << "\n=== Running Vec2 Tests ===\n\n";
  
  test_vec2_construction();
  test_vec2_arithmetic();
  test_vec2_compound_assignment();
  test_vec2_comparison();
  test_vec2_dot_product();
  test_vec2_cross_product();
  test_vec2_length();
  test_vec2_normalized();
  test_vec2_distance();
  test_vec2_perpendicular();
  test_vec2_lerp();
  
  std::cout << "\n✓ All Vec2 tests passed!\n\n";
  return 0;
}
