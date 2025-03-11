#include "fibonacci.h"
#include <gmpxx.h>
#include <cassert>

// Q[√x] - a + b √x
template<int x>
struct QRX {
  mpq_class a;
  mpq_class b;
  QRX(mpq_class a, mpq_class b = 1) : a(a), b(b) {}
  ~QRX() {}
  QRX<x> operator+(const QRX<x> &other) const {
    const mpq_class& a1 = a;
    const mpq_class& b1 = b;
    const mpq_class& a2 = other.a;
    const mpq_class& b2 = other.b;
    return QRX<x>(a1 + a2, b1 + b2);
  }
  QRX<x> operator-(const QRX<x> &other) const {
    const mpq_class& a1 = a;
    const mpq_class& b1 = b;
    const mpq_class& a2 = other.a;
    const mpq_class& b2 = other.b;
    return QRX<x>(a1 - a2, b1 - b2);
  }
  QRX<x> operator*(const QRX<x> &other) const {
    const mpq_class& a1 = a;
    const mpq_class& b1 = b;
    const mpq_class& a2 = other.a;
    const mpq_class& b2 = other.b;
    return QRX<x>(a1 * a2 + b1 * b2 * x, a1 * b2 + b1 * a2);
  }
  QRX<x> operator/(const QRX<x> &other) const {
    const mpq_class& a1 = a;
    const mpq_class& b1 = b;
    const mpq_class& a2 = other.a;
    const mpq_class& b2 = other.b;
    mpq_class den = a2 * a2 - b2 * b2 * x;
    return QRX<x>((a1 * a2 - b1 * b2 * x)/den, (b1 * a2 - a1 * b2 * x)/den);
  }
  QRX<x> pow(mpz_class n) const {
    if (n == 0) {
      return QRX<x>(1, 0);
    }
    if (n == 1) {
      return *this;
    }
    if (n == 2) {
      return (*this) * (*this);
    }
    if (n % 2 == 0) {
      auto half = pow(n / 2);
      return half * half;
    } else {
      return (*this) * pow(n - 1);
    }
  }
};

char* fibonacci(char* n_str) {
  QRX<5> root5 = QRX<5>(0, 1); // 0 + √5
  QRX<5> phi = QRX<5>(mpq_class(1, 2), mpq_class(1, 2)); // 1/2 + 1/2 √5
  QRX<5> psi = QRX<5>(mpq_class(1, 2), mpq_class(-1, 2)); // 1/2 - 1/2 √5

  mpz_class n = mpz_class(n_str, 16); // convert base 16 to mpz
  QRX<5> m = (phi.pow(n) - psi.pow(n)) / root5;
  std::string m_str = m.a.get_num().get_str(16);
  uint64_t len = std::strlen(m_str.c_str());
  char* m_str_out = (char*) std::malloc((1 + len) * sizeof(char));
  std::memcpy(m_str_out, m_str.c_str(), len);
  m_str_out[len] = '\0';
  return m_str_out;
}