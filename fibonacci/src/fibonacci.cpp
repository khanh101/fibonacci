#include "fibonacci.h"
#include <cassert>
#include <cstdlib>
#include <gmpxx.h>

// TODO - add more algebraic structures: Ring, Euclidean Domain, Polynomial ring, Matrix ring, Finite Field, etc
// TODO - add some number theory algorithms
// TODO - add some coding algorithms: ReedSolomon code, algebraic geometry code

using Z = mpz_class; // integer
using Q = mpq_class; // rational

// quadratic field F(√d) = Frac(F[√d]) = F[√d] = {a + b √d: a ∈ Q, b ∈ Q}
// where F is a field
template<class F, int d>
struct QF {
  F a;
  F b;
  QF(F a, F b = 1) : a(a), b(b) {}
  ~QF() {}
  static QF<F, d> zero() {
    return QF<F, d>(0, 0);
  }
  static QF<F, d> one() {
    return QF<F, d>(1, 0);
  }

  QF<F, d> operator+(const QF<F, d> &other) const {
    const F& a1 = a;
    const F& b1 = b;
    const F& a2 = other.a;
    const F& b2 = other.b;
    return QF<F, d>(a1 + a2, b1 + b2);
  }
  QF<F, d> operator-(const QF<F, d> &other) const {
    const F& a1 = a;
    const F& b1 = b;
    const F& a2 = other.a;
    const F& b2 = other.b;
    return QF<F, d>(a1 - a2, b1 - b2);
  }
  QF<F, d> operator*(const QF<F, d> &other) const {
    const F& a1 = a;
    const F& b1 = b;
    const F& a2 = other.a;
    const F& b2 = other.b;
    return QF<F, d>(a1 * a2 + b1 * b2 * d, a1 * b2 + b1 * a2);
  }
  QF<F, d> operator/(const QF<F, d> &other) const {
    const F& a1 = a;
    const F& b1 = b;
    const F& a2 = other.a;
    const F& b2 = other.b;
    F den = a2 * a2 - b2 * b2 * d;
    return QF<F, d>((a1 * a2 - b1 * b2 * d)/den, (b1 * a2 - a1 * b2 * d)/den);
  }
  QF<F, d> pow(Z n) const {
    if (n < 0) {
      return one() / pow(-n);
    }
    if (n == 0) {
      return QF<F, d>(1, 0);
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
  QF<Q, 5> root5 = QF<Q, 5>(0, 1); // 0 + √5
  QF<Q, 5> phi = QF<Q, 5>(Q(1, 2), Q(1, 2)); // 1/2 + 1/2 √5
  QF<Q, 5> psi = QF<Q, 5>(Q(1, 2), Q(-1, 2)); // 1/2 - 1/2 √5

  Z n = str_to_Z(n_str);
  QF<Q, 5> m = (phi.pow(n) - psi.pow(n)) / root5;
  m.a.canonicalize();
  Z anum = m.a.get_num();
  return Z_to_str(anum);
}