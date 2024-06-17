(defun impar (n)
"Calcula o n-esimo numero impar"
  (- (* 2 n) 1)
)

(defun calcularPI (n)
  (cond
    ((< n 0) nil)
    ((= n 1) 4)
    (t (if (= (rem n 2) 0) (- (calcularPI (- n 1)) (/ 4 (impar n))) (+ (calcularPI (- n 1)) (/ 4 (impar n)))))
  )
)

(print (calcularPI 5))