# Sin and Cos

The characters where the story known as trigonometry starts at the simple and delightful, $\sin$ & $\cos$.  

Starting with:
## $\sin(u(x))$
There are plethora of ways we can tackle this problem and we will take a look at various ways.  
Let's get right into it, so, we have our function $f(x) = \sin(u(x))$ or 
```math
f = \sin(u)
```
differentiating both sides gives us:
```math
\begin{equation}
f_1 = u_1\cos(u)
\end{equation}
```
squaring both sides will give us:
```math
f_1^2 = u_1^2\cos^2(u)
```
using the pythagorean identity $\sin^2(x) + \cos^2(x) = 1$ we can replace $\cos^2(u)$ with $1 - \sin^2(u)$ in our equation, giving us:
```math
f_1^2 = u_1^2(1-\sin^2(u))
```
and since $f = \sin(u)$, replacing $\sin$ with $f$, we get:
```math
f_1^2 = u_1^2(1-f^2)
```
or
```math
\begin{equation}
f_1^2 = u_1^2-(u_1f)^2
\end{equation}
```

If we apply Leibniz's rule on both sides of the equation $n-1$ times, we get:
```math
\sum_{k=0}^{n-1}\binom{n-1}{k}f_{k+1}f_{n-k}=\sum_{k=0}^{n-1}\binom{n-1}{k}u_{k+1}u_{n-k}-\sum_{k=0}^{n-1}\binom{n-1}{k}\left(\sum_{r=0}^{k}\binom{k}{r}u_{r+1}f_{k-r}\right)\left(\sum_{r=0}^{n-k-1}\binom{n-k-1}{r}u_{r+1}f_{n-k-r-1}\right)
```
That is pure mess, but let's work with it...  
Looking at the LHS, we can see that $f_n$ appears only two times in that summation, the first $k=0$ and the last $k=n-1$ terms, so taking them out of the summation, we get:
```math
2f_{1}f_{n}=\sum_{k=0}^{n-1}\binom{n-1}{k}u_{k+1}u_{n-k}-\sum_{k=0}^{n-1}\binom{n-1}{k}\left(\sum_{r=0}^{k}\binom{k}{r}u_{r+1}f_{k-r}\right)\left(\sum_{r=0}^{n-k-1}\binom{n-k-1}{r}u_{r+1}f_{n-k-r-1}\right)-\sum_{k=1}^{n-2}\binom{n-1}{k}f_{k+1}f_{n-k}
```
To put everything under a single summation, let's pull $k=0$ and $k=n-1$ terms from the other summations too
```math
2f_{1}f_{n}=2u_{1}u_{n}-2u_{1}f\sum_{k=0}^{n-1}\binom{n-1}{k}u_{k+1}f_{n-k-1}+\sum_{k=1}^{n-2}\binom{n-1}{k}u_{k+1}u_{n-k}-\sum_{k=1}^{n-2}\binom{n-1}{k}\left(\sum_{r=0}^{k}\binom{k}{r}u_{r+1}f_{k-r}\right)\left(\sum_{r=0}^{n-k-1}\binom{n-k-1}{r}u_{r+1}f_{n-k-r-1}\right)-\sum_{k=1}^{n-2}\binom{n-1}{k}f_{k+1}f_{n-k}
```
and let's take out the $k=0$ and $k=n-1$ terms from the newly generated summation as well
```math
2f_{1}f_{n}=2u_{1}u_{n}-2u_{1}^{2}ff_{n-1}-2u_{1}u_{n}f^2-2u_{1}f\sum_{k=1}^{n-2}\binom{n-1}{k}u_{k+1}f_{n-k-1}+\sum_{k=1}^{n-2}\binom{n-1}{k}u_{k+1}u_{n-k}-\sum_{k=1}^{n-2}\binom{n-1}{k}\left(\sum_{r=0}^{k}\binom{k}{r}u_{r+1}f_{k-r}\right)\left(\sum_{r=0}^{n-k-1}\binom{n-k-1}{r}u_{r+1}f_{n-k-r-1}\right)-\sum_{k=1}^{n-2}\binom{n-1}{k}f_{k+1}f_{n-k}
```
and now collapse it
```math
2f_{1}f_{n}=2u_{1}u_{n}-2u_{1}^{2}ff_{n-1}-2u_{1}u_{n}f^2+\sum_{k=1}^{n-2}\binom{n-1}{k}\left(u_{k+1}u_{n-k}-f_{k+1}f_{n-k}-2u_{1}fu_{k+1}f_{n-k-1}-\left(\sum_{r=0}^{k}\binom{k}{r}u_{r+1}f_{k-r}\right)\left(\sum_{r=0}^{n-k-1}\binom{n-k-1}{r}u_{r+1}f_{n-k-r-1}\right)\right)
```
simplifying a bit
```math
\begin{align*}
2f_{1}f_{n}&=2u_{1}u_{n}(1-f^2)-2u_{1}^{2}ff_{n-1}+\sum_{k=1}^{n-2}\binom{n-1}{k}\left(u_{k+1}(u_{n-k}-2u_{1}ff_{n-k-1})-f_{k+1}f_{n-k}-\left(\sum_{r=0}^{k}\binom{k}{r}u_{r+1}f_{k-r}\right)\left(\sum_{r=0}^{n-k-1}\binom{n-k-1}{r}u_{r+1}f_{n-k-r-1}\right)\right) \\
f_n&=\frac{u_1}{f_1}\left(u_n(1-f^2)-u_1ff_{n-1}\right)+\frac{1}{2f_1}\sum_{k=1}^{n-2}\binom{n-1}{k}\left(u_{k+1}(u_{n-k}-2u_{1}ff_{n-k-1})-f_{k+1}f_{n-k}-\left(\sum_{r=0}^{k}\binom{k}{r}u_{r+1}f_{k-r}\right)\left(\sum_{r=0}^{n-k-1}\binom{n-k-1}{r}u_{r+1}f_{n-k-r-1}\right)\right) \\
\frac{u_1}{f_1}&=\frac{1}{\cos(u)}\quad(\text{from eq. 1}) \\
f_n&=u_n\cos(u)-u_1f_{n-1}\tan(u)+\frac{1}{2f_1}\sum_{k=1}^{n-2}\binom{n-1}{k}\left(u_{k+1}(u_{n-k}-2u_{1}ff_{n-k-1})-f_{k+1}f_{n-k}-\left(\sum_{r=0}^{k}\binom{k}{r}u_{r+1}f_{k-r}\right)\left(\sum_{r=0}^{n-k-1}\binom{n-k-1}{r}u_{r+1}f_{n-k-r-1}\right)\right) \\
\end{align*}
```
And we have our formula!
```math
f_n=u_n\cos(u)-u_1f_{n-1}\tan(u)+\frac{1}{2f_1}\sum_{k=1}^{n-2}\binom{n-1}{k}\left(u_{k+1}(u_{n-k}-2u_{1}ff_{n-k-1})-f_{k+1}f_{n-k}-\left(\sum_{r=0}^{k}\binom{k}{r}u_{r+1}f_{k-r}\right)\left(\sum_{r=0}^{n-k-1}\binom{n-k-1}{r}u_{r+1}f_{n-k-r-1}\right)\right)
```
Implemented it might look like:
```python
def sin_derivatives(u_list, order):
    # u_list contains all derivatives of sin(u) from order 0..n at some point x

    f_list = [0.0] * (order + 1) # reserving space for all the derivatives of f
    f_list[0] = math.sin(u_list[0])
    cosu = math.cos(u_list[0])
    tanu = math.tan(u_list[0])

    if order > 0:
        f_list[1] = u_list[1] * cosu

    for n in range(2, order + 1):
        f_list[n] += u_list[n] * cosu - u_list[1] * f_list[n-1] * tanu

        sum = 0.0
        for k in range(1, n - 1):

            inner_sum_1 = 0.0
            for r in range(k + 1):
                inner_sum_1 += nCr(k, r) * u_list[r + 1] * f_list[k-r]

            inner_sum_2 = 0.0
            for r in range(n - k):
                inner_sum_2 += nCr(n-k-1, r) * u_list[r + 1] * f_list[n-k-r-1]
            
            sum += u_list[k+1]*(u_list[n-k]-2*u_list[1]*f_list[0]*f_list[n-k-1])
            sum -= f_list[k+1]*f_list[n-k]
            sum -= inner_sum_1 * inner_sum_2
        
        f_list[n] -= sum / (2 * f_list[1])
    
    return f_list
```