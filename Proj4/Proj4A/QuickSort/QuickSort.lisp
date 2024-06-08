(defun quicksort (list)
  (if (or (null list) (null (cdr list)))
      list
      (let* ((pivot (car list))
             (rest (cdr list))
             (smaller (remove-if-not (lambda (x) (<= x pivot)) rest))
             (greater (remove-if-not (lambda (x) (> x pivot)) rest)))
        (append (quicksort smaller) (list pivot) (quicksort greater)))))

;; Example usage
(let ((list '(10 7 8 9 1 5)))
  (format t "Sorted list: ~a~%" (quicksort list)))
