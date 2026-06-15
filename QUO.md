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

Which in the actual practice would be just:
```python
one_over_x_derivatives(point, derivative_number):
    result = math.gamma(derivative_number + 1) / pow(x, n+1)
    return result if derivative_number % 2 == 0 else -result
```

## 1/u(x)
Let's now do it for the function `f(x) = 1/u(x)`.
- [] Starting by derivating the first few derivatives of the function:
```
f₀: 1/u₀
f₁: -u₁/u₀²
f₂: -u₂/u₀² + 2u₁²/u₀³
f₃: -u₃/u₀² + 6u₂u₁/u₀³ - 6u₁³/u₀⁴
f₄: -u₄/u₀² + 8u₃u₁/u₀³ + 6u₂²/u₀³ + 24u₁⁴/u₀⁵
```

Hmmm, doesn't seem like it makes a formula, does it?\
- [] Let's do it our way!:
```
f₀: 1/u₀
f₁: -u₁f₀/u₀
f₂: -u₂f₀/u₀ - 2u₁f₁/u₀
f₃: -u₃f₀/u₀ - 3u₂f₁/u₀ - 3u₁f₂/u₀
f₄: -u₄f₀/u₀ - 4u₃f₁/u₀ - 6u₂f₂/u₀ - 4u₁f₃/u₀
```

There it is!\
Now, the astute amongst you might be able to see the formula emerging from it.

> [!IMPORTANT]
> Which would be:
f<sub>n</sub> = -1/u₀⋅**<sub>i=0</sub><sup>n-1</sup>∑** (<sup>n</sup><sub>i</sub>)⋅f<sub>i</sub>⋅u<sub>n-i</sub>

> [!NOTE]
> The important thing to note here is that f₀ will be 1/u₀ and not -1/u₀  
and is only defined when `u₀ != 0`

In practice, it would something like this:
```python
reciprocal_derivatives(u_list, derivative_number):
    f_list = [0.0] * (derivative_number+1)
    f_list[0] = 1/u_list[0]
    for k in range(1, derivative_number):
        for i in range(k):
            f_list[k] += nCr(k, i) * f_list[i] * u_list[k - i];
        f_list[k] /= -u_list[0]
    return f_list
```

Now, I recommend you derive the formula for f(x) = u(x) / v(x) before we get into the next section, as there is also a very neat process to do so too.

## u(x)/v(x)

Let's just get straight into this one without really doing boiler plate work.\
No, that would be for the reader but for the elegant solution, here it is:

As we derived the `leibniz's formula` in the [`README`](README.md)\
We can use that as our base!\
Leibniz's formula:\
f<sub>n</sub> = **<sub>k=0</sub><sup>n</sup>∑** (<sup>n</sup><sub>k</sub>)⋅u<sub>n-k</sub>⋅v<sub>k</sub>\
Let's change the name of u to f and f to u.

So, we will have:\
u<sub>n</sub> = **<sub>k=0</sub><sup>n</sup>∑** (<sup>n</sup><sub>k</sub>)⋅f<sub>n-k</sub>⋅v<sub>k</sub>\

Now, let's take n = 3 for example:\
`u₃ = f₃⋅v₀ + 3⋅f₂⋅v₁ + 3⋅f₁⋅v₂ + f₀⋅v₃`\
Or:\
`u₃ = f₀⋅v₃ + 3⋅f₁⋅v₂ + 3⋅f₂⋅v₁ + f₃⋅v₀`\
Let's send `u₃` to the other side and `f₃⋅v₀` to the other side of the `=`.\
We will get:\
`-f₃⋅v₀ = -u₃ + 3⋅f₁⋅v₂ + 3⋅f₂⋅v₁`\
And then divide both sides by `-v₀`\
And then we would have:\
`f₃ = (u₃ - (f₀⋅v₃ + 3⋅f₁⋅v₂ + 3⋅f₂⋅v₁))/v₀`

Do you see it???\
It's almost the same as the `1/u₀` that we derived!

Here:\
> [!IMPORTANT]
> The formula that would come out is:  
f<sub>n</sub> = (u<sub>n</sub> - **<sub>i=0</sub><sup>n-1</sup>∑** ((<sup>n</sup><sub>i</sub>}·v<sub>n-i</sub>·f<sub>i</sub>))/v₀  
or:  
f<sub>n</sub> = (u<sub>n</sub> - **<sub>i=1</sub><sup>n</sup>∑** ((<sup>n</sup><sub>i</sub>}·v<sub>i</sub>·f<sub>n-i</sub>))/v₀  

Which in practice would look like:\
```python
div_derivatives(u_list, v_list, derivative_number):
    f_list = [0] * (derivative_number + 1)
    for k in range(derivative_number + 1):
        for i in range(k):
            f_list[k] -= nCr(k, i) * v_list[k-i] * f_list[i]
        f_list[k] += u_list[k]
        f_list[k] /= v_list[0]
    return f_list
```

Now, you can continue back to the [`logarithm`](LN.md)!