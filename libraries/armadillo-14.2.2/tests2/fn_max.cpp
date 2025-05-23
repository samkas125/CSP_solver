// SPDX-License-Identifier: Apache-2.0
// 
// Copyright 2011-2017 Ryan Curtin (http://www.ratml.org/)
// Copyright 2017 National ICT Australia (NICTA)
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ------------------------------------------------------------------------

#include <armadillo>

#include "catch.hpp"

using namespace arma;

TEST_CASE("fn_max_subview_test")
  {
  // We will assume subview.at() works and returns points within the bounds of
  // the matrix, so we just have to ensure the results are the same as
  // Mat.max()...
  for (size_t r = 50; r < 150; ++r)
    {
    mat x(r, r, fill::randn);

    uword x_max          = x.index_max();
    uword x_subview_max1 = x.submat(0, 0, r - 1, r - 1).index_max();
    uword x_subview_max2 = x.cols(0, r - 1).index_max();
    uword x_subview_max3 = x.rows(0, r - 1).index_max();

    const double mval  = x.max();
    const double mval1 = x.submat(0, 0, r - 1, r - 1).max();
    const double mval2 = x.cols(0, r - 1).max();
    const double mval3 = x.rows(0, r - 1).max();

    REQUIRE( x_max == x_subview_max1 );
    REQUIRE( x_max == x_subview_max2 );
    REQUIRE( x_max == x_subview_max3 );

    REQUIRE( mval == Approx(mval1) );
    REQUIRE( mval == Approx(mval2) );
    REQUIRE( mval == Approx(mval3) );

    REQUIRE( mval == Approx(x(x_max)) );
    }
  }



TEST_CASE("fn_max_subview_col_test")
  {
  for (size_t r = 10; r < 50; ++r)
    {
    vec x(r, fill::randn);

    uword x_max          = x.index_max();
    uword x_subview_max1 = x.submat(0, 0, r - 1, 0).index_max();
    uword x_subview_max2 = x.rows(0, r - 1).index_max();

    const double mval  = x.max();
    const double mval1 = x.submat(0, 0, r - 1, 0).max();
    const double mval2 = x.rows(0, r - 1).max();

    REQUIRE( x_max == x_subview_max1 );
    REQUIRE( x_max == x_subview_max2 );

    REQUIRE( mval == Approx(mval1) );
    REQUIRE( mval == Approx(mval2) );

    REQUIRE( mval == Approx(x(x_max)) );
    }
  }



TEST_CASE("fn_max_subview_row_test")
  {
  for (size_t r = 10; r < 50; ++r)
    {
    rowvec x(r, fill::randn);

    uword x_max          = x.index_max();
    uword x_subview_max1 = x.submat(0, 0, 0, r - 1).index_max();
    uword x_subview_max2 = x.cols(0, r - 1).index_max();

    const double mval  = x.max();
    const double mval1 = x.submat(0, 0, 0, r - 1).max();
    const double mval2 = x.cols(0, r - 1).max();

    REQUIRE( x_max == x_subview_max1 );
    REQUIRE( x_max == x_subview_max2 );

    REQUIRE( mval == Approx(mval1) );
    REQUIRE( mval == Approx(mval2) );

    REQUIRE( mval == Approx(x(x_max)) );
    }
  }



