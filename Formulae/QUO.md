# Fraction functions
Let's have a look at the functions of the format:\
f(x) = u(x)/v(x)

## 1/x
Let's start by looking at just the function `f(x) = 1/x`.
- [] Starting by derivating the first few derivatives of the function:
```
f₀: 1/x
f₁: -1/x²
f₂: 2/x³
f₃: -6/x⁴
f₄: 24/x⁵
```

Now, the astute amongst you might have spotted it already but what we are looking at here is\
`The factorial numbers!`, which goes on as:\
`1 1 2 6 24 120`, represented as `n!` where `n!` means `n⋅(n-1)⋅(n-2)⋅...1`, where at the `n=0` the value is `1` instead of `0`!

> [!IMPORTANT]
> So this can be easily summed up as:\
f<sub>n</sub> = -1<sup>n</sup>⋅n!/x<sup>n+1</sup>

## 1/u(x)
Let's now do it for the function `f(x) = 1/u(x)`.
- [] Starting by derivating the first few derivatives of the function:
```
f₀: 1/u₀
f₁: -u₁/u₀²
f₂: -u₂/u₀² + 2u₁²/u₀³
f₃: -u₃/u₀² + 6u₂u₁/u₀³ - 6u₁³/u₀⁴
f₄: -u₄/u₀² + 8u₃u₁/u₀³ + 6u₂²/u₀³ + 24
```