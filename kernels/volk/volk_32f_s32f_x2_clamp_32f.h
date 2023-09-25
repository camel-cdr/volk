/* -*- c++ -*- */
/*
 * Copyright 2023 Free Software Foundation, Inc.
 *
 * This file is part of VOLK
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */

/*!
 * \page volk_32fc_s32f_x2_clamp_32f
 *
 * \b Overview
 *
 * Clamps the values to an upper and a lower bound.
 *
 * <b>Dispatcher Prototype</b>
 * \code
 * void volk_32f_s32f_x2_clamp_32f(float* out,
 *              const float* in,
 *              const float min,
 *              const float max,
 *              unsigned int num_points) \endcode
 *
 * \b Inputs
 * \li in: Pointer to float values.
 * \li min: Minimum value to clamp to. \li max: Maximum value to clamp to. \li
 * num_points: The number of points in the vector.
 *
 * \b Outputs
 * \li out: Pointer to output values.
 *
 * \b Example
 * \code
 * float x[4] = {-2.f, -1.f, 1.f, 2.f};
 * float y[4];
 *
 * volk_32f_s32f_x2_clamp_32f(y, x, -1.5f, 1.5f, 4);
 * // Expect y = {-1.5f, -1.f, 1.f, 1.5f}
 *
 * \endcode
 */
#include <inttypes.h>

#ifndef INCLUDED_volk_32fc_s32f_x2_clamp_32f_a_H
#define INCLUDED_volk_32fc_s32f_x2_clamp_32f_a_H

#if LV_HAVE_AVX2
#include <immintrin.h>
static inline void volk_32f_s32f_x2_clamp_32f_a_avx2(float* out,
                                                     const float* in,
                                                     const float min,
                                                     const float max,
                                                     unsigned int num_points)
{
    const __m256 vmin = _mm256_set1_ps(min);
    const __m256 vmax = _mm256_set1_ps(max);

    uint32_t number = 0;
    uint32_t eighth_points = num_points / 8;
    for (; number < eighth_points; number++) {
        __m256 res = _mm256_load_ps(in);
        __m256 max_mask = _mm256_cmp_ps(vmax, res, _CMP_LT_OS);
        __m256 min_mask = _mm256_cmp_ps(res, vmin, _CMP_LT_OS);
        res = _mm256_blendv_ps(res, vmax, max_mask);
        res = _mm256_blendv_ps(res, vmin, min_mask);
        _mm256_store_ps(out, res);
        in += 8;
        out += 8;
    }

    number = eighth_points * 8;
    for (; number < num_points; number++) {
        *out++ = (*in > max) ? max : (*in < min) ? min : *in;
        in++;
    }
}
#endif /* LV_HAVE_AVX2 */

#if LV_HAVE_SSE4_1
#include <immintrin.h>
static inline void volk_32f_s32f_x2_clamp_32f_a_sse4_1(float* out,
                                                       const float* in,
                                                       const float min,
                                                       const float max,
                                                       unsigned int num_points)
{
    const __m128 vmin = _mm_set1_ps(min);
    const __m128 vmax = _mm_set1_ps(max);

    uint32_t number = 0;
    uint32_t quarter_points = num_points / 4;
    for (; number < quarter_points; number++) {
        __m128 res = _mm_load_ps(in);
        __m128 max_mask = _mm_cmplt_ps(vmax, res);
        __m128 min_mask = _mm_cmplt_ps(res, vmin);
        res = _mm_blendv_ps(res, vmax, max_mask);
        res = _mm_blendv_ps(res, vmin, min_mask);
        _mm_store_ps(out, res);
        in += 4;
        out += 4;
    }

    number = quarter_points * 4;
    for (; number < num_points; number++) {
        *out++ = (*in > max) ? max : (*in < min) ? min : *in;
        in++;
    }
}
#endif /* LV_HAVE_SSE4_1 */

#endif /* INCLUDED_volk_32fc_s32f_x2_clamp_32f_a_H */

#ifndef INCLUDED_volk_32fc_s32f_x2_clamp_32f_u_H
#define INCLUDED_volk_32fc_s32f_x2_clamp_32f_u_H

#if LV_HAVE_AVX2
#include <immintrin.h>
static inline void volk_32f_s32f_x2_clamp_32f_u_avx2(float* out,
                                                     const float* in,
                                                     const float min,
                                                     const float max,
                                                     unsigned int num_points)
{
    const __m256 vmin = _mm256_set1_ps(min);
    const __m256 vmax = _mm256_set1_ps(max);

    uint32_t number = 0;
    uint32_t eighth_points = num_points / 8;
    for (; number < eighth_points; number++) {
        __m256 res = _mm256_loadu_ps(in);
        __m256 max_mask = _mm256_cmp_ps(vmax, res, _CMP_LT_OS);
        __m256 min_mask = _mm256_cmp_ps(res, vmin, _CMP_LT_OS);
        res = _mm256_blendv_ps(res, vmax, max_mask);
        res = _mm256_blendv_ps(res, vmin, min_mask);
        _mm256_storeu_ps(out, res);
        in += 8;
        out += 8;
    }

    number = eighth_points * 8;
    for (; number < num_points; number++) {
        *out++ = (*in > max) ? max : (*in < min) ? min : *in;
        in++;
    }
}
#endif /* LV_HAVE_AVX2 */

#if LV_HAVE_SSE4_1
#include <immintrin.h>
static inline void volk_32f_s32f_x2_clamp_32f_u_sse4_1(float* out,
                                                       const float* in,
                                                       const float min,
                                                       const float max,
                                                       unsigned int num_points)
{
    const __m128 vmin = _mm_set1_ps(min);
    const __m128 vmax = _mm_set1_ps(max);

    uint32_t number = 0;
    uint32_t quarter_points = num_points / 4;
    for (; number < quarter_points; number++) {
        __m128 res = _mm_loadu_ps(in);
        __m128 max_mask = _mm_cmplt_ps(vmax, res);
        __m128 min_mask = _mm_cmplt_ps(res, vmin);
        res = _mm_blendv_ps(res, vmax, max_mask);
        res = _mm_blendv_ps(res, vmin, min_mask);
        _mm_storeu_ps(out, res);
        in += 4;
        out += 4;
    }

    number = quarter_points * 4;
    for (; number < num_points; number++) {
        *out++ = (*in > max) ? max : (*in < min) ? min : *in;
        in++;
    }
}
#endif /* LV_HAVE_SSE4_1 */

#ifdef LV_HAVE_GENERIC
static inline void volk_32f_s32f_x2_clamp_32f_generic(float* out,
                                                      const float* in,
                                                      const float min,
                                                      const float max,
                                                      unsigned int num_points)
{
    uint32_t number = 0;
    for (; number < num_points; number++) {
        *out++ = (*in > max) ? max : (*in < min) ? min : *in;
        in++;
    }
}
#endif /* LV_HAVE_GENERIC */

#endif /* INCLUDED_volk_32fc_s32f_x2_clamp_32f_u_H */
