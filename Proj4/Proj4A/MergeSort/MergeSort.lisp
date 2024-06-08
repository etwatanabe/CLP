(defun merge-sort (list)
  (if (or (null list) (null (cdr list)))
      list
      (let ((middle (truncate (length list) 2)))
        (merge 'list
               (merge-sort (subseq list 0 middle))
               (merge-sort (subseq list middle))
               #'<))))

;; Helper function to display the sorted list
(defun print-list (list)
  (dolist (item list)
    (format t "~a " item))
  (terpri))

;; Main function to test merge sort
(defun main ()
  (let ((list '(12 11 13 5 6 7)))
    (format t "Given list: ~a~%" list)
    (let ((sorted-list (merge-sort list)))
      (format t "Sorted list: ")
      (print-list sorted-list))))

(main)
