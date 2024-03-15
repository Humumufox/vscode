# 针对特定模式的递归转迭代的自底向上方法

自底向上也即从终止条件的返回值和参数出发，不断地**求解参数**，同时更新返回值，直到计算得到的参数（记为*估计参数*）和**原始参数**相同时，返回对应的返回值。

在这一过程中，如果递归调用时的参数是由参数（或者模式匹配解包出来的变量）经过计算得到的，需要这一过程的**逆计算**（同时意味着运算可逆），如果只依赖解包的参数，则只需要将模式当做表达式处理，即可求解参数。

同时这一方法，需要**估计参数**能够和原始参数进行比较，意味着求解参数的过程只依赖模式的运算，而不依赖模式中，未在返回时使用的变量，换句话说，参数的所有信息，都可以由返回值计算得到。

## 单参数

### 1 单终止条件和单次递归调用

```
fact 0 = 1
fact (Suc n) = (Suc n) * (fact n)
```

```
appro = 0; res = 1

appro = 0 -> n = 0
res = 1 -> (fact n) = 1

appro = Suc 0
res = (Suc 0) * 1
```

#### 反例

> 参数存在未知部分，无法通过自底向上的过程构造

```
length [] = 0
length x # xs = (length xs) + 1
```

```
appro = []; res = 0

appro = [] -> xs = []
res = 0 -> (length xs) = 0

appro = x # [] // `x` 依赖自顶向下传递的参数
res = 0 + 1
```

### 2 多终止条件和单次递归调用

多条件单调用时，原始参数只对应其中一个终止条件。可以同时维护以这些终止条件为起点的求解过程，直到其中一个的估计参数与原始参数相等。

```
fact 0 = 1
fact 1 = 1
fact (Suc (Suc n)) = (Suc n) * (fact n)
```

```
appro = 0; res = 1

appro = 0 -> n = 0
res = 1 -> (fact n) = 1

appro = Suc (Suc 0)
res = (Suc 0) * 1

---

appro = 1; res = 1

appro = 1 -> n = 1
res = 1 -> (fact n) = 1

appro = Suc (Suc 1)
res = (Suc 1) * 1
```

> 这里可以考虑使用累加器

### 3 单终止条件和多次递归调用

单条件多调用时，一般不同的调用的实参不相同，实参由调用者的参数经过（不同的）计算得到。

```
foo 0 = 1
foo n = (foo (n / 2)) + (foo (n - 1))
```

```
appro = 0; res = 1

appro = 0 -> n - 1 = 0 -> n = 1 // 此处需要逆运算
res = 1 -> foo (n - 1) = 1

appro = 1
res = (foo (1 / 2)) + 1 = (foo 0) + 1 // 此处的 foo 0 可以递归调用
```

尽管仍包含递归调用，但是可以消除其中部分递归。

### 4 多终止条件和多次递归调用

```
fib 0 = 1
fib 1 = 1
fib n = (fib (n - 1)) + (fib (n - 2))
```

结合 2 和 3 可以实现消除部分的递归，但是需要 bfs 求解参数，同时未被消除的递归调用会令并行求解过程实际调用次数增加。

```
// 1 1 2 3 5 8

fib 5 = fib 4 + fib 3   // 1
fib 4 = fib 3 + fib 2   // 1
fib 3 = fib 2 + fib 1   // 2
fib 2 = fib 1 + fib 0   // 2 + 1 = 3
fib 1 = 1               // 3 + 2 = 5
fib 0 = 1               // 3

fib 5 = fib 4 + fib 3
      = fib 3 + fib 2 + fib2 + fib1
      = fib 2 + fib 1 + fib 1 + fib 0 + fib 1 + fib 0 + 1
      = fib 1 + fib 0 + 1 + 1 + 1 + 1 + 1 + 1
      = 8
```

函数调用次数为 15 次，假设消除掉 fib (n - 2)，则调用次数仅减少为 14 次（有增加的可能）。

```
fib 5 =                                                 // 1
0, 1 -> 2, (fib 1) + 1 -> 4, (fib 3) + (fib 1) + 1
1, 1 -> 3, (fib 2) + 1 -> 5, (fib 4) + (fib 2) + 1

fib 4 =                                                 // 1
0, 1 -> 2, (fib 1) + 1 -> 4, (fib 3) + (fib 1) + 1
1, 1 -> 3, (fib 2) + 1

fib 3 =                                                 // 1 + 1 = 2
0, 1 -> 2, (fib 1) + 1
1, 1 -> 3, (fib 2) + 1

fib 2 =                                                 // 1 + 2 = 3
0, 1 -> 2, (fib 1) + 1
1, 1

fib 1   // 1 + 1 + 2 + 3 = 7
fib 0   // 0
```

### 总结

当终止条件只有一个时，递归调用可以（部分）消除，而在多条件时，则不适合采用这种方法。
当终止条件为多个，递归调用只有一次时，可以使用添加累加器的方式，但是需要求解单位元。

## 多参数