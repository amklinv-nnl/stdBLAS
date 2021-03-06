/*
//@HEADER
// ************************************************************************
//
//                        Kokkos v. 2.0
//              Copyright (2019) Sandia Corporation
//
// Under the terms of Contract DE-AC04-94AL85000 with Sandia Corporation,
// the U.S. Government retains certain rights in this software. //
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
// 1. Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
//
// 3. Neither the name of the Corporation nor the names of the
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY SANDIA CORPORATION "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL SANDIA CORPORATION OR THE
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Questions? Contact Christian R. Trott (crtrott@sandia.gov)
//
// ************************************************************************
//@HEADER
*/

#ifndef LINALG_INCLUDE_EXPERIMENTAL___P1673_BITS_BLAS1_LINALG_COPY_HPP_
#define LINALG_INCLUDE_EXPERIMENTAL___P1673_BITS_BLAS1_LINALG_COPY_HPP_

namespace std {
namespace experimental {
inline namespace __p1673_version_0 {

namespace {

template<class in_vector_t,
         class out_vector_t>
void linalg_copy_rank_1(in_vector_t x,
                        out_vector_t y)
{
  for (ptrdiff_t i = 0; i < y.extent(0); ++i) {
    y(i) = x(i);
  }
}

template<class in_matrix_t,
         class out_matrix_t>
void linalg_copy_rank_2(in_matrix_t x,
                        out_matrix_t y)
{
  for (ptrdiff_t j = 0; j < y.extent(1); ++j) {
    for (ptrdiff_t i = 0; i < y.extent(0); ++i) {
      y(i,j) = x(i,j);
    }
  }
}

// TODO add mdarray specializations; needed so that out_object_t is
// not passed by value (which would be wrong for a container type like
// mdarray).

}

template<class in_object_t,
         class out_object_t>
void linalg_copy(in_object_t x,
                 out_object_t y)
{
  if constexpr (x.rank() == 1) {
    linalg_copy_rank_1(x, y);
  }
  else if constexpr (x.rank() == 2) {
    linalg_copy_rank_2(x, y);
  }
  else {
    static_assert("Not implemented");
  }
}

template<class ExecutionPolicy,
         class in_object_t,
         class out_object_t>
void linalg_copy(ExecutionPolicy&& /* exec */,
                 in_object_t x,
                 out_object_t y)
{
  linalg_copy(x, y);
}

// TODO add mdarray specializations

} // end inline namespace __p1673_version_0
} // end namespace experimental
} // end namespace std

#endif //LINALG_INCLUDE_EXPERIMENTAL___P1673_BITS_BLAS1_LINALG_COPY_HPP_
