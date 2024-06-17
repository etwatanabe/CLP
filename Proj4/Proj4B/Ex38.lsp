(defun pow (x n)
  (if (= n 0)
    1
    (* x (pow x (- n 1)))
  )
)

(defun fat (n)
  (if (= n 1)
    1
    (* n (fat (- n 1)))
  )
)

(defun h (n)
  (cond
    ((< n 1) nil)
    ((= n 1) 1)
    (t (if (= (rem n 2) 0)
      (- (h (- n 1)) (/ (pow n n) (fat n)))
      (+ (h (- n 1)) (/ (pow n n) (fat n)))
    ))
  )
)

(print (h 5))