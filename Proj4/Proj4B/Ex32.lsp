(defun fat (N)
  (if (= N 1)
    1
    (* N (fat (- N 1)))
  )
)

(defun pow (x n)
  (if (= n 0)
    1
    (* x (pow x (- n 1)))
  )
)

(defun e (x n)
  (cond
    ((< n 0) nil)
    ((= n 0) 1) 
    (t (+ (/ (pow x n) (fat n)) (e x (- n 1))))
  )
)

(print (e 2 4))