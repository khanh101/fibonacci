#include "fibonacci.h"
#include <cassert>
#include <cstdlib>
#include <cstdint>
#include <gmpxx.h>

using Z = mpz_class; // integer
using Q = mpq_class; // rational

// quadratic field Q[√x] = {a + b √x: a ∈ Q, b ∈ Q}
template<int d>
struct QF {
  Q a;
  Q b;
  QF(Q a, Q b = 1) : a(a), b(b) {}
  ~QF() {}
  QF<d> operator+(const QF<d> &other) const {
    const Q& a1 = a;
    const Q& b1 = b;
    const Q& a2 = other.a;
    const Q& b2 = other.b;
    return QF<d>(a1 + a2, b1 + b2);
  }
  QF<d> operator-(const QF<d> &other) const {
    const Q& a1 = a;
    const Q& b1 = b;
    const Q& a2 = other.a;
    const Q& b2 = other.b;
    return QF<d>(a1 - a2, b1 - b2);
  }
  QF<d> operator*(const QF<d> &other) const {
    const Q& a1 = a;
    const Q& b1 = b;
    const Q& a2 = other.a;
    const Q& b2 = other.b;
    return QF<d>(a1 * a2 + b1 * b2 * d, a1 * b2 + b1 * a2);
  }
  QF<d> operator/(const QF<d> &other) const {
    const Q& a1 = a;
    const Q& b1 = b;
    const Q& a2 = other.a;
    const Q& b2 = other.b;
    Q den = a2 * a2 - b2 * b2 * d;
    return QF<d>((a1 * a2 - b1 * b2 * d)/den, (b1 * a2 - a1 * b2 * d)/den);
  }
  QF<d> pow(Z n) const {
    if (n == 0) {
      return QF<d>(1, 0);
    }
    if (n % 2 == 0) {
      auto half = pow(n / 2);
      return half * half;
    } else {
      return (*this) * pow(n - 1);
    }
  }
};

Z str_to_Z(char* s) {
  return Z(s, 16); // convert base 16 to mpz
}

char* Z_to_str(Z z) {
  std::string str = z.get_str(16);
  char* c_str = (char*) std::malloc(str.size() + 1);
  std::memcpy(c_str, str.c_str(), str.size());
  c_str[str.size()] = '\0';
  return c_str;
}

char* fibonacci(char* n_str) {
  QF<5> root5 = QF<5>(0, 1); // 0 + √5
  QF<5> phi = QF<5>(Q(1, 2), Q(1, 2)); // 1/2 + 1/2 √5
  QF<5> psi = QF<5>(Q(1, 2), Q(-1, 2)); // 1/2 - 1/2 √5

  Z n = str_to_Z(n_str);
  QF<5> m = (phi.pow(n) - psi.pow(n)) / root5;
  m.a.canonicalize();
  Z anum = m.a.get_num();
  return Z_to_str(anum);
}