// TEST_CASE("fn_max_incomplete_subview_test")
//   {
//   for (size_t r = 50; r < 150; ++r)
//     {
//     mat x(r, r, fill::randn);
// 
//     uword x_max;
//     uword x_subview_max1;
//     uword x_subview_max2;
//     uword x_subview_max3;
// 
//     const double mval = x.max(x_max);
//     const double mval1 = x.submat(1, 1, r - 2, r - 2).max(x_subview_max1);
//     const double mval2 = x.cols(1, r - 2).max(x_subview_max2);
//     const double mval3 = x.rows(1, r - 2).max(x_subview_max3);
// 
//     uword row, col;
//     x.max(row, col);
// 
//     if (row != 0 && row != r - 1 && col != 0 && col != r - 1)
//       {
//       uword srow, scol;
// 
//       srow = x_subview_max1 % (r - 2);
//       scol = x_subview_max1 / (r - 2);
//       REQUIRE( x_max == (srow + 1) + r * (scol + 1) );
//       REQUIRE( x_max == x_subview_max2 + r );
// 
//       srow = x_subview_max3 % (r - 2);
//       scol = x_subview_max3 / (r - 2);
//       REQUIRE( x_max == (srow + 1) + r * scol );
// 
//       REQUIRE( mval == Approx(mval1) );
//       REQUIRE( mval == Approx(mval2) );
//       REQUIRE( mval == Approx(mval3) );
//       }
//     }
//   }



TEST_CASE("fn_max_incomplete_subview_col_test")
  {
  for (size_t r = 10; r < 50; ++r)
    {
    vec x(r, fill::randn);

    uword x_max          = x.index_max();
    uword x_subview_max1 = x.submat(1, 0, r - 2, 0).index_max();
    uword x_subview_max2 = x.rows(1, r - 2).index_max();

    const double mval  = x.max();
    const double mval1 = x.submat(1, 0, r - 2, 0).max();
    const double mval2 = x.rows(1, r - 2).max();

    if (x_max != 0 && x_max != r - 1)
      {
      REQUIRE( x_max == x_subview_max1 + 1 );
      REQUIRE( x_max == x_subview_max2 + 1 );

      REQUIRE( mval == Approx(mval1) );
      REQUIRE( mval == Approx(mval2) );

      REQUIRE( mval == Approx(x(x_max)) );
      }
    }
  }



TEST_CASE("fn_max_cx_subview_row_test")
  {
  for (size_t r = 10; r < 50; ++r)
    {
    cx_rowvec x(r, fill::randn);

    uword x_max          = x.index_max();
    uword x_subview_max1 = x.submat(0, 0, 0, r - 1).index_max();
    uword x_subview_max2 = x.cols(0, r - 1).index_max();

    const std::complex<double> mval  = x.max();
    const std::complex<double> mval1 = x.submat(0, 0, 0, r - 1).max();
    const std::complex<double> mval2 = x.cols(0, r - 1).max();

    REQUIRE( x_max == x_subview_max1 );
    REQUIRE( x_max == x_subview_max2 );

    REQUIRE( mval.real() == Approx(mval1.real()) );
    REQUIRE( mval.imag() == Approx(mval1.imag()) );
    REQUIRE( mval.real() == Approx(mval2.real()) );
    REQUIRE( mval.imag() == Approx(mval2.imag()) );

    REQUIRE( mval.real() == Approx(x(x_max).real()) );
    REQUIRE( mval.imag() == Approx(x(x_max).imag()) );
    }
  }



// TEST_CASE("fn_max_cx_incomplete_subview_test")
//   {
//   for (size_t r = 50; r < 150; ++r)
//     {
//     cx_mat x(r, r, fill::randn);
// 
//     uword x_max;
//     uword x_subview_max1;
//     uword x_subview_max2;
//     uword x_subview_max3;
// 
//     const std::complex<double> mval = x.max(x_max);
//     const std::complex<double> mval1 = x.submat(1, 1, r - 2, r - 2).max(x_subview_max1);
//     const std::complex<double> mval2 = x.cols(1, r - 2).max(x_subview_max2);
//     const std::complex<double> mval3 = x.rows(1, r - 2).max(x_subview_max3);
// 
//     uword row, col;
//     x.max(row, col);
// 
//     if (row != 0 && row != r - 1 && col != 0 && col != r - 1)
//       {
//       uword srow, scol;
// 
//       srow = x_subview_max1 % (r - 2);
//       scol = x_subview_max1 / (r - 2);
//       REQUIRE( x_max == (srow + 1) + r * (scol + 1) );
//       REQUIRE( x_max == x_subview_max2 + r );
// 
//       srow = x_subview_max3 % (r - 2);
//       scol = x_subview_max3 / (r - 2);
//       REQUIRE( x_max == (srow + 1) + r * scol );
// 
//       REQUIRE( mval.real() == Approx(mval1.real()) );
//       REQUIRE( mval.imag() == Approx(mval1.imag()) );
//       REQUIRE( mval.real() == Approx(mval2.real()) );
//       REQUIRE( mval.imag() == Approx(mval2.imag()) );
//       REQUIRE( mval.real() == Approx(mval3.real()) );
//       REQUIRE( mval.imag() == Approx(mval3.imag()) );
//       }
//     }
//   }



