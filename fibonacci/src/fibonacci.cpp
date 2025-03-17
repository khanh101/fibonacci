#include "fibonacci.h"
#include <cassert>
#include <cstdlib>
#include <gmpxx.h>

// TODO - add more algebraic structures: Ring, Euclidean Domain, Polynomial ring, Matrix ring, Finite Field, etc
// TODO - add some number theory algorithms
// TODO - add some coding algorithms: ReedSolomon code, algebraic geometry code

using Z = mpz_class; // integer
using Q = mpq_class; // rational

// Z[√d]
template<int d>
struct ZRD {
  Z a;
  Z b;
  ZRD(Z a, Z b = 0): a(a), b(b) {}
  ~ZRD() {}
  static ZRD one() {
    return ZRD(1, 0);
  }
  ZRD operator*(const ZRD& other) const {
    const Z& a1 = a;
    const Z& b1 = b;
    const Z& a2 = other.a;
    const Z& b2 = other.b;
    return ZRD(a1 * a2 + b1 * b2 * d, a1 * b2 + b1 * a2);
  }

  ZRD pow(Z n) const {
    if (n < 0) {
      throw std::runtime_error("n < 0 not implemented");
    }
    if (n == 0) {
      return ZRD(1, 0);
    }
    if (n % 2 == 0) {
      auto half = pow(n / 2);
      return half * half;
    } else {
      return (*this) * pow(n - 1);
    }
  }
};

// quadratic field F(√d) = Frac(F[√d]) = F[√d] = {a + b √d: a ∈ Q, b ∈ Q}
// where F is a field
template<class F, int d>
struct QuadraticField {
  F a;
  F b;
  QuadraticField(F a, F b = 0): a(a), b(b) {}
  ~QuadraticField() {}
  static QuadraticField<F, d> zero() {
    return QuadraticField<F, d>(0, 0);
  }
  static QuadraticField<F, d> one() {
    return QuadraticField<F, d>(1, 0);
  }

  QuadraticField<F, d> operator+(const QuadraticField<F, d> &other) const {
    const F& a1 = a;
    const F& b1 = b;
    const F& a2 = other.a;
    const F& b2 = other.b;
    return QuadraticField<F, d>(a1 + a2, b1 + b2);
  }
  QuadraticField<F, d> operator-(const QuadraticField<F, d> &other) const {
    const F& a1 = a;
    const F& b1 = b;
    const F& a2 = other.a;
    const F& b2 = other.b;
    return QuadraticField<F, d>(a1 - a2, b1 - b2);
  }
  QuadraticField<F, d> operator*(const QuadraticField<F, d> &other) const {
    const F& a1 = a;
    const F& b1 = b;
    const F& a2 = other.a;
    const F& b2 = other.b;
    return QuadraticField<F, d>(a1 * a2 + b1 * b2 * d, a1 * b2 + b1 * a2);
  }
  QuadraticField<F, d> operator/(const QuadraticField<F, d> &other) const {
    const F& a1 = a;
    const F& b1 = b;
    const F& a2 = other.a;
    const F& b2 = other.b;
    F den = a2 * a2 - b2 * b2 * d;
    return QuadraticField<F, d>((a1 * a2 - b1 * b2 * d)/den, (b1 * a2 - a1 * b2 * d)/den);
  }
  QuadraticField<F, d> pow(Z n) const {
    if (n < 0) {
      return one() / pow(-n);
    }
    if (n == 0) {
      return QuadraticField<F, d>(1, 0);
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

char* fibonacci_faster(char* n_str) {
  Z n = str_to_Z(n_str);
  ZRD<5> phi = ZRD<5>(1, 1); // 1 + √5
  ZRD<5> m = phi.pow(n);
  Z result;
  mpz_div_2exp(result.get_mpz_t(), m.b.get_mpz_t(), n.get_ui()-1); // result = b / 2^n
  return Z_to_str(result);
}

char* fibonacci(char* n_str) {
  QuadraticField<Q, 5> root5 = QuadraticField<Q, 5>(0, 1); // 0 + √5
  QuadraticField<Q, 5> phi = QuadraticField<Q, 5>(Q(1, 2), Q(1, 2)); // 1/2 + 1/2 √5
  QuadraticField<Q, 5> psi = QuadraticField<Q, 5>(Q(1, 2), Q(-1, 2)); // 1/2 - 1/2 √5

  Z n = str_to_Z(n_str);
  QuadraticField<Q, 5> m = (phi.pow(n) - psi.pow(n)) / root5;
  m.a.canonicalize();
  Z anum = m.a.get_num();
  return Z_to_str(anum);
}