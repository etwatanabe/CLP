(defun insert (item lst)
  (cond ((null lst) (list item))
        ((<= item (car lst)) (cons item lst))
        (t (cons (car lst) (insert item (cdr lst))))))

(defun insertion-sort (lst)
  (if (null lst)
      nil
      (insert (car lst) (insertion-sort (cdr lst)))))