TEST_CASE("fn_max_cx_incomplete_subview_col_test")
  {
  for (size_t r = 10; r < 50; ++r)
    {
    cx_vec x(r, fill::randn);

    uword x_max          = x.index_max();
    uword x_subview_max1 = x.submat(1, 0, r - 2, 0).index_max();
    uword x_subview_max2 = x.rows(1, r - 2).index_max();

    const std::complex<double> mval  = x.max();
    const std::complex<double> mval1 = x.submat(1, 0, r - 2, 0).max();
    const std::complex<double> mval2 = x.rows(1, r - 2).max();

    if (x_max != 0 && x_max != r - 1)
      {
      REQUIRE( x_max == x_subview_max1 + 1 );
      REQUIRE( x_max == x_subview_max2 + 1 );

      REQUIRE( mval.real() == Approx(mval1.real()) );
      REQUIRE( mval.imag() == Approx(mval1.imag()) );
      REQUIRE( mval.real() == Approx(mval2.real()) );
      REQUIRE( mval.imag() == Approx(mval2.imag()) );

      REQUIRE( mval.real() == Approx(x(x_max).real()) );
      REQUIRE( mval.imag() == Approx(x(x_max).imag()) );
      }
    }
  }



TEST_CASE("fn_max_cx_incomplete_subview_row_test")
  {
  for (size_t r = 10; r < 50; ++r)
    {
    cx_rowvec x(r, fill::randn);

    uword x_max          = x.index_max();
    uword x_subview_max1 = x.submat(0, 1, 0, r - 2).index_max();
    uword x_subview_max2 = x.cols(1, r - 2).index_max();

    const std::complex<double> mval  = x.max();
    const std::complex<double> mval1 = x.submat(0, 1, 0, r - 2).max();
    const std::complex<double> mval2 = x.cols(1, r - 2).max();

    if (x_max != 0 && x_max != r - 1)
      {
      REQUIRE( x_max == x_subview_max1 + 1 );
      REQUIRE( x_max == x_subview_max2 + 1 );

      REQUIRE( mval.real() == Approx(mval1.real()) );
      REQUIRE( mval.imag() == Approx(mval1.imag()) );
      REQUIRE( mval.real() == Approx(mval2.real()) );
      REQUIRE( mval.imag() == Approx(mval2.imag()) );

      REQUIRE( mval.real() == Approx(x(x_max).real()) );
      REQUIRE( mval.imag() == Approx(x(x_max).imag()) );
      }
    }
  }



TEST_CASE("fn_max_weird_operation")
  {
  mat a(10, 10, fill::randn);
  mat b(25, 10, fill::randn);

  mat output = a * b.t();

  uword real_max      = output.index_max();
  uword operation_max = (a * b.t()).index_max();

  const double mval       = output.max();
  const double other_mval = (a * b.t()).max();

  REQUIRE( real_max == operation_max            );
  REQUIRE( mval     == Approx(other_mval)       );
  REQUIRE( mval     == Approx(output(real_max)) );
  }



