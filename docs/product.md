# Product functions

We have our function $f = u \cdot v$  
If we differentiate it *once* applying the product rule, we get:  
```math
f_1 = u_1 v + uv_1
```

## Guessing the formula
Derivating the function a few more times gives us:
```math
\begin{align*}
&f = u v  \\
&f_1 = u_1 v + u v_1  \\
&f_2 = u_2 v + 2u_1 v_1 + u v_2  \\
&f_3 = u_3 v + 3u_2 v_1 + 3u_1 v_2 + u v_3  \\
&f_4 = u_4 v + 4 u_3 v_1 + 6 u_2 v_2 + 4 u_1 v_3 + u v_4  \\
&\cdots
\end{align*}
```
If we separate all the coefficients, we get:  
```math
\begin{gather*}
C_0 = 1  \\
C_1 = 1, 1  \\
C_2 = 1, 2, 1  \\
C_3 = 1, 3, 3, 1  \\
C_4 = 1, 4, 6, 4, 1  \\
\cdots
\end{gather*}
```
These is the Pascal's triangle!  
And if we separate the order of $u$ in each derivative we get:
```math
\begin{gather*}
f : 0 \\
f_1 : 1, 0 \\
f_2 : 2, 1, 0 \\
f_3 : 3, 2, 1, 0 \\
f_4 : 4, 3, 2, 1, 0 \\
\cdots
\end{gather*}
```
These just go down to $0$ from the order $n$ in each successive term.  
And doing the same for $v$ gives us:
```math
\begin{gather*}
f : 0 \\
f_1 : 0, 1 \\
f_2 : 0, 1, 2 \\
f_3 : 0, 1, 2, 3 \\
f_4 : 0, 1, 2, 3, 4 \\
\cdots
\end{gather*}
```
These do the opposite of $u$ and go from $0\to n$.  
That gives us all the information for writing our formula!

> [!IMPORTANT]
> If we were to write it in a compact form, we would get:  
$`f_n = \sum_{k = 0}^n\binom{n}{k} u_{n-k} v_{k}`$

## Formal proof  
We will prove it by Mathematical Induction.  

**Step 1:**  
Base Case $(n=1)$  
We verify the rule for $n=1$: 
```math
\frac{d^1}{dx^1} (f \cdot g) = \sum_{k=0}^{1} \binom{1}{k} f^{(1-k)} g^{(k)}
```
Expanding the sum for $k=0$ and $k=1$:
```math
\binom{1}{0} f^{(1)} g^{(0)} + \binom{1}{1} f^{(0)} g^{(1)} = (1) f'g + (1) f g'= f'g + fg'
```
This matches the standard product rule of calculus. Thus, the base case holds true.  

**Step 2:**  
Inductive Hypothesis  
Let's assume that our rule holds true for some arbitrary positive integer $m$, meaning:
```math
\frac{d^m}{dx^m} (f \cdot g) = \sum_{i=0}^{m} \binom{m}{i} f^{(m-i)} g^{(i)}
```

**Step 3:**  
Inductive Step $(n = m+1)$  
Now we must prove that the rule holds for $n = m+1$. We take the derivative of the $m^{th}$ derivative:
```math
\frac{d^{m+1}}{dx^{m+1}} (f \cdot g) = \frac{d}{dx} \left[ \frac{d^m}{dx^m} (f \cdot g) \right]
```
Substitute the inductive hypothesis into the equation
```math
\frac{d}{dx} \left[ \sum_{i=0}^{m} \binom{m}{i} f^{(m-i)} g^{(i)} \right]
```
Since the derivative is a linear operator, we can differentiate the sum term-by-term. By applying the standard product rule to the terms inside the summation, we get
```math
\sum_{i=0}^{m} \binom{m}{i} \left( f^{(m-i+1)} g^{(i)} + f^{(m-i)} g^{(i+1)} \right)
```
We can split this into two separate summations:
```math
\sum_{i=0}^{m} \binom{m}{i} f^{(m+1-i)} g^{(i)} + \sum_{i=0}^{m} \binom{m}{i} f^{(m-i)} g^{(i+1)}
```
In the second sum, let's shift the index of summation by substituting $j = i+1$. When $i=0$, $j=1$; when $i=m$, $j=m+1$. Substituting these in yields:
```math
\sum_{i=0}^{m} \binom{m}{i} f^{(m+1-i)} g^{(i)} + \sum_{j=1}^{m+1} \binom{m}{j-1} f^{(m-(j-1))} g^{(j)}
```
Adjust the dummy variable $j$ back to $i$ in the second sum
```math
\sum_{i=0}^{m} \binom{m}{i} f^{(m+1-i)} g^{(i)} + \sum_{i=1}^{m+1} \binom{m}{i-1} f^{(m+1-i)} g^{(i)}
```
Next, we extract the $i=0$ term from the first sum and the $i=m+1$ term from the second sum to combine the remaining terms
```math
\binom{m}{0} f^{(m+1)} g + \left[ \sum_{i=1}^{m} \binom{m}{i} f^{(m+1-i)} g^{(i)} + \sum_{i=1}^{m} \binom{m}{i-1} f^{(m+1-i)} g^{(i)} \right] + \binom{m}{m} f g^{(m+1)}
```
Factor out the matching terms in the brackets: 
```math
\binom{m}{0} f^{(m+1)} g + \sum_{i=1}^{m} \left[ \binom{m}{i} + \binom{m}{i-1} \right] f^{(m+1-i)} g^{(i)} + \binom{m}{m} f g^{(m+1)}
```
By using Pascal's Identity for binomial coefficients, $\binom{m}{i} + \binom{m}{i-1} = \binom{m+1}{i}$, and observing that $\binom{m}{0} = \binom{m+1}{0} = 1$ and $\binom{m}{m} = \binom{m+1}{m+1} = 1$, we can rewrite the expression as:
```math
\binom{m+1}{0} f^{(m+1)} g + \sum_{i=1}^{m} \binom{m+1}{i} f^{(m+1-i)} g^{(i)} + \binom{m+1}{m+1} f g^{(m+1)}
```
We can now *re-absorb* the boundary terms back into the summation:
```math
\sum_{i=0}^{m+1} \binom{m+1}{i} f^{(m+1-i)} g^{(i)}
```
**Conclusion:** This exact result is the Leibniz formula with n replaced by m+1. Therefore, by the principle of mathematical induction, the formula we derived holds *true for all positive integers n*. 


A really elegant and simple formula that computes the desired derivatives in $O(n)$ (given that we know all $(u\to u_n) \text{ and }(v \to v_n)$)  
In practice, it will look something like this:  
```python
def product_derivative(u_list, v_list, order):
    # u_list is the list of derivatives of u from 0 upto `order` like:
    # [u0(a), u1(a), u2(a)...u{n}(a)]
    # same with v_list

    result = 0.0

    for k in range(order + 1):
        # nCr(n, k) * u{n-k} * v{k}
        result += nCr(order, k) * u_list[order - k] * v_list[k]
    
    return result
```
Or if we are going to calculate all the derivatives from $0 \to n$ then:
```python
def product_derivatives(u_list, v_list, order):
    # calculate individual product derivative orders and create a list
    f_list = [product_derivative(u_list, v_list, n) for n in range(order + 1)]
    return f_list
```
This result is pretty well known and is referred to as `Leibniz's theorem`  