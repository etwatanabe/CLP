(defun quicksort (lst)
  (if (null lst)
      nil
      (let ((pivot (car lst))
            (rest (cdr lst)))
        (append (quicksort (remove-if-not (lambda (x) (<= x pivot)) rest))
                (list pivot)
                (quicksort (remove-if-not (lambda (x) (> x pivot)) rest))))))
