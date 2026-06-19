# POW function
In this file we will be discussing about the $n^{th}$ derivative of the function $f(x) = u(x)^c$  
The most familiar case that we encounter for this function is $c = \frac 1 2$. So let's take a look at it first.
## $\sqrt u(x)$:
The following derivation will be the slower version which just showcase some pascal's triangle manipulations, go to [quicker derivation](#quicker-derivation) if you want to see the result emerge quickly(I recommend taking a look at it anyway, because it might become easier to see through this longer derivation!)  
The first derivatives of the function $f = \sqrt u$, will be:
```math
f_1 = \frac {u_1} {2\sqrt u}
```
Since $f = \sqrt u$ it also equals:
```math
f_1 = \frac {u_1} {2f}
```
Multiplying both sides by $f$ we get:
```math
f_1f = \frac 1 2 u_1
```  
Let's define $h = f_1$ and $v = u_1$, now we have:  
```math
hf = \frac 1 2 v
```
By leibniz formula, we know that if we have some function $y = h\cdot f$, it's nth derivative is equal to:
```math
y_n = \sum_{k=0}^{n}\binom{n}{k}f_{k}h_{n-k}
```
On the **RHS**, differentiating n times will yield us $\frac 1 2 v_n$.  
After these operations, we have:
```math
\frac 1 2 v_n = \sum_{k=0}^{n}\binom{n}{k}f_{k}h_{n-k}
```
If we define an operator $D = \frac d {dx}$ and we have some function $f =  D^ku$, differentiating both sides w.r.t. $x$, n times, will result in $D^nf = D^{n+k}u$ or in our notation $f_n = u_{n+k}$.  
By this knowledge, we can replace $h_m \longrightarrow f_{m+1}$ and $v_m \longrightarrow u_{m+1}$, and now we have:
```math
\frac 1 2 u_{n+1} = \sum_{k=0}^{n}\binom{n}{k}f_{k}f_{n-k+1}
```
Replacing $n \longrightarrow n-1$, we get:  
```math
\frac 1 2 u_{n} = \sum_{k=0}^{n-1}\binom{n-1}{k}f_{k}f_{n-k}
```
If we take the $k = 0$ term out of the summation, we get:
```math
\frac 1 2 u_{n} = f\cdot f_n + \sum_{k=1}^{n-1}\binom{n-1}{k}f_{k}f_{n-k}
```  
Subtracting $\sum_{k=1}^{n-1}\binom{n-1}{k}f_{k}f_{n-k}$ from both sides, we get:
```math
\begin{equation}
f\cdot f_n = \frac 1 2 u_{n} - \sum_{k=1}^{n-1}\binom{n-1}{k}f_{k}f_{n-k}
\end{equation}
```
On the **RHS**, taking the LCM of 2, we get:
```math
\frac {u_{n} - 2\sum_{k=1}^{n-1}\binom{n-1}{k}f_{k}f_{n-k}} 2
```
If we take the summation as $S_1$:
```math
2\sum_{k=1}^{n-1}\binom{n-1}{k}f_{k}f_{n-k}
```
And let's take $S_2$:
```math
\sum_{k=1}^{n-1}\binom{n}{k}f_{k}f_{n-k}
```  
By Pascal's triangle, we know that:
```math
\binom{n}{k} = \binom{n-1}{k}+\binom{n-1}{k-1}
```
So:
```math
S_2 = \sum_{k=1}^{n-1}\binom{n-1}{k}f_{k}f_{n-k} + \sum_{k=1}^{n-1}\binom{n-1}{k-1}f_{k}f_{n-k}
```
Let's take $S_3$ as:
```math
\sum_{k=1}^{n-1}\binom{n-1}{k-1}f_{k}f_{n-k}
```
Taking a new index $j = n-k$, we get:
```math
\sum_{j=1}^{n-1}\binom{n-1}{j}f_{n-j}f_{j}
```
And because multiplication is commutative, we have $S_1 = 2S_3$ and $S_2=2S_3$ respectively, we have the result $S_1 = S_2$. $\begin{equation}\end{equation}$
Now, in equation $(1)$, if we divide both sides by $f$, we get:
```math
f_n = \frac {u_{n} - 2\sum_{k=1}^{n-1}\binom{n-1}{k}f_{k}f_{n-k}} {2f}
```
#### Quicker derivation:
Now, it could have been achieved much more easily if we consider than $f^2 = u$ and apply leibniz on it, which gives us:
```math
u_n = \sum_{k=0}^{n}\binom{n}{k}f_kf_{n-k}
```
Since, the first and the last term contain our desired $f_n$ terms, let's take them out of the summation:
```math
u_n = 2ff_n+\sum_{k=1}^{n-1}\binom{n}{k}f_kf_{n-k}
```
And with simple arrangements, we have:
```math
f_n = \frac {u_n-\sum_{k=1}^{n-1}\binom{n}{k}f_kf_{n-k}} {2f}
```
Which skips all the boilerplate work and lands us to our final result directly but hey! Who doesn't like getting mathematical rigor like the first one! (Sorry (not sorry) for trolling ya with the long proof :D but you did get some cool tricks with pascal's triangle's symmetry so maybe thank me instead :3 )
> [!IMPORTANT]
> And so our final recurrence relation for $\sqrt {u(x)}$ is:  
$f_n = \frac {u_{n} - 2\sum_{k=1}^{n-1}\binom{n-1}{k}f_{k}f_{n-k}} {2f}$  
Or using equation $(2)$:  
$f_n = \frac {u_{n} - \sum_{k=1}^{n-1}\binom{n}{k}f_{k}f_{n-k}} {2f}$  
$: n \ge 2$  
$f_1 = \frac {u_1} {2f}$  
$f = \sqrt u$

In code:
```python
def sqrt_derivatives(u_list, order):
    # u_list contains all the derivatives of u from order 0 till n
    
    # preserves space for all the derivatives of f
    f_list = [0.0] * (order + 1)
    f_list[0] = math.sqrt(u_list[0]) #f0 = sqrt(u0)

    # outer loop to calculate all the derivatives 1 till n
    for n in range(1, order + 1):

        # inner loop to calculate individual f{m}
        for k in range(1, n):
            f_list[n] -= nCr(n,k) * f_list[k] * f_list[n-k]
        f_list[n] += u_list[n]
        f_list[n] /= 2.0 * f_list[0]

    return f_list
```