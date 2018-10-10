#pragma once


namespace std {
  // basic version of std::make_unique
  template<typename T, typename... Ts>
  std::unique_ptr<T> make_unique(Ts&&... params) {
    return std::unique_ptr<T>(new T(std::forward<Ts>(params)...));
  }
}