TEST_CASE("fn_max_weird_sparse_operation")
  {
  sp_mat a; a.sprandn(10, 10, 0.3);
  sp_mat b; b.sprandn(25, 10, 0.3);

  sp_mat output = a * b.t();

  uword real_max      =      output.index_max();
  uword operation_max = (a * b.t()).index_max();

  const double mval       =      output.max();
  const double other_mval = (a * b.t()).max();

  REQUIRE( real_max == operation_max            );
  REQUIRE( mval     == Approx(other_mval)       );
  REQUIRE( mval     == Approx(output(real_max)) );
  }



TEST_CASE("fn_max_sp_subview_test")
  {
  // We will assume subview.at() works and returns points within the bounds of
  // the matrix, so we just have to ensure the results are the same as
  // Mat.max()...
  for (size_t r = 50; r < 150; ++r)
    {
    sp_mat x;  x.sprandn(r, r, 0.3);

    uword x_max          = x.index_max();
    uword x_subview_max1 = x.submat(0, 0, r - 1, r - 1).index_max();
    uword x_subview_max2 = x.cols(0, r - 1).index_max();
    uword x_subview_max3 = x.rows(0, r - 1).index_max();

    const double mval  = x.max();
    const double mval1 = x.submat(0, 0, r - 1, r - 1).max();
    const double mval2 = x.cols(0, r - 1).max();
    const double mval3 = x.rows(0, r - 1).max();

    if (mval != 0.0)
      {
      REQUIRE( x_max == x_subview_max1 );
      REQUIRE( x_max == x_subview_max2 );
      REQUIRE( x_max == x_subview_max3 );

      REQUIRE( mval == Approx(mval1) );
      REQUIRE( mval == Approx(mval2) );
      REQUIRE( mval == Approx(mval3) );
      
      REQUIRE( mval == Approx(x(x_max)) );
      }
    }
  }



TEST_CASE("fn_max_spsubview_col_test")
  {
  for (size_t r = 10; r < 50; ++r)
    {
    sp_vec x;  x.sprandn(r, 1, 0.3);

    uword x_max          = x.index_max();
    uword x_subview_max1 = x.submat(0, 0, r - 1, 0).index_max();
    uword x_subview_max2 = x.rows(0, r - 1).index_max();

    const double mval  = x.max();
    const double mval1 = x.submat(0, 0, r - 1, 0).max();
    const double mval2 = x.rows(0, r - 1).max();

    if (mval != 0.0)
      {
      REQUIRE( x_max == x_subview_max1 );
      REQUIRE( x_max == x_subview_max2 );

      REQUIRE( mval == Approx(mval1) );
      REQUIRE( mval == Approx(mval2) );
      
      REQUIRE( mval == Approx(x(x_max)) );
      }
    }
  }



TEST_CASE("fn_max_spsubview_row_max_test")
  {
  for (size_t r = 10; r < 50; ++r)
    {
    sp_rowvec x;  x.sprandn(1, r, 0.3);

    uword x_max          = x.index_max();
    uword x_subview_max1 = x.submat(0, 0, 0, r - 1).index_max();
    uword x_subview_max2 = x.cols(0, r - 1).index_max();

    const double mval  = x.max();
    const double mval1 = x.submat(0, 0, 0, r - 1).max();
    const double mval2 = x.cols(0, r - 1).max();

    if (mval != 0.0)
      {
      REQUIRE( x_max == x_subview_max1 );
      REQUIRE( x_max == x_subview_max2 );

      REQUIRE( mval == Approx(mval1) );
      REQUIRE( mval == Approx(mval2) );
      
      REQUIRE( mval == Approx(x(x_max)) );
      }
    }
  }



