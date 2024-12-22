# AdditiveOfOperation
ℤ を整数の集合とする。

ℕ₂ を2以上の整数の集合とする。

m+n = m☆m☆…☆m (mがn個) が成り立つような2項演算 ☆: ℕ₂×ℕ₂→ℕ₂ において、

ℕ₂→ℕ₂-{m}; n↦m☆n が全単射であることは、

☆⁽⁰⁾ = ☆ かつ

m☆⁽ʳ⁻¹⁾m☆⁽ʳ⁻¹⁾…☆⁽ʳ⁻¹⁾m (mがn個) = m☆⁽ʳ⁾n であるような

2項演算の列 (☆⁽⁻ʳ⁾)ᵣ₌₀ が存在する必要十分条件である。

そしてこのとき a⁽⁻ʳ⁾, A⁽⁻ʳ⁾: ℤ→ℤ を

a⁽⁻ʳ⁾◦Succ(n) = A⁽⁻ʳ⁾(n) =

                            {n+1      (n ≤ 0)

                            {m        (n = 1)

                            {m☆⁽⁻ʳ⁾n (n ≥ 2)                                         
                                                               
で定めれば A⁽⁻ʳ⁻¹⁾ = A⁽⁻ʳ⁾◦Succ◦A⁽⁻ʳ⁾⁻¹だから

A⁽⁻ʳ⁻¹⁾ = a⁽⁻ʳ⁾◦Succ◦Succ◦Succ⁻¹◦a⁽⁻ʳ⁾⁻¹ = a⁽⁻ʳ⁾◦Succ◦a⁽⁻ʳ⁾⁻¹であり、

a⁽⁻ʳ⁻¹⁾ = A⁽⁻ʳ⁻¹⁾◦Succ⁻¹ = a⁽⁻ʳ⁾◦Succ◦a⁽⁻ʳ⁾⁻¹◦Succ⁻¹となる。

さらに a⁽⁰⁾ は巡回する部分が有限な巡回置換の積であり、

帰納的に a⁽⁻ʳ⁾ もそうである。

これはそのような a⁽⁻ʳ⁾, A⁽⁻ʳ⁾ を計算するプログラムである。
