(defun fib (n)
  (if (or (= n 1) (= n 2))
    1
    (+ (fib (- n 1)) (fib (- n 2)))
  )
)

(defun prodFib (n)
  (cond 
    ((< n 1) nil)
    ((= n 1) (fib 1))
    (t (* (prodFib (- n 1)) (fib n)))
  )
)

(print (prodFib 7))