// TEST_CASE("fn_max_spincompletesubview_max_test")
//   {
//   for (size_t r = 50; r < 150; ++r)
//     {
//     sp_mat x;
//     x.sprandn(r, r, 0.3);
// 
//     uword x_max;
//     uword x_subview_max1;
//     uword x_subview_max2;
//     uword x_subview_max3;
// 
//     const double mval = x.max(x_max);
//     const double mval1 = x.submat(1, 1, r - 2, r - 2).max(x_subview_max1);
//     const double mval2 = x.cols(1, r - 2).max(x_subview_max2);
//     const double mval3 = x.rows(1, r - 2).max(x_subview_max3);
// 
//     uword row, col;
//     x.max(row, col);
// 
//     if (row != 0 && row != r - 1 && col != 0 && col != r - 1 && mval != 0.0)
//       {
//       uword srow, scol;
// 
//       srow = x_subview_max1 % (r - 2);
//       scol = x_subview_max1 / (r - 2);
//       REQUIRE( x_max == (srow + 1) + r * (scol + 1) );
//       REQUIRE( x_max == x_subview_max2 + r );
// 
//       srow = x_subview_max3 % (r - 2);
//       scol = x_subview_max3 / (r - 2);
//       REQUIRE( x_max == (srow + 1) + r * scol );
// 
//       REQUIRE( mval == Approx(mval1) );
//       REQUIRE( mval == Approx(mval2) );
//       REQUIRE( mval == Approx(mval3) );
//       }
//     }
//   }



TEST_CASE("fn_max_spincompletesubview_col_max_test")
  {
  for (size_t r = 10; r < 50; ++r)
    {
    sp_vec x;  x.sprandu(r, 1, 0.3);

    uword x_max          = x.index_max();
    uword x_subview_max1 = x.submat(1, 0, r - 2, 0).index_max();
    uword x_subview_max2 = x.rows(1, r - 2).index_max();

    const double mval  = x.max();
    const double mval1 = x.submat(1, 0, r - 2, 0).max();
    const double mval2 = x.rows(1, r - 2).max();

    if (x_max != 0 && x_max != r - 1 && mval != 0.0)
      {
      REQUIRE( x_max == x_subview_max1 + 1 );
      REQUIRE( x_max == x_subview_max2 + 1 );

      REQUIRE( mval == Approx(mval1) );
      REQUIRE( mval == Approx(mval2) );
      
      REQUIRE( mval == Approx(x(x_max)));
      }
    }
  }



TEST_CASE("fn_max_spincompletesubview_row_max_test")
  {
  for (size_t r = 10; r < 50; ++r)
    {
    sp_rowvec x;  x.sprandn(1, r, 0.3);

    uword x_max          = x.index_max();
    uword x_subview_max1 = x.submat(0, 1, 0, r - 2).index_max();
    uword x_subview_max2 = x.cols(1, r - 2).index_max();

    const double mval  = x.max();
    const double mval1 = x.submat(0, 1, 0, r - 2).max();
    const double mval2 = x.cols(1, r - 2).max();

    if (mval != 0.0 && x_max != 0 && x_max != r - 1)
      {
      REQUIRE( x_max == x_subview_max1 + 1 );
      REQUIRE( x_max == x_subview_max2 + 1 );

      REQUIRE( mval == Approx(mval1) );
      REQUIRE( mval == Approx(mval2) );

      REQUIRE( mval == Approx( x(x_max) ) );
      }
    }
  }



TEST_CASE("fn_max_sp_cx_subview_max_test")
  {
  // We will assume subview.at() works and returns points within the bounds of
  // the matrix, so we just have to ensure the results are the same as
  // Mat.max()...
  for (size_t r = 50; r < 150; ++r)
    {
    sp_cx_mat x;  x.sprandn(r, r, 0.3);

    uword x_max          = x.index_max();
    uword x_subview_max1 = x.submat(0, 0, r - 1, r - 1).index_max();
    uword x_subview_max2 = x.cols(0, r - 1).index_max();
    uword x_subview_max3 = x.rows(0, r - 1).index_max();

    const std::complex<double> mval  = x.max();
    const std::complex<double> mval1 = x.submat(0, 0, r - 1, r - 1).max();
    const std::complex<double> mval2 = x.cols(0, r - 1).max();
    const std::complex<double> mval3 = x.rows(0, r - 1).max();

    if (mval != std::complex<double>(0.0))
      {
      REQUIRE( x_max == x_subview_max1 );
      REQUIRE( x_max == x_subview_max2 );
      REQUIRE( x_max == x_subview_max3 );

      REQUIRE( mval.real() == Approx(mval1.real()) );
      REQUIRE( mval.imag() == Approx(mval1.imag()) );
      REQUIRE( mval.real() == Approx(mval2.real()) );
      REQUIRE( mval.imag() == Approx(mval2.imag()) );
      REQUIRE( mval.real() == Approx(mval3.real()) );
      REQUIRE( mval.imag() == Approx(mval3.imag()) );

      REQUIRE( mval.real() == Approx(x(x_max).real()) );
      REQUIRE( mval.imag() == Approx(x(x_max).imag()) );
      }
    }
  }



