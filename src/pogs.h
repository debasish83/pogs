#ifndef POGS_H_
#define POGS_H_

#include <vector>
#include "prox_lib.h"

enum POGS_ORD { COL, ROW };

// Data structure for input to Pogs().
template <typename T, typename M>
struct PogsData {
  // Input.
  std::vector<FunctionObj<T> > f, g;
  const M A;
  size_t m, n;

  // Output.
  T *x, *y, *l, optval;

  // Parameters.
  T rho, abs_tol, rel_tol;
  unsigned int max_iter;
  bool quiet, adaptive_rho;

  // Factors
  M factors;

  // Constructor.
  PogsData(const M &A, size_t m, size_t n)
      : A(A), m(m), n(n), x(0), y(0), l(0), rho(1),
        abs_tol(static_cast<T>(1e-4)), rel_tol(static_cast<T>(1e-3)),
        max_iter(2000), quiet(false), adaptive_rho(true), factors(0) { }
};

// Pogs solver.
template <typename T, typename M>
int Pogs(PogsData<T, M> *pogs_data);

// Dense matrix type.
template <typename T, POGS_ORD O>
struct Dense {
  static const POGS_ORD Ord = O;
  T *val;
  Dense(T *val) : val(val) { }; 
};

// Sparse matrix type.
template <typename T, typename I, POGS_ORD O>
struct Sparse {
  static const POGS_ORD Ord = O;
  T *val;
  I *ptr;
  I *ind;
  I nnz;
  Sparse(T *val, I *ptr, I *ind, I nnz)
      : val(val), ptr(ptr), ind(ind), nnz(nnz) { };
};

// Factor allocation and freeing.
template <typename T, POGS_ORD O>
int AllocDenseFactors(PogsData<T, Dense<T, O> > *pogs_data);

template <typename T, POGS_ORD O>
void FreeDenseFactors(PogsData<T, Dense<T, O> > *pogs_data);

template <typename T, typename I, POGS_ORD O>
int AllocSparseFactors(PogsData<T, Sparse<T, I, O> > *pogs_data);

template <typename T, typename I, POGS_ORD O>
void FreeSparseFactors(PogsData<T, Sparse<T, I,O> > *pogs_data);

#endif  // POGS_H_

