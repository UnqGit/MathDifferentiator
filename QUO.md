# Fraction functions
Let's have a look at the functions of the format:  
$f(x) = \frac {u(x)} {v(x)}$

## $\frac {1} {x}$:
Let's start by looking at just $f(x) = \frac {1} {x}$.  
Starting by derivating the first few derivatives of the function:
```math
\begin{align*}
&f = \frac {1} {x} \\
&f_1 = -\frac {1} {x^2} \\
&f_2 = \frac {2} {x^3} \\
&f_3 = -\frac {6} {x^4} \\
&f_4 = \frac {24} {x^5} \\
\end{align*}
```

Now, the astute amongst you might have spotted it already there are factorials in here!  
Since $\frac {d} {dx} x^n = nx^{n-1}$ and here the function $\frac 1 x$ is just $x^{-1}$ so each consecutive differentiation step brings another negative number down and decrements the power to the next negative integer, we get:  
$\prod_{k=1}^n-k$ as the coefficient of $x^{-(n+1)}$ in $f_n$ which is the same as $(-1)^n\cdot n!$.


> [!IMPORTANT]
> So this can be easily summed up as:  
$f_n = (-1)^n \frac {n!} {x^{n+1}}$

Which in practice, would be just:
```python
def one_over_x_derivatives(point, order):
    # n!/x^(n+1)
    result = math.gamma(order + 1) / pow(x, order + 1)
    # since (-1)^n has only two possible states because n is a +ve integer.
    # it will be 1 if n is even and -1 if n is odd
    return result if order % 2 == 0 else -result
```

## $\frac 1 {u(x)}$:
Let's now do it for the function $f(x) = \frac 1 {u(x)}$.  
Starting by derivating the first few derivatives of the function:
```math
\begin{align*}
&f = \frac {1} {u} \\
&f_1 = - \frac {u_1} {u^2} \\
&f_2 = - \frac {u_2} {u^2} + 2\frac {u_1^2} {u^3} \\
&f_3 = - \frac {u_3} {u^2} + 6\frac {u_2u_1} {u^3} - 6\frac {u_1^3} {u^4} \\
&f_4 = - \frac {u_4} {u^2} + 8\frac {u_3u_1} {u^3} + 6\frac {u_2^2} {u^3} + 24\frac {u_1^4} {u^5} \\
\end{align*}
```