TEST_CASE("fn_max_sp_cx_subview_col_max_test")
  {
  for (size_t r = 10; r < 50; ++r)
    {
    sp_cx_vec x;  x.sprandn(r, 1, 0.3);

    uword x_max          = x.index_max();
    uword x_subview_max1 = x.submat(0, 0, r - 1, 0).index_max();
    uword x_subview_max2 = x.rows(0, r - 1).index_max();

    const std::complex<double> mval  = x.max();
    const std::complex<double> mval1 = x.submat(0, 0, r - 1, 0).max();
    const std::complex<double> mval2 = x.rows(0, r - 1).max();

    if (mval != std::complex<double>(0.0))
      {
      REQUIRE( x_max == x_subview_max1 );
      REQUIRE( x_max == x_subview_max2 );

      REQUIRE( mval.real() == Approx(mval1.real()) );
      REQUIRE( mval.imag() == Approx(mval1.imag()) );
      REQUIRE( mval.real() == Approx(mval2.real()) );
      REQUIRE( mval.imag() == Approx(mval2.imag()) );

      REQUIRE( mval.real() == Approx(x(x_max).real()) );
      REQUIRE( mval.imag() == Approx(x(x_max).imag()) );
      }
    }
  }



TEST_CASE("fn_max_sp_cx_subview_row_max_test")
  {
  for (size_t r = 10; r < 50; ++r)
    {
    sp_cx_rowvec x;  x.sprandn(1, r, 0.3);

    uword x_max          = x.index_max();
    uword x_subview_max1 = x.submat(0, 0, 0, r - 1).index_max();
    uword x_subview_max2 = x.cols(0, r - 1).index_max();

    const std::complex<double> mval  = x.max();
    const std::complex<double> mval1 = x.submat(0, 0, 0, r - 1).max();
    const std::complex<double> mval2 = x.cols(0, r - 1).max();

    if (mval != std::complex<double>(0.0))
      {
      REQUIRE( x_max == x_subview_max1 );
      REQUIRE( x_max == x_subview_max2 );

      REQUIRE( mval.real() == Approx(mval1.real()) );
      REQUIRE( mval.imag() == Approx(mval1.imag()) );
      REQUIRE( mval.real() == Approx(mval2.real()) );
      REQUIRE( mval.imag() == Approx(mval2.imag()) );

      REQUIRE( mval.real() == Approx(x(x_max).real()) );
      REQUIRE( mval.imag() == Approx(x(x_max).imag()) );
      }
    }
  }



