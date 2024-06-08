(defun A (m n)
  (cond ((= m 0) (+ n 1))
        ((and (> m 0) (= n 0)) (A (- m 1) 1))
        ((and (> m 0) (> n 0)) (A (- m 1) (A m (- n 1))))))
        
(print (A 1 2))