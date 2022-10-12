#ifndef _GUILEMEMORY
#define _GUILEMEMORY

#include <cstdlib>
#include <new> // std::bad_alloc

extern "C" {
#include <libguile.h>
}

// Use Guile's garbage collector for C++ objects
// g++ NewDelete.cpp `pkg-config --cflags --libs guile-3.0`

// Overload the global new and delete
void *operator new(size_t size) {
  // std::cout << "Calling new" << std::endl;
  // void * ptr = scm_malloc(size);
  void *ptr = scm_gc_malloc(size, "");
  if (!ptr) {
    throw std::bad_alloc();
  } else {
    return ptr;
  }
}

void operator delete(void *ptr) noexcept {
  // std::cout << "Calling delete" << std::endl;
  // free(ptr);
}

// Allocates using Guile's garbage collection system
template <typename T> class GuileAllocator {
public:
  using value_type = T;

  GuileAllocator() = default;

  template <typename U> GuileAllocator(const GuileAllocator<U> &other) {
    (void)other;
  }

  T *allocate(size_t n) {
    auto ptr = static_cast<T *>(scm_gc_malloc(sizeof(T) * n, ""));
    if (ptr)
      return ptr;
    else
      throw std::bad_alloc();
  }

  void deallocate(T *ptr, size_t n) {
    (void)n;
    // free(ptr);
  }
};

#endif