// TEST_CASE("fn_max_sp_cx_incomplete_subview_max_test")
//   {
//   for (size_t r = 50; r < 150; ++r)
//     {
//     sp_cx_mat x;
//     x.sprandn(r, r, 0.3);
// 
//     uword x_max;
//     uword x_subview_max1;
//     uword x_subview_max2;
//     uword x_subview_max3;
// 
//     const std::complex<double> mval = x.max(x_max);
//     const std::complex<double> mval1 = x.submat(1, 1, r - 2, r - 2).max(x_subview_max1);
//     const std::complex<double> mval2 = x.cols(1, r - 2).max(x_subview_max2);
//     const std::complex<double> mval3 = x.rows(1, r - 2).max(x_subview_max3);
// 
//     uword row, col;
//     x.max(row, col);
// 
//     if (row != 0 && row != r - 1 && col != 0 && col != r - 1 && mval != std::complex<double>(0.0))
//       {
//       uword srow, scol;
// 
//       srow = x_subview_max1 % (r - 2);
//       scol = x_subview_max1 / (r - 2);
//       REQUIRE( x_max == (srow + 1) + r * (scol + 1) );
//       REQUIRE( x_max == x_subview_max2 + r );
// 
//       srow = x_subview_max3 % (r - 2);
//       scol = x_subview_max3 / (r - 2);
//       REQUIRE( x_max == (srow + 1) + r * scol );
// 
//       REQUIRE( mval.real() == Approx(mval1.real()) );
//       REQUIRE( mval.imag() == Approx(mval1.imag()) );
//       REQUIRE( mval.real() == Approx(mval2.real()) );
//       REQUIRE( mval.imag() == Approx(mval2.imag()) );
//       REQUIRE( mval.real() == Approx(mval3.real()) );
//       REQUIRE( mval.imag() == Approx(mval3.imag()) );
//       }
//     }
//   }



TEST_CASE("fn_max_sp_cx_incomplete_subview_col_max_test")
  {
  for (size_t r = 10; r < 50; ++r)
    {
    arma::sp_cx_vec x;  x.sprandn(r, 1, 0.3);

    uword x_max          = x.index_max();
    uword x_subview_max1 = x.submat(1, 0, r - 2, 0).index_max();
    uword x_subview_max2 = x.rows(1, r - 2).index_max();

    const std::complex<double> mval  = x.max();
    const std::complex<double> mval1 = x.submat(1, 0, r - 2, 0).max();
    const std::complex<double> mval2 = x.rows(1, r - 2).max();

    if (x_max != 0 && x_max != r - 1 && mval != std::complex<double>(0.0))
      {
      REQUIRE( x_max == x_subview_max1 + 1 );
      REQUIRE( x_max == x_subview_max2 + 1 );

      REQUIRE( mval.real() == Approx(mval1.real()) );
      REQUIRE( mval.imag() == Approx(mval1.imag()) );
      REQUIRE( mval.real() == Approx(mval2.real()) );
      REQUIRE( mval.imag() == Approx(mval2.imag()) );

      REQUIRE( mval.real() == Approx(x(x_max).real()) );
      REQUIRE( mval.imag() == Approx(x(x_max).imag()) );
      }
    }
  }



TEST_CASE("fn_max_sp_cx_incomplete_subview_row_max_test")
  {
  for (size_t r = 10; r < 50; ++r)
    {
    sp_cx_rowvec x;  x.sprandn(1, r, 0.3);

    uword x_max          = x.index_max();
    uword x_subview_max1 = x.submat(0, 1, 0, r - 2).index_max();
    uword x_subview_max2 = x.cols(1, r - 2).index_max();

    const std::complex<double> mval  = x.max();
    const std::complex<double> mval1 = x.submat(0, 1, 0, r - 2).max();
    const std::complex<double> mval2 = x.cols(1, r - 2).max();

    if (x_max != 0 && x_max != r - 1 && mval != std::complex<double>(0.0))
      {
      REQUIRE( x_max == x_subview_max1 + 1 );
      REQUIRE( x_max == x_subview_max2 + 1 );

      REQUIRE( mval.real() == Approx(mval1.real()) );
      REQUIRE( mval.imag() == Approx(mval1.imag()) );
      REQUIRE( mval.real() == Approx(mval2.real()) );
      REQUIRE( mval.imag() == Approx(mval2.imag()) );

      REQUIRE( mval.real() == Approx(x(x_max).real()) );
      REQUIRE( mval.imag() == Approx(x(x_max).imag()) );
      }
    }
  }
