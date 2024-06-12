(defun merge-sort (lst)
  (if (or (null lst) (null (cdr lst)))
      lst
      (let* ((middle (floor (length lst) 2))
             (left (subseq lst 0 middle))
             (right (subseq lst middle)))
        (merge (merge-sort left) (merge-sort right)))))

(defun merge (left right)
  (cond ((null left) right)
        ((null right) left)
        ((<= (car left) (car right))
         (cons (car left) (merge (cdr left) right)))
        (t (cons (car right) (merge left (cdr right))))))
