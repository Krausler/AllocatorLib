#pragma once

#include "Allocator/Allocator.h"

#include <vector>
#include <unordered_map>
#include <string>
#include <xstring>

template<typename Type>
using Vector = std::vector<Type, All::Allocator>;

template<typename KeyType, typename ValueType>
using HashMap = std::unordered_map<KeyType, ValueType, All::Allocator>;

//using String = std::basic_string<char, char_traits<char>, All::Allocator>;