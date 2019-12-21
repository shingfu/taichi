#include <taichi/ir.h>

TLANG_NAMESPACE_BEGIN

template <typename Tf, typename Ti>
Expr svd_bitwise_or(const Expr &a, const Expr &b) {
  return bit_cast<Tf>(bit_cast<Ti>(a) || bit_cast<Ti>(b));
}

template <typename Tf, typename Ti>
Expr svd_bitwise_xor(const Expr &a, const Expr &b) {
  return bit_cast<Tf>(bit_cast<Ti>(a) ^ bit_cast<Ti>(b));
}

template <typename Tf, typename Ti>
Expr svd_bitwise_and(const Expr &a, const Expr &b) {
  return bit_cast<Tf>(bit_cast<Ti>(a) && bit_cast<Ti>(b));
}

template <typename Tf, typename Ti>
std::tuple<Expr,
           Expr,
           Expr,
           Expr,
           Expr,
           Expr,
           Expr,
           Expr,
           Expr,
           Expr,
           Expr,
           Expr,
           Expr,
           Expr,
           Expr,
           Expr,
           Expr,
           Expr,
           Expr,
           Expr,
           Expr>
sifakis_svd_export(const Expr &a00,
                   const Expr &a01,
                   const Expr &a02,
                   const Expr &a10,
                   const Expr &a11,
                   const Expr &a12,
                   const Expr &a20,
                   const Expr &a21,
                   const Expr &a22,
                   int num_iters) {
  static_assert(sizeof(Tf) == sizeof(Ti), "");
  constexpr Tf Four_Gamma_Squared = 5.82842712474619f;
  constexpr Tf Sine_Pi_Over_Eight = 0.3826834323650897f;
  constexpr Tf Cosine_Pi_Over_Eight = 0.9238795325112867f;

  auto Sfour_gamma_squared = Var(Tf(0.0));
  auto Ssine_pi_over_eight = Var(Tf(0.0));
  auto Scosine_pi_over_eight = Var(Tf(0.0));
  auto Sone_half = Var(Tf(0.0));
  auto Sone = Var(Tf(0.0));
  auto Stiny_number = Var(Tf(0.0));
  auto Ssmall_number = Var(Tf(0.0));
  auto Sa11 = Var(Tf(0.0));
  auto Sa21 = Var(Tf(0.0));
  auto Sa31 = Var(Tf(0.0));
  auto Sa12 = Var(Tf(0.0));
  auto Sa22 = Var(Tf(0.0));
  auto Sa32 = Var(Tf(0.0));
  auto Sa13 = Var(Tf(0.0));
  auto Sa23 = Var(Tf(0.0));
  auto Sa33 = Var(Tf(0.0));
  auto Sv11 = Var(Tf(0.0));
  auto Sv21 = Var(Tf(0.0));
  auto Sv31 = Var(Tf(0.0));
  auto Sv12 = Var(Tf(0.0));
  auto Sv22 = Var(Tf(0.0));
  auto Sv32 = Var(Tf(0.0));
  auto Sv13 = Var(Tf(0.0));
  auto Sv23 = Var(Tf(0.0));
  auto Sv33 = Var(Tf(0.0));
  auto Su11 = Var(Tf(0.0));
  auto Su21 = Var(Tf(0.0));
  auto Su31 = Var(Tf(0.0));
  auto Su12 = Var(Tf(0.0));
  auto Su22 = Var(Tf(0.0));
  auto Su32 = Var(Tf(0.0));
  auto Su13 = Var(Tf(0.0));
  auto Su23 = Var(Tf(0.0));
  auto Su33 = Var(Tf(0.0));
  auto Sc = Var(Tf(0.0));
  auto Ss = Var(Tf(0.0));
  auto Sch = Var(Tf(0.0));
  auto Ssh = Var(Tf(0.0));
  auto Stmp1 = Var(Tf(0.0));
  auto Stmp2 = Var(Tf(0.0));
  auto Stmp3 = Var(Tf(0.0));
  auto Stmp4 = Var(Tf(0.0));
  auto Stmp5 = Var(Tf(0.0));
  auto Sqvs = Var(Tf(0.0));
  auto Sqvvx = Var(Tf(0.0));
  auto Sqvvy = Var(Tf(0.0));
  auto Sqvvz = Var(Tf(0.0));
  auto Ss11 = Var(Tf(0.0));
  auto Ss21 = Var(Tf(0.0));
  auto Ss31 = Var(Tf(0.0));
  auto Ss22 = Var(Tf(0.0));
  auto Ss32 = Var(Tf(0.0));
  auto Ss33 = Var(Tf(0.0));
  Sfour_gamma_squared = Expr(Four_Gamma_Squared);
  Ssine_pi_over_eight = Expr(Sine_Pi_Over_Eight);
  Scosine_pi_over_eight = Expr(Cosine_Pi_Over_Eight);
  Sone_half = Tf(0.5f);
  Sone = Tf(1.0f);
  Stiny_number = Tf(1.e-20f);
  Ssmall_number = Tf(1.e-12f);
  Sa11 = load_if_ptr(a00);
  Sa21 = load_if_ptr(a10);
  Sa31 = load_if_ptr(a20);
  Sa12 = load_if_ptr(a01);
  Sa22 = load_if_ptr(a11);
  Sa32 = load_if_ptr(a21);
  Sa13 = load_if_ptr(a02);
  Sa23 = load_if_ptr(a12);
  Sa33 = load_if_ptr(a22);
  Sqvs = Tf(1.0f);
  Sqvvx = Tf(0.0f);
  Sqvvy = Tf(0.0f);
  Sqvvz = Tf(0.0f);
  Ss11 = Sa11 * Sa11;
  Stmp1 = Sa21 * Sa21;
  Ss11 = Stmp1 + Ss11;
  Stmp1 = Sa31 * Sa31;
  Ss11 = Stmp1 + Ss11;
  Ss21 = Sa12 * Sa11;
  Stmp1 = Sa22 * Sa21;
  Ss21 = Stmp1 + Ss21;
  Stmp1 = Sa32 * Sa31;
  Ss21 = Stmp1 + Ss21;
  Ss31 = Sa13 * Sa11;
  Stmp1 = Sa23 * Sa21;
  Ss31 = Stmp1 + Ss31;
  Stmp1 = Sa33 * Sa31;
  Ss31 = Stmp1 + Ss31;
  Ss22 = Sa12 * Sa12;
  Stmp1 = Sa22 * Sa22;
  Ss22 = Stmp1 + Ss22;
  Stmp1 = Sa32 * Sa32;
  Ss22 = Stmp1 + Ss22;
  Ss32 = Sa13 * Sa12;
  Stmp1 = Sa23 * Sa22;
  Ss32 = Stmp1 + Ss32;
  Stmp1 = Sa33 * Sa32;
  Ss32 = Stmp1 + Ss32;
  Ss33 = Sa13 * Sa13;
  Stmp1 = Sa23 * Sa23;
  Ss33 = Stmp1 + Ss33;
  Stmp1 = Sa33 * Sa33;
  Ss33 = Stmp1 + Ss33;
  For(0, num_iters, [&](Expr sweep) {
    Ssh = Ss21 * Sone_half;
    Stmp5 = Ss11 - Ss22;
    Stmp2 = Ssh * Ssh;
    Stmp1 = bit_cast<Tf>(select(Stmp2 >= Stiny_number,
                                Expr(Ti(int32(0xffffffff))), Expr(Ti(0))));
    Ssh = svd_bitwise_and<Tf, Ti>(Stmp1, Ssh);
    Sch = svd_bitwise_and<Tf, Ti>(Stmp1, Stmp5);
    Stmp2 = svd_bitwise_and<Tf, Ti>(Expr(~bit_cast<Ti>(Stmp1)), Sone);
    Sch = svd_bitwise_or<Tf, Ti>(Sch, Stmp2);
    Stmp1 = Ssh * Ssh;
    Stmp2 = Sch * Sch;
    Stmp3 = Stmp1 + Stmp2;
    Stmp4 = rsqrt(Stmp3);
    Ssh = Stmp4 * Ssh;
    Sch = Stmp4 * Sch;
    Stmp1 = Sfour_gamma_squared * Stmp1;
    Stmp1 = bit_cast<Tf>(
        select(Stmp2 <= Stmp1, Expr(Ti(int32(0xffffffff))), Expr(Ti(0))));
    Stmp2 = svd_bitwise_and<Tf, Ti>(Ssine_pi_over_eight, Stmp1);
    Ssh = svd_bitwise_and<Tf, Ti>(Expr(~bit_cast<Ti>(Stmp1)), Ssh);
    Ssh = svd_bitwise_or<Tf, Ti>(Ssh, Stmp2);
    Stmp2 = svd_bitwise_and<Tf, Ti>(Scosine_pi_over_eight, Stmp1);
    Sch = svd_bitwise_and<Tf, Ti>(Expr(~bit_cast<Ti>(Stmp1)), Sch);
    Sch = svd_bitwise_or<Tf, Ti>(Sch, Stmp2);
    Stmp1 = Ssh * Ssh;
    Stmp2 = Sch * Sch;
    Sc = Stmp2 - Stmp1;
    Ss = Sch * Ssh;
    Ss = Ss + Ss;
    Stmp3 = Stmp1 + Stmp2;
    Ss33 = Ss33 * Stmp3;
    Ss31 = Ss31 * Stmp3;
    Ss32 = Ss32 * Stmp3;
    Ss33 = Ss33 * Stmp3;
    Stmp1 = Ss * Ss31;
    Stmp2 = Ss * Ss32;
    Ss31 = Sc * Ss31;
    Ss32 = Sc * Ss32;
    Ss31 = Stmp2 + Ss31;
    Ss32 = Ss32 - Stmp1;
    Stmp2 = Ss * Ss;
    Stmp1 = Ss22 * Stmp2;
    Stmp3 = Ss11 * Stmp2;
    Stmp4 = Sc * Sc;
    Ss11 = Ss11 * Stmp4;
    Ss22 = Ss22 * Stmp4;
    Ss11 = Ss11 + Stmp1;
    Ss22 = Ss22 + Stmp3;
    Stmp4 = Stmp4 - Stmp2;
    Stmp2 = Ss21 + Ss21;
    Ss21 = Ss21 * Stmp4;
    Stmp4 = Sc * Ss;
    Stmp2 = Stmp2 * Stmp4;
    Stmp5 = Stmp5 * Stmp4;
    Ss11 = Ss11 + Stmp2;
    Ss21 = Ss21 - Stmp5;
    Ss22 = Ss22 - Stmp2;
    Stmp1 = Ssh * Sqvvx;
    Stmp2 = Ssh * Sqvvy;
    Stmp3 = Ssh * Sqvvz;
    Ssh = Ssh * Sqvs;
    Sqvs = Sch * Sqvs;
    Sqvvx = Sch * Sqvvx;
    Sqvvy = Sch * Sqvvy;
    Sqvvz = Sch * Sqvvz;
    Sqvvz = Sqvvz + Ssh;
    Sqvs = Sqvs - Stmp3;
    Sqvvx = Sqvvx + Stmp2;
    Sqvvy = Sqvvy - Stmp1;
    Ssh = Ss32 * Sone_half;
    Stmp5 = Ss22 - Ss33;
    Stmp2 = Ssh * Ssh;
    Stmp1 = bit_cast<Tf>(select(Stmp2 >= Stiny_number,
                                Expr(Ti(int32(0xffffffff))), Expr(Ti(0))));
    Ssh = svd_bitwise_and<Tf, Ti>(Stmp1, Ssh);
    Sch = svd_bitwise_and<Tf, Ti>(Stmp1, Stmp5);
    Stmp2 = svd_bitwise_and<Tf, Ti>(Expr(~bit_cast<Ti>(Stmp1)), Sone);
    Sch = svd_bitwise_or<Tf, Ti>(Sch, Stmp2);
    Stmp1 = Ssh * Ssh;
    Stmp2 = Sch * Sch;
    Stmp3 = Stmp1 + Stmp2;
    Stmp4 = rsqrt(Stmp3);
    Ssh = Stmp4 * Ssh;
    Sch = Stmp4 * Sch;
    Stmp1 = Sfour_gamma_squared * Stmp1;
    Stmp1 = bit_cast<Tf>(
        select(Stmp2 <= Stmp1, Expr(Ti(int32(0xffffffff))), Expr(Ti(0))));
    Stmp2 = svd_bitwise_and<Tf, Ti>(Ssine_pi_over_eight, Stmp1);
    Ssh = svd_bitwise_and<Tf, Ti>(Expr(~bit_cast<Ti>(Stmp1)), Ssh);
    Ssh = svd_bitwise_or<Tf, Ti>(Ssh, Stmp2);
    Stmp2 = svd_bitwise_and<Tf, Ti>(Scosine_pi_over_eight, Stmp1);
    Sch = svd_bitwise_and<Tf, Ti>(Expr(~bit_cast<Ti>(Stmp1)), Sch);
    Sch = svd_bitwise_or<Tf, Ti>(Sch, Stmp2);
    Stmp1 = Ssh * Ssh;
    Stmp2 = Sch * Sch;
    Sc = Stmp2 - Stmp1;
    Ss = Sch * Ssh;
    Ss = Ss + Ss;
    Stmp3 = Stmp1 + Stmp2;
    Ss11 = Ss11 * Stmp3;
    Ss21 = Ss21 * Stmp3;
    Ss31 = Ss31 * Stmp3;
    Ss11 = Ss11 * Stmp3;
    Stmp1 = Ss * Ss21;
    Stmp2 = Ss * Ss31;
    Ss21 = Sc * Ss21;
    Ss31 = Sc * Ss31;
    Ss21 = Stmp2 + Ss21;
    Ss31 = Ss31 - Stmp1;
    Stmp2 = Ss * Ss;
    Stmp1 = Ss33 * Stmp2;
    Stmp3 = Ss22 * Stmp2;
    Stmp4 = Sc * Sc;
    Ss22 = Ss22 * Stmp4;
    Ss33 = Ss33 * Stmp4;
    Ss22 = Ss22 + Stmp1;
    Ss33 = Ss33 + Stmp3;
    Stmp4 = Stmp4 - Stmp2;
    Stmp2 = Ss32 + Ss32;
    Ss32 = Ss32 * Stmp4;
    Stmp4 = Sc * Ss;
    Stmp2 = Stmp2 * Stmp4;
    Stmp5 = Stmp5 * Stmp4;
    Ss22 = Ss22 + Stmp2;
    Ss32 = Ss32 - Stmp5;
    Ss33 = Ss33 - Stmp2;
    Stmp1 = Ssh * Sqvvx;
    Stmp2 = Ssh * Sqvvy;
    Stmp3 = Ssh * Sqvvz;
    Ssh = Ssh * Sqvs;
    Sqvs = Sch * Sqvs;
    Sqvvx = Sch * Sqvvx;
    Sqvvy = Sch * Sqvvy;
    Sqvvz = Sch * Sqvvz;
    Sqvvx = Sqvvx + Ssh;
    Sqvs = Sqvs - Stmp1;
    Sqvvy = Sqvvy + Stmp3;
    Sqvvz = Sqvvz - Stmp2;
    Ssh = Ss31 * Sone_half;
    Stmp5 = Ss33 - Ss11;
    Stmp2 = Ssh * Ssh;
    Stmp1 = bit_cast<Tf>(select(Stmp2 >= Stiny_number,
                                Expr(Ti(int32(0xffffffff))), Expr(Ti(0))));
    Ssh = svd_bitwise_and<Tf, Ti>(Stmp1, Ssh);
    Sch = svd_bitwise_and<Tf, Ti>(Stmp1, Stmp5);
    Stmp2 = svd_bitwise_and<Tf, Ti>(Expr(~bit_cast<Ti>(Stmp1)), Sone);
    Sch = svd_bitwise_or<Tf, Ti>(Sch, Stmp2);
    Stmp1 = Ssh * Ssh;
    Stmp2 = Sch * Sch;
    Stmp3 = Stmp1 + Stmp2;
    Stmp4 = rsqrt(Stmp3);
    Ssh = Stmp4 * Ssh;
    Sch = Stmp4 * Sch;
    Stmp1 = Sfour_gamma_squared * Stmp1;
    Stmp1 = bit_cast<Tf>(
        select(Stmp2 <= Stmp1, Expr(Ti(int32(0xffffffff))), Expr(Ti(0))));
    Stmp2 = svd_bitwise_and<Tf, Ti>(Ssine_pi_over_eight, Stmp1);
    Ssh = svd_bitwise_and<Tf, Ti>(Expr(~bit_cast<Ti>(Stmp1)), Ssh);
    Ssh = svd_bitwise_or<Tf, Ti>(Ssh, Stmp2);
    Stmp2 = svd_bitwise_and<Tf, Ti>(Scosine_pi_over_eight, Stmp1);
    Sch = svd_bitwise_and<Tf, Ti>(Expr(~bit_cast<Ti>(Stmp1)), Sch);
    Sch = svd_bitwise_or<Tf, Ti>(Sch, Stmp2);
    Stmp1 = Ssh * Ssh;
    Stmp2 = Sch * Sch;
    Sc = Stmp2 - Stmp1;
    Ss = Sch * Ssh;
    Ss = Ss + Ss;
    Stmp3 = Stmp1 + Stmp2;
    Ss22 = Ss22 * Stmp3;
    Ss32 = Ss32 * Stmp3;
    Ss21 = Ss21 * Stmp3;
    Ss22 = Ss22 * Stmp3;
    Stmp1 = Ss * Ss32;
    Stmp2 = Ss * Ss21;
    Ss32 = Sc * Ss32;
    Ss21 = Sc * Ss21;
    Ss32 = Stmp2 + Ss32;
    Ss21 = Ss21 - Stmp1;
    Stmp2 = Ss * Ss;
    Stmp1 = Ss11 * Stmp2;
    Stmp3 = Ss33 * Stmp2;
    Stmp4 = Sc * Sc;
    Ss33 = Ss33 * Stmp4;
    Ss11 = Ss11 * Stmp4;
    Ss33 = Ss33 + Stmp1;
    Ss11 = Ss11 + Stmp3;
    Stmp4 = Stmp4 - Stmp2;
    Stmp2 = Ss31 + Ss31;
    Ss31 = Ss31 * Stmp4;
    Stmp4 = Sc * Ss;
    Stmp2 = Stmp2 * Stmp4;
    Stmp5 = Stmp5 * Stmp4;
    Ss33 = Ss33 + Stmp2;
    Ss31 = Ss31 - Stmp5;
    Ss11 = Ss11 - Stmp2;
    Stmp1 = Ssh * Sqvvx;
    Stmp2 = Ssh * Sqvvy;
    Stmp3 = Ssh * Sqvvz;
    Ssh = Ssh * Sqvs;
    Sqvs = Sch * Sqvs;
    Sqvvx = Sch * Sqvvx;
    Sqvvy = Sch * Sqvvy;
    Sqvvz = Sch * Sqvvz;
    Sqvvy = Sqvvy + Ssh;
    Sqvs = Sqvs - Stmp2;
    Sqvvz = Sqvvz + Stmp1;
    Sqvvx = Sqvvx - Stmp3;
  });
  Stmp2 = Sqvs * Sqvs;
  Stmp1 = Sqvvx * Sqvvx;
  Stmp2 = Stmp1 + Stmp2;
  Stmp1 = Sqvvy * Sqvvy;
  Stmp2 = Stmp1 + Stmp2;
  Stmp1 = Sqvvz * Sqvvz;
  Stmp2 = Stmp1 + Stmp2;
  Stmp1 = rsqrt(Stmp2);
  Stmp4 = Stmp1 * Sone_half;
  Stmp3 = Stmp1 * Stmp4;
  Stmp3 = Stmp1 * Stmp3;
  Stmp3 = Stmp2 * Stmp3;
  Stmp1 = Stmp1 + Stmp4;
  Stmp1 = Stmp1 - Stmp3;
  Sqvs = Sqvs * Stmp1;
  Sqvvx = Sqvvx * Stmp1;
  Sqvvy = Sqvvy * Stmp1;
  Sqvvz = Sqvvz * Stmp1;
  Stmp1 = Sqvvx * Sqvvx;
  Stmp2 = Sqvvy * Sqvvy;
  Stmp3 = Sqvvz * Sqvvz;
  Sv11 = Sqvs * Sqvs;
  Sv22 = Sv11 - Stmp1;
  Sv33 = Sv22 - Stmp2;
  Sv33 = Sv33 + Stmp3;
  Sv22 = Sv22 + Stmp2;
  Sv22 = Sv22 - Stmp3;
  Sv11 = Sv11 + Stmp1;
  Sv11 = Sv11 - Stmp2;
  Sv11 = Sv11 - Stmp3;
  Stmp1 = Sqvvx + Sqvvx;
  Stmp2 = Sqvvy + Sqvvy;
  Stmp3 = Sqvvz + Sqvvz;
  Sv32 = Sqvs * Stmp1;
  Sv13 = Sqvs * Stmp2;
  Sv21 = Sqvs * Stmp3;
  Stmp1 = Sqvvy * Stmp1;
  Stmp2 = Sqvvz * Stmp2;
  Stmp3 = Sqvvx * Stmp3;
  Sv12 = Stmp1 - Sv21;
  Sv23 = Stmp2 - Sv32;
  Sv31 = Stmp3 - Sv13;
  Sv21 = Stmp1 + Sv21;
  Sv32 = Stmp2 + Sv32;
  Sv13 = Stmp3 + Sv13;
  Stmp2 = Sa12;
  Stmp3 = Sa13;
  Sa12 = Sv12 * Sa11;
  Sa13 = Sv13 * Sa11;
  Sa11 = Sv11 * Sa11;
  Stmp1 = Sv21 * Stmp2;
  Sa11 = Sa11 + Stmp1;
  Stmp1 = Sv31 * Stmp3;
  Sa11 = Sa11 + Stmp1;
  Stmp1 = Sv22 * Stmp2;
  Sa12 = Sa12 + Stmp1;
  Stmp1 = Sv32 * Stmp3;
  Sa12 = Sa12 + Stmp1;
  Stmp1 = Sv23 * Stmp2;
  Sa13 = Sa13 + Stmp1;
  Stmp1 = Sv33 * Stmp3;
  Sa13 = Sa13 + Stmp1;
  Stmp2 = Sa22;
  Stmp3 = Sa23;
  Sa22 = Sv12 * Sa21;
  Sa23 = Sv13 * Sa21;
  Sa21 = Sv11 * Sa21;
  Stmp1 = Sv21 * Stmp2;
  Sa21 = Sa21 + Stmp1;
  Stmp1 = Sv31 * Stmp3;
  Sa21 = Sa21 + Stmp1;
  Stmp1 = Sv22 * Stmp2;
  Sa22 = Sa22 + Stmp1;
  Stmp1 = Sv32 * Stmp3;
  Sa22 = Sa22 + Stmp1;
  Stmp1 = Sv23 * Stmp2;
  Sa23 = Sa23 + Stmp1;
  Stmp1 = Sv33 * Stmp3;
  Sa23 = Sa23 + Stmp1;
  Stmp2 = Sa32;
  Stmp3 = Sa33;
  Sa32 = Sv12 * Sa31;
  Sa33 = Sv13 * Sa31;
  Sa31 = Sv11 * Sa31;
  Stmp1 = Sv21 * Stmp2;
  Sa31 = Sa31 + Stmp1;
  Stmp1 = Sv31 * Stmp3;
  Sa31 = Sa31 + Stmp1;
  Stmp1 = Sv22 * Stmp2;
  Sa32 = Sa32 + Stmp1;
  Stmp1 = Sv32 * Stmp3;
  Sa32 = Sa32 + Stmp1;
  Stmp1 = Sv23 * Stmp2;
  Sa33 = Sa33 + Stmp1;
  Stmp1 = Sv33 * Stmp3;
  Sa33 = Sa33 + Stmp1;
  Stmp1 = Sa11 * Sa11;
  Stmp4 = Sa21 * Sa21;
  Stmp1 = Stmp1 + Stmp4;
  Stmp4 = Sa31 * Sa31;
  Stmp1 = Stmp1 + Stmp4;
  Stmp2 = Sa12 * Sa12;
  Stmp4 = Sa22 * Sa22;
  Stmp2 = Stmp2 + Stmp4;
  Stmp4 = Sa32 * Sa32;
  Stmp2 = Stmp2 + Stmp4;
  Stmp3 = Sa13 * Sa13;
  Stmp4 = Sa23 * Sa23;
  Stmp3 = Stmp3 + Stmp4;
  Stmp4 = Sa33 * Sa33;
  Stmp3 = Stmp3 + Stmp4;
  Stmp4 = bit_cast<Tf>(
      select(Stmp1 < Stmp2, Expr(Ti(int32(0xffffffff))), Expr(Ti(0))));
  Stmp5 = svd_bitwise_xor<Tf, Ti>(Sa11, Sa12);
  Stmp5 = svd_bitwise_and<Tf, Ti>(Stmp5, Stmp4);
  Sa11 = svd_bitwise_xor<Tf, Ti>(Sa11, Stmp5);
  Sa12 = svd_bitwise_xor<Tf, Ti>(Sa12, Stmp5);
  Stmp5 = svd_bitwise_xor<Tf, Ti>(Sa21, Sa22);
  Stmp5 = svd_bitwise_and<Tf, Ti>(Stmp5, Stmp4);
  Sa21 = svd_bitwise_xor<Tf, Ti>(Sa21, Stmp5);
  Sa22 = svd_bitwise_xor<Tf, Ti>(Sa22, Stmp5);
  Stmp5 = svd_bitwise_xor<Tf, Ti>(Sa31, Sa32);
  Stmp5 = svd_bitwise_and<Tf, Ti>(Stmp5, Stmp4);
  Sa31 = svd_bitwise_xor<Tf, Ti>(Sa31, Stmp5);
  Sa32 = svd_bitwise_xor<Tf, Ti>(Sa32, Stmp5);
  Stmp5 = svd_bitwise_xor<Tf, Ti>(Sv11, Sv12);
  Stmp5 = svd_bitwise_and<Tf, Ti>(Stmp5, Stmp4);
  Sv11 = svd_bitwise_xor<Tf, Ti>(Sv11, Stmp5);
  Sv12 = svd_bitwise_xor<Tf, Ti>(Sv12, Stmp5);
  Stmp5 = svd_bitwise_xor<Tf, Ti>(Sv21, Sv22);
  Stmp5 = svd_bitwise_and<Tf, Ti>(Stmp5, Stmp4);
  Sv21 = svd_bitwise_xor<Tf, Ti>(Sv21, Stmp5);
  Sv22 = svd_bitwise_xor<Tf, Ti>(Sv22, Stmp5);
  Stmp5 = svd_bitwise_xor<Tf, Ti>(Sv31, Sv32);
  Stmp5 = svd_bitwise_and<Tf, Ti>(Stmp5, Stmp4);
  Sv31 = svd_bitwise_xor<Tf, Ti>(Sv31, Stmp5);
  Sv32 = svd_bitwise_xor<Tf, Ti>(Sv32, Stmp5);
  Stmp5 = svd_bitwise_xor<Tf, Ti>(Stmp1, Stmp2);
  Stmp5 = svd_bitwise_and<Tf, Ti>(Stmp5, Stmp4);
  Stmp1 = svd_bitwise_xor<Tf, Ti>(Stmp1, Stmp5);
  Stmp2 = svd_bitwise_xor<Tf, Ti>(Stmp2, Stmp5);
  Stmp5 = Tf(-2.0f);
  Stmp5 = svd_bitwise_and<Tf, Ti>(Stmp5, Stmp4);
  Stmp4 = Tf(1.0f);
  Stmp4 = Stmp4 + Stmp5;
  Sa12 = Sa12 * Stmp4;
  Sa22 = Sa22 * Stmp4;
  Sa32 = Sa32 * Stmp4;
  Sv12 = Sv12 * Stmp4;
  Sv22 = Sv22 * Stmp4;
  Sv32 = Sv32 * Stmp4;
  Stmp4 = bit_cast<Tf>(
      select(Stmp1 < Stmp3, Expr(Ti(int32(0xffffffff))), Expr(Ti(0))));
  Stmp5 = svd_bitwise_xor<Tf, Ti>(Sa11, Sa13);
  Stmp5 = svd_bitwise_and<Tf, Ti>(Stmp5, Stmp4);
  Sa11 = svd_bitwise_xor<Tf, Ti>(Sa11, Stmp5);
  Sa13 = svd_bitwise_xor<Tf, Ti>(Sa13, Stmp5);
  Stmp5 = svd_bitwise_xor<Tf, Ti>(Sa21, Sa23);
  Stmp5 = svd_bitwise_and<Tf, Ti>(Stmp5, Stmp4);
  Sa21 = svd_bitwise_xor<Tf, Ti>(Sa21, Stmp5);
  Sa23 = svd_bitwise_xor<Tf, Ti>(Sa23, Stmp5);
  Stmp5 = svd_bitwise_xor<Tf, Ti>(Sa31, Sa33);
  Stmp5 = svd_bitwise_and<Tf, Ti>(Stmp5, Stmp4);
  Sa31 = svd_bitwise_xor<Tf, Ti>(Sa31, Stmp5);
  Sa33 = svd_bitwise_xor<Tf, Ti>(Sa33, Stmp5);
  Stmp5 = svd_bitwise_xor<Tf, Ti>(Sv11, Sv13);
  Stmp5 = svd_bitwise_and<Tf, Ti>(Stmp5, Stmp4);
  Sv11 = svd_bitwise_xor<Tf, Ti>(Sv11, Stmp5);
  Sv13 = svd_bitwise_xor<Tf, Ti>(Sv13, Stmp5);
  Stmp5 = svd_bitwise_xor<Tf, Ti>(Sv21, Sv23);
  Stmp5 = svd_bitwise_and<Tf, Ti>(Stmp5, Stmp4);
  Sv21 = svd_bitwise_xor<Tf, Ti>(Sv21, Stmp5);
  Sv23 = svd_bitwise_xor<Tf, Ti>(Sv23, Stmp5);
  Stmp5 = svd_bitwise_xor<Tf, Ti>(Sv31, Sv33);
  Stmp5 = svd_bitwise_and<Tf, Ti>(Stmp5, Stmp4);
  Sv31 = svd_bitwise_xor<Tf, Ti>(Sv31, Stmp5);
  Sv33 = svd_bitwise_xor<Tf, Ti>(Sv33, Stmp5);
  Stmp5 = svd_bitwise_xor<Tf, Ti>(Stmp1, Stmp3);
  Stmp5 = svd_bitwise_and<Tf, Ti>(Stmp5, Stmp4);
  Stmp1 = svd_bitwise_xor<Tf, Ti>(Stmp1, Stmp5);
  Stmp3 = svd_bitwise_xor<Tf, Ti>(Stmp3, Stmp5);
  Stmp5 = Tf(-2.0f);
  Stmp5 = svd_bitwise_and<Tf, Ti>(Stmp5, Stmp4);
  Stmp4 = Tf(1.0f);
  Stmp4 = Stmp4 + Stmp5;
  Sa11 = Sa11 * Stmp4;
  Sa21 = Sa21 * Stmp4;
  Sa31 = Sa31 * Stmp4;
  Sv11 = Sv11 * Stmp4;
  Sv21 = Sv21 * Stmp4;
  Sv31 = Sv31 * Stmp4;
  Stmp4 = bit_cast<Tf>(
      select(Stmp2 < Stmp3, Expr(Ti(int32(0xffffffff))), Expr(Ti(0))));
  Stmp5 = svd_bitwise_xor<Tf, Ti>(Sa12, Sa13);
  Stmp5 = svd_bitwise_and<Tf, Ti>(Stmp5, Stmp4);
  Sa12 = svd_bitwise_xor<Tf, Ti>(Sa12, Stmp5);
  Sa13 = svd_bitwise_xor<Tf, Ti>(Sa13, Stmp5);
  Stmp5 = svd_bitwise_xor<Tf, Ti>(Sa22, Sa23);
  Stmp5 = svd_bitwise_and<Tf, Ti>(Stmp5, Stmp4);
  Sa22 = svd_bitwise_xor<Tf, Ti>(Sa22, Stmp5);
  Sa23 = svd_bitwise_xor<Tf, Ti>(Sa23, Stmp5);
  Stmp5 = svd_bitwise_xor<Tf, Ti>(Sa32, Sa33);
  Stmp5 = svd_bitwise_and<Tf, Ti>(Stmp5, Stmp4);
  Sa32 = svd_bitwise_xor<Tf, Ti>(Sa32, Stmp5);
  Sa33 = svd_bitwise_xor<Tf, Ti>(Sa33, Stmp5);
  Stmp5 = svd_bitwise_xor<Tf, Ti>(Sv12, Sv13);
  Stmp5 = svd_bitwise_and<Tf, Ti>(Stmp5, Stmp4);
  Sv12 = svd_bitwise_xor<Tf, Ti>(Sv12, Stmp5);
  Sv13 = svd_bitwise_xor<Tf, Ti>(Sv13, Stmp5);
  Stmp5 = svd_bitwise_xor<Tf, Ti>(Sv22, Sv23);
  Stmp5 = svd_bitwise_and<Tf, Ti>(Stmp5, Stmp4);
  Sv22 = svd_bitwise_xor<Tf, Ti>(Sv22, Stmp5);
  Sv23 = svd_bitwise_xor<Tf, Ti>(Sv23, Stmp5);
  Stmp5 = svd_bitwise_xor<Tf, Ti>(Sv32, Sv33);
  Stmp5 = svd_bitwise_and<Tf, Ti>(Stmp5, Stmp4);
  Sv32 = svd_bitwise_xor<Tf, Ti>(Sv32, Stmp5);
  Sv33 = svd_bitwise_xor<Tf, Ti>(Sv33, Stmp5);
  Stmp5 = svd_bitwise_xor<Tf, Ti>(Stmp2, Stmp3);
  Stmp5 = svd_bitwise_and<Tf, Ti>(Stmp5, Stmp4);
  Stmp2 = svd_bitwise_xor<Tf, Ti>(Stmp2, Stmp5);
  Stmp3 = svd_bitwise_xor<Tf, Ti>(Stmp3, Stmp5);
  Stmp5 = Tf(-2.0f);
  Stmp5 = svd_bitwise_and<Tf, Ti>(Stmp5, Stmp4);
  Stmp4 = Tf(1.0f);
  Stmp4 = Stmp4 + Stmp5;
  Sa13 = Sa13 * Stmp4;
  Sa23 = Sa23 * Stmp4;
  Sa33 = Sa33 * Stmp4;
  Sv13 = Sv13 * Stmp4;
  Sv23 = Sv23 * Stmp4;
  Sv33 = Sv33 * Stmp4;
  Su11 = Tf(1.0f);
  Su21 = Tf(0.0f);
  Su31 = Tf(0.0f);
  Su12 = Tf(0.0f);
  Su22 = Tf(1.0f);
  Su32 = Tf(0.0f);
  Su13 = Tf(0.0f);
  Su23 = Tf(0.0f);
  Su33 = Tf(1.0f);
  Ssh = Sa21 * Sa21;
  Ssh = bit_cast<Tf>(
      select(Ssh >= Ssmall_number, Expr(Ti(int32(0xffffffff))), Expr(Ti(0))));
  Ssh = svd_bitwise_and<Tf, Ti>(Ssh, Sa21);
  Stmp5 = Tf(0.0f);
  Sch = Stmp5 - Sa11;
  Sch = max(Sch, Sa11);
  Sch = max(Sch, Ssmall_number);
  Stmp5 = bit_cast<Tf>(
      select(Sa11 >= Stmp5, Expr(Ti(int32(0xffffffff))), Expr(Ti(0))));
  Stmp1 = Sch * Sch;
  Stmp2 = Ssh * Ssh;
  Stmp2 = Stmp1 + Stmp2;
  Stmp1 = rsqrt(Stmp2);
  Stmp4 = Stmp1 * Sone_half;
  Stmp3 = Stmp1 * Stmp4;
  Stmp3 = Stmp1 * Stmp3;
  Stmp3 = Stmp2 * Stmp3;
  Stmp1 = Stmp1 + Stmp4;
  Stmp1 = Stmp1 - Stmp3;
  Stmp1 = Stmp1 * Stmp2;
  Sch = Sch + Stmp1;
  Stmp1 = svd_bitwise_and<Tf, Ti>(Expr(~bit_cast<Ti>(Stmp5)), Ssh);
  Stmp2 = svd_bitwise_and<Tf, Ti>(Expr(~bit_cast<Ti>(Stmp5)), Sch);
  Sch = svd_bitwise_and<Tf, Ti>(Stmp5, Sch);
  Ssh = svd_bitwise_and<Tf, Ti>(Stmp5, Ssh);
  Sch = svd_bitwise_or<Tf, Ti>(Sch, Stmp1);
  Ssh = svd_bitwise_or<Tf, Ti>(Ssh, Stmp2);
  Stmp1 = Sch * Sch;
  Stmp2 = Ssh * Ssh;
  Stmp2 = Stmp1 + Stmp2;
  Stmp1 = rsqrt(Stmp2);
  Stmp4 = Stmp1 * Sone_half;
  Stmp3 = Stmp1 * Stmp4;
  Stmp3 = Stmp1 * Stmp3;
  Stmp3 = Stmp2 * Stmp3;
  Stmp1 = Stmp1 + Stmp4;
  Stmp1 = Stmp1 - Stmp3;
  Sch = Sch * Stmp1;
  Ssh = Ssh * Stmp1;
  Sc = Sch * Sch;
  Ss = Ssh * Ssh;
  Sc = Sc - Ss;
  Ss = Ssh * Sch;
  Ss = Ss + Ss;
  Stmp1 = Ss * Sa11;
  Stmp2 = Ss * Sa21;
  Sa11 = Sc * Sa11;
  Sa21 = Sc * Sa21;
  Sa11 = Sa11 + Stmp2;
  Sa21 = Sa21 - Stmp1;
  Stmp1 = Ss * Sa12;
  Stmp2 = Ss * Sa22;
  Sa12 = Sc * Sa12;
  Sa22 = Sc * Sa22;
  Sa12 = Sa12 + Stmp2;
  Sa22 = Sa22 - Stmp1;
  Stmp1 = Ss * Sa13;
  Stmp2 = Ss * Sa23;
  Sa13 = Sc * Sa13;
  Sa23 = Sc * Sa23;
  Sa13 = Sa13 + Stmp2;
  Sa23 = Sa23 - Stmp1;
  Stmp1 = Ss * Su11;
  Stmp2 = Ss * Su12;
  Su11 = Sc * Su11;
  Su12 = Sc * Su12;
  Su11 = Su11 + Stmp2;
  Su12 = Su12 - Stmp1;
  Stmp1 = Ss * Su21;
  Stmp2 = Ss * Su22;
  Su21 = Sc * Su21;
  Su22 = Sc * Su22;
  Su21 = Su21 + Stmp2;
  Su22 = Su22 - Stmp1;
  Stmp1 = Ss * Su31;
  Stmp2 = Ss * Su32;
  Su31 = Sc * Su31;
  Su32 = Sc * Su32;
  Su31 = Su31 + Stmp2;
  Su32 = Su32 - Stmp1;
  Ssh = Sa31 * Sa31;
  Ssh = bit_cast<Tf>(
      select(Ssh >= Ssmall_number, Expr(Ti(int32(0xffffffff))), Expr(Ti(0))));
  Ssh = svd_bitwise_and<Tf, Ti>(Ssh, Sa31);
  Stmp5 = Tf(0.0f);
  Sch = Stmp5 - Sa11;
  Sch = max(Sch, Sa11);
  Sch = max(Sch, Ssmall_number);
  Stmp5 = bit_cast<Tf>(
      select(Sa11 >= Stmp5, Expr(Ti(int32(0xffffffff))), Expr(Ti(0))));
  Stmp1 = Sch * Sch;
  Stmp2 = Ssh * Ssh;
  Stmp2 = Stmp1 + Stmp2;
  Stmp1 = rsqrt(Stmp2);
  Stmp4 = Stmp1 * Sone_half;
  Stmp3 = Stmp1 * Stmp4;
  Stmp3 = Stmp1 * Stmp3;
  Stmp3 = Stmp2 * Stmp3;
  Stmp1 = Stmp1 + Stmp4;
  Stmp1 = Stmp1 - Stmp3;
  Stmp1 = Stmp1 * Stmp2;
  Sch = Sch + Stmp1;
  Stmp1 = svd_bitwise_and<Tf, Ti>(Expr(~bit_cast<Ti>(Stmp5)), Ssh);
  Stmp2 = svd_bitwise_and<Tf, Ti>(Expr(~bit_cast<Ti>(Stmp5)), Sch);
  Sch = svd_bitwise_and<Tf, Ti>(Stmp5, Sch);
  Ssh = svd_bitwise_and<Tf, Ti>(Stmp5, Ssh);
  Sch = svd_bitwise_or<Tf, Ti>(Sch, Stmp1);
  Ssh = svd_bitwise_or<Tf, Ti>(Ssh, Stmp2);
  Stmp1 = Sch * Sch;
  Stmp2 = Ssh * Ssh;
  Stmp2 = Stmp1 + Stmp2;
  Stmp1 = rsqrt(Stmp2);
  Stmp4 = Stmp1 * Sone_half;
  Stmp3 = Stmp1 * Stmp4;
  Stmp3 = Stmp1 * Stmp3;
  Stmp3 = Stmp2 * Stmp3;
  Stmp1 = Stmp1 + Stmp4;
  Stmp1 = Stmp1 - Stmp3;
  Sch = Sch * Stmp1;
  Ssh = Ssh * Stmp1;
  Sc = Sch * Sch;
  Ss = Ssh * Ssh;
  Sc = Sc - Ss;
  Ss = Ssh * Sch;
  Ss = Ss + Ss;
  Stmp1 = Ss * Sa11;
  Stmp2 = Ss * Sa31;
  Sa11 = Sc * Sa11;
  Sa31 = Sc * Sa31;
  Sa11 = Sa11 + Stmp2;
  Sa31 = Sa31 - Stmp1;
  Stmp1 = Ss * Sa12;
  Stmp2 = Ss * Sa32;
  Sa12 = Sc * Sa12;
  Sa32 = Sc * Sa32;
  Sa12 = Sa12 + Stmp2;
  Sa32 = Sa32 - Stmp1;
  Stmp1 = Ss * Sa13;
  Stmp2 = Ss * Sa33;
  Sa13 = Sc * Sa13;
  Sa33 = Sc * Sa33;
  Sa13 = Sa13 + Stmp2;
  Sa33 = Sa33 - Stmp1;
  Stmp1 = Ss * Su11;
  Stmp2 = Ss * Su13;
  Su11 = Sc * Su11;
  Su13 = Sc * Su13;
  Su11 = Su11 + Stmp2;
  Su13 = Su13 - Stmp1;
  Stmp1 = Ss * Su21;
  Stmp2 = Ss * Su23;
  Su21 = Sc * Su21;
  Su23 = Sc * Su23;
  Su21 = Su21 + Stmp2;
  Su23 = Su23 - Stmp1;
  Stmp1 = Ss * Su31;
  Stmp2 = Ss * Su33;
  Su31 = Sc * Su31;
  Su33 = Sc * Su33;
  Su31 = Su31 + Stmp2;
  Su33 = Su33 - Stmp1;
  Ssh = Sa32 * Sa32;
  Ssh = bit_cast<Tf>(
      select(Ssh >= Ssmall_number, Expr(Ti(int32(0xffffffff))), Expr(Ti(0))));
  Ssh = svd_bitwise_and<Tf, Ti>(Ssh, Sa32);
  Stmp5 = Tf(0.0f);
  Sch = Stmp5 - Sa22;
  Sch = max(Sch, Sa22);
  Sch = max(Sch, Ssmall_number);
  Stmp5 = bit_cast<Tf>(
      select(Sa22 >= Stmp5, Expr(Ti(int32(0xffffffff))), Expr(Ti(0))));
  Stmp1 = Sch * Sch;
  Stmp2 = Ssh * Ssh;
  Stmp2 = Stmp1 + Stmp2;
  Stmp1 = rsqrt(Stmp2);
  Stmp4 = Stmp1 * Sone_half;
  Stmp3 = Stmp1 * Stmp4;
  Stmp3 = Stmp1 * Stmp3;
  Stmp3 = Stmp2 * Stmp3;
  Stmp1 = Stmp1 + Stmp4;
  Stmp1 = Stmp1 - Stmp3;
  Stmp1 = Stmp1 * Stmp2;
  Sch = Sch + Stmp1;
  Stmp1 = svd_bitwise_and<Tf, Ti>(Expr(~bit_cast<Ti>(Stmp5)), Ssh);
  Stmp2 = svd_bitwise_and<Tf, Ti>(Expr(~bit_cast<Ti>(Stmp5)), Sch);
  Sch = svd_bitwise_and<Tf, Ti>(Stmp5, Sch);
  Ssh = svd_bitwise_and<Tf, Ti>(Stmp5, Ssh);
  Sch = svd_bitwise_or<Tf, Ti>(Sch, Stmp1);
  Ssh = svd_bitwise_or<Tf, Ti>(Ssh, Stmp2);
  Stmp1 = Sch * Sch;
  Stmp2 = Ssh * Ssh;
  Stmp2 = Stmp1 + Stmp2;
  Stmp1 = rsqrt(Stmp2);
  Stmp4 = Stmp1 * Sone_half;
  Stmp3 = Stmp1 * Stmp4;
  Stmp3 = Stmp1 * Stmp3;
  Stmp3 = Stmp2 * Stmp3;
  Stmp1 = Stmp1 + Stmp4;
  Stmp1 = Stmp1 - Stmp3;
  Sch = Sch * Stmp1;
  Ssh = Ssh * Stmp1;
  Sc = Sch * Sch;
  Ss = Ssh * Ssh;
  Sc = Sc - Ss;
  Ss = Ssh * Sch;
  Ss = Ss + Ss;
  Stmp1 = Ss * Sa21;
  Stmp2 = Ss * Sa31;
  Sa21 = Sc * Sa21;
  Sa31 = Sc * Sa31;
  Sa21 = Sa21 + Stmp2;
  Sa31 = Sa31 - Stmp1;
  Stmp1 = Ss * Sa22;
  Stmp2 = Ss * Sa32;
  Sa22 = Sc * Sa22;
  Sa32 = Sc * Sa32;
  Sa22 = Sa22 + Stmp2;
  Sa32 = Sa32 - Stmp1;
  Stmp1 = Ss * Sa23;
  Stmp2 = Ss * Sa33;
  Sa23 = Sc * Sa23;
  Sa33 = Sc * Sa33;
  Sa23 = Sa23 + Stmp2;
  Sa33 = Sa33 - Stmp1;
  Stmp1 = Ss * Su12;
  Stmp2 = Ss * Su13;
  Su12 = Sc * Su12;
  Su13 = Sc * Su13;
  Su12 = Su12 + Stmp2;
  Su13 = Su13 - Stmp1;
  Stmp1 = Ss * Su22;
  Stmp2 = Ss * Su23;
  Su22 = Sc * Su22;
  Su23 = Sc * Su23;
  Su22 = Su22 + Stmp2;
  Su23 = Su23 - Stmp1;
  Stmp1 = Ss * Su32;
  Stmp2 = Ss * Su33;
  Su32 = Sc * Su32;
  Su33 = Sc * Su33;
  Su32 = Su32 + Stmp2;
  Su33 = Su33 - Stmp1;
  return std::make_tuple(Su11, Su12, Su13, Su21, Su22, Su23, Su31, Su32, Su33,
                         Sv11, Sv12, Sv13, Sv21, Sv22, Sv23, Sv31, Sv32, Sv33,
                         Sa11, Sa22, Sa33);
}

TLANG_NAMESPACE_END
