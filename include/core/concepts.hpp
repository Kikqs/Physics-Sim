#pragma once
#ifndef SIM_CONCEPTS_HPP
#define SIM_CONCEPTS_HPP
// include/core/concepts.hpp
// Shared concepts used throughout the project

#include <concepts>

namespace sim {

/// Concept for types that can be used as scalars in mathematical operations
template<typename T>
concept Scalar = std::floating_point<T> || std::integral<T>;

} // namespace sim

#endif // SIM_CONCEPTS_HPP