Hmmm, looks interesting but doesn't seem like it makes a formula, does it?  
*[Bell polynomials](https://en.wikipedia.org/wiki/Bell_polynomials)  
Let's do it our way, by replacing with previous definitions:
```math
\begin{align*}
&f = \frac {1} {u} \\
&f_1 = - \frac {u_1f} {u} \\
&f_2 = - \frac {u_2f} {u} - 2\frac {u_1f_1} {u} \\
&f_3 = - \frac {u_3f} {u} - 3\frac {u_2f_1} {u} - 3\frac {u_1f_2} {u} \\
&f_4 = - \frac {u_4f} {u} - 4\frac {u_3f_1} {u} - 6\frac {u_2f_2} {u} - 4\frac {u_1f_3} {u} \\
\end{align*}
```

There it is!  
Now, the some of you might be able to see the formula emerging from it.  
If you look at the coefficients, they are:
```math
\begin{gather*}
C_1 = -1 \\
C_2 = -1,-2 \\
C_3 = -1,-3,-3 \\
C_4 = -1,-4,-6,-4 \\
\end{gather*}
```
For context, the pascal's triangle:
```math
\begin{gather*}
1\\
1,1\\
1,2,1\\
1,3,3,1\\
1,4,6,4,1\\
\cdots
\end{gather*}
```
The coefficients match from row 1 and onwards excluding the final term!  
If we look at the orders of $u$ in each of the $f_n$, we will see:
```math
\begin{gather*}
f_1 : 1\\
f_2 : 2,1\\
f_3 : 3,2,1\\
f_4 : 4,3,2,1\\
\end{gather*}
```
Each decrease from $n$ till $1$ !  
And if we look at the orders of the previous derivatives of $f$ used, we can see:
```math
\begin{gather*}
f_1 : 0\\
f_2 : 0,1\\
f_3 : 0,1,2\\
f_4 : 0,1,2,3\\
\end{gather*}
```
Each increases from $0$ till $n-1$ !  
So by seeing the pattern and trying to make a formula out of it
> [!IMPORTANT]
> We will get:  
$f_n = -\frac {1} {u} \sum_{k=0}^{n-1}\binom{n}{k}f_{k}u_{n-k}$  
Or by index manipulation:  
$f_n = -\frac {1} {u} \sum_{k=1}^{n}\binom{n}{k}f_{n-k}u_{k}$  
where $n \ge 1$ and $u(a) \ne 0$


In practice, it would be something like this:
```python
def reciprocal_derivatives(u_list, order):
    # u_list holds all the derivatives of the function u (0 till n)
    # at some point 'a'
    f_list = [0.0] * (order+1) # making space for f0, f1, f2 ... f{n}
    f_list[0] = 1 / u_list[0] # f0 = 1/u

    # outer loop to calculate all f{1...n}
    for n in range(1, order):

        #inner loop to calculate individual f{m}
        for k in range(n):
            f_list[n] += nCr(n, k) * f_list[k] * u_list[n - k]

        # applying the factor of -1/u0
        f_list[n] /= -u_list[0]

    return f_list
```

Now, I recommend you derive the formula for $f(x) = \frac{u(x)} {v(x)}$ before we get into the next section, as there is also a very neat process to do so too.

## $\frac {u(x)} {v(x)}$:

Let's just get straight into this one without really doing boiler plate work.  
The above section might have seemed a little *'hand wavy'* for some of you, now let's actually derive it using known results so it may seem a little more concrete.

As we derived the *leibniz's formula* in the [README](README.md)  
We can use that to our advantage.  
Leibniz's formula:  
$f_n = \sum_{k=0}^n\binom{n}{k}u_{n-k}v_k$  
now here to our function $f(x) = \frac {u(x)} {v(x)}$ ($v(x) \ne 0$).
Let's multiply both sides with $v(x)$, and so we get: $f\cdot v = u$, by applying the leibniz formula on it, we get:
```math
u_n = \sum_{k=0}^n\binom{n}{k}f_{n-k}v_k
```
Which we can rewrite as:  
```math
u_n = \binom{n}{0}f_nv_0 + \sum_{k=1}^n\binom{n}{k}f_{n-k}v_{k}
```
And since $\binom{n}{r} = \frac {n!} {r!(n-r)!}$ and $0! = 1$.  
If we calculate $\binom{n}{0}$, it would equal $\frac{n!}{0!n!}$ which is $1$. So we get:  
```math
u_n = f_nv + \sum_{k=1}^n\binom{n}{k}f_{n-k}v_{k}
```
Subtracting both sides by $\sum_{k=1}^n\binom{n}{k}f_{n-k}v_{k}$, we get:
```math
f_nv = u_n - \sum_{k=1}^n\binom{n}{k}f_{n-k}v_{k}
```
Since we assumed $v(x) \ne 0$, divide both sides by $v$ and we get:
```math
f_n = \frac {u_n - \sum_{k=1}^n\binom{n}{k}f_{n-k}v_{k}} {v}
```
> [!IMPORTANT]
> The final formula that comes out is:  
$f_n = \frac {u_n - \sum_{k=1}^n\binom{n}{k}f_{n-k}v_{k}} {v}$  
or:  
$f_n = \frac {u_n - \sum_{k=0}^{n-1}\binom{n}{k}v_{n-k}f_{k}} {v}$  
Where $n \ge 1$ and $f_0 = \frac u v$.

It's implementation looks like:  
```python
def div_derivatives(u_list, v_list, order):
    # u_list and v_list are all the derivattives of u and v respectively
    # from order 0 till n at a particular point 'a'
    f_list = [0.0] * (order + 1) # making space for the derivatives of f

    # outer loop to calculate all f {0...n}
    for n in range(order + 1):

        # calculating individual f{m}
        for k in range(n):
            # subtracting terms from the summation part
            f_list[n] -= nCr(n, k) * v_list[n-k] * f_list[k]
        
        # adding the single u{n} part and dividing everything by v
        f_list[n] += u_list[n]
        f_list[n] /= v_list[0]

    return f_list
```

Getting back at the $f = \frac 1 u$, if in $f=\frac u v$ we consider $u\to1$ and $v\to u$ and $n\ge1$, then $\frac {d^n} {dx^n} 1 = 0$ $\forall$ $n \ge1$, we get:  
> using $f_n = \frac {u_n - \sum_{k=0}^{n-1}\binom{n}{k}v_{n-k}f_{k}} {v}$  

$f_n = -\frac{1}{u}\sum_{k=0}^{n-1}\binom{n}{k}u_{n-k}f_k$, this is the same we got by the *look and guess* process so we can confirm our earlier result was true!

Now, you can continue back to the [`logarithm`](LN.md)!