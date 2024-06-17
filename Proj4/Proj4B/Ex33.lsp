(defun x (A n)
  (cond
    ((or (<= A 0) (< n 0)) nil)
    ((= n 1) 1)
    (t (/ (+ (x A (- n 1)) (/ A (x A (- n 1)))) 2))
  )
)

(print (x 3 5))