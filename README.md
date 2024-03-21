## 简单说明

---

CLF约束  

$\frac{2 \cdot (v - v_d)}{m} \cdot u + \lambda \cdot (v - v_d)^2 \leq \delta$  

CBF约束  

$-\frac{u}{m} \cdot (Th + \frac{v-v_0}{c \cdot g}) + (v_0 - v) + \gamma \cdot (z- Th \cdot v - \frac{1}{2} \cdot \frac{(v - v_0)^2}{c \cdot g}) \geq 0$  

化简得到，  
CLF约束中u的系数  
$aCLF = \frac{2 \cdot (v - v_d)}{m}$  

CLF约束中不等式常数项  
$constraintValueCLF = -\lambda \cdot (v - v_d)^2 + \delta$  

CBF约束中u的系数  
$aCBF = \frac{1}{m} \cdot (Th + \frac{v-v_0}{c \cdot g})$  

CBF约束中不等式常数项  
$constraintValueCBF = (v_0 - v) + \gamma \cdot (z- Th \cdot v - \frac{1}{2} \cdot \frac{(v - v_0)^2}{c \cdot g})$  

最后转化为  

$f(x)=\frac{1}{2} \cdot x^T \cdot P \cdot x + q^T \cdot x$  
$subject\ to:$  
$aCLF \cdot x \leq constraintValueCLF$  
$aCBF \cdot x \leq constraintValueCBF$  

$x = \left[\begin{matrix} u \\ \delta \end{matrix}\right]$  

$P = \left[\begin{matrix} 1 & 0 \\ 0 & p \end{matrix}\right]$  

$q = \left[\begin{matrix}0 & 0\end{matrix}\right]$  

将约束表示为矩阵形式：  

$l \leq A \cdot x \leq u$  

这里转换成三个约束条件，是引入松弛变量  
将CLF不等式约束转化为等式约束  
$aCLF \cdot x - \delta = constraintValueCLF$  
$\delta \geq 0$  


$A = \left[\begin{matrix} aCLF & -1 \\ aCBF & 0 \\ 0 & 1 \end{matrix}\right]$  

$l = \left[\begin{matrix}constraintValueCLF - \delta \\ -INFTY \\ 0 \end{matrix}\right]$  

$u = \left[\begin{matrix} constraintValueCLF - \delta \\ constraintValueCBF \\ INFTY \end{matrix}\right]$  

这里$constraintValueCLF - \delta$是因为上面化简时将$\delta$也算入了常数项  
