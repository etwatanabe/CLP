(defun fib (n)
  (if (or (= n 1) (= n 2))
    1
    (+ (fib (- n 1)) (fib (- n 2)))
  )
)

(defun fat (N)
  (if (= N 1)
    1
    (* N (fat (- N 1)))
  )
)

(defun g (n)
  (cond
    ((< n 0) nil)
    ((= n 1) 1)
    (t (if (= (rem n 2) 0)
      (- (g (- n 1)) (/ n (fat (fib n))))
      (+ (g (- n 1)) (/ n (fat (fib n))))
    ))
  )
)

(print (g